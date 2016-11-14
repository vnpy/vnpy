/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"


#include "../client/EPosixClientSocketPlatform.h"
#include "EClientSocketSSL.h"

#include "../client/TwsSocketClientErrors.h"
#include "../client/EWrapper.h"
#include "../client/EDecoder.h"
#include "../client/EReaderSignal.h"
#include "EReaderSSL.h"
#include "../client/EMessage.h"

#include <string.h>
#include <assert.h>
#include <ostream>

const int MIN_SERVER_VER_SUPPORTED    = 38; //all supported server versions are defined in EDecoder.h

std::vector<EMutex> EClientSocketSSL::sslLocks(CRYPTO_num_locks());

void EClientSocketSSL::lockingFunc(int mode, int type, const char *file, int line) {
    if (mode & CRYPTO_LOCK)
        sslLocks[type].Enter();
    else
        sslLocks[type].Leave();
}

unsigned long EClientSocketSSL::thIdFunc() {
#if defined(IB_POSIX)
    return syscall(SYS_gettid);
#elif defined(IB_WIN32)
    return GetCurrentThreadId();
#else
#   error "Not implemented on this platform"
#endif

}

///////////////////////////////////////////////////////////
// member funcs
EClientSocketSSL::EClientSocketSSL(EWrapper *ptr, EReaderSignal *pSignal) : EClient( ptr, new ESocketSSL())
{
	m_fd = SocketsInit() ? -1 : -2;
    m_allowRedirect = false;
    m_asyncEConnect = false;
    m_pSignal = pSignal;

    SSL_load_error_strings();
    ERR_load_BIO_strings();
    SSL_library_init();
    CRYPTO_set_locking_callback(lockingFunc);
    CRYPTO_w_lock(CRYPTO_LOCK_DYNLOCK);
    CRYPTO_set_id_callback(thIdFunc);
    CRYPTO_w_unlock(CRYPTO_LOCK_DYNLOCK);
}

EClientSocketSSL::~EClientSocketSSL()
{
	if( m_fd != -2)
		SocketsDestroy();
}

bool EClientSocketSSL::asyncEConnect() const {
    return m_asyncEConnect;
}

void EClientSocketSSL::asyncEConnect(bool val) {
    m_asyncEConnect = val;
}

bool EClientSocketSSL::eConnect( const char *host, unsigned int port, int clientId, bool extraAuth)
{
	if( m_fd == -2) {
		getWrapper()->error( NO_VALID_ID, FAIL_CREATE_SOCK.code(), FAIL_CREATE_SOCK.msg());
		return false;
	}

	// reset errno
	errno = 0;

	// already connected?
	if( m_fd >= 0) {
		errno = EISCONN;
		getWrapper()->error( NO_VALID_ID, ALREADY_CONNECTED.code(), ALREADY_CONNECTED.msg());
		return false;
	}

	// normalize host
	m_hostNorm = (host && *host) ? host : "127.0.0.1";

	// initialize host and port
	setHost( m_hostNorm);
	setPort( port);

	// try to connect to specified host and port
	ConnState resState = CS_DISCONNECTED;
	
    return eConnectImpl( clientId, extraAuth, &resState);
}

ESocketSSL *EClientSocketSSL::getTransport() {
    assert(dynamic_cast<ESocketSSL*>(m_transport.get()) != 0);

    return static_cast<ESocketSSL*>(m_transport.get());
}

void EClientSocketSSL::ImportRootCertificatesFromWindowsCertStore() {
#if defined(IB_WIN32)
    auto store = CertOpenSystemStore(0, "ROOT");
    auto osslStore = SSL_CTX_get_cert_store(m_pCTX);

    for (auto certCtx = CertEnumCertificatesInStore(store, 0); certCtx; certCtx = CertEnumCertificatesInStore(store, certCtx)) {
        if (!(certCtx->dwCertEncodingType & X509_ASN_ENCODING))
            continue;

        auto pBuf = certCtx->pbCertEncoded;
        auto cert = d2i_X509(0, (const unsigned char **)&pBuf, certCtx->cbCertEncoded);

        X509_STORE_add_cert(osslStore, cert);
    }


    CertCloseStore(store, 0);
#endif
}


bool EClientSocketSSL::eConnectImpl(int clientId, bool extraAuth, ConnState* stateOutPt)
{
	// resolve host
	struct hostent* hostEnt = gethostbyname( host().c_str());
	if ( !hostEnt) {
		getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
		return false;
	}

	// create socket
	m_fd = socket(AF_INET, SOCK_STREAM, 0);

	// cannot create socket
	if( m_fd < 0) {
		getWrapper()->error( NO_VALID_ID, FAIL_CREATE_SOCK.code(), FAIL_CREATE_SOCK.msg());
		return false;
	}

	// starting to connect to server
	struct sockaddr_in sa;
	memset( &sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons( port());
	sa.sin_addr.s_addr = ((in_addr*)hostEnt->h_addr)->s_addr;

	// try to connect
	if( (connect( m_fd, (struct sockaddr *) &sa, sizeof( sa))) < 0) {
		// error connecting
		SocketClose( m_fd);
		m_fd = -1;
		getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
		return false;
	}

    m_pCTX = SSL_CTX_new(SSLv23_client_method());

    if (!m_pCTX && !handleSocketError())
        return false;

    ImportRootCertificatesFromWindowsCertStore();

    m_pSSL = SSL_new(m_pCTX);

    if (!m_pSSL && !handleSocketError())
        return false;

    if (!SSL_set_fd(m_pSSL, m_fd) && !handleSocketError())
        return false;

    if (!SSL_connect(m_pSSL) && !handleSocketError())
        return false;

    if(SSL_get_verify_result(m_pSSL) != X509_V_OK)
    {
        getWrapper()->error(NO_VALID_ID, SSL_FAIL.code(), SSL_FAIL.msg() + "certificate verification failure");

        //return false;
    }

    getTransport()->fd(m_pSSL);

	// set client id
	setClientId( clientId);
	setExtraAuth( extraAuth);
	
    int res = sendConnectRequest();

    if (res == 0 || res < 0 && !handleSocketError(res))
        return false;

	if( !isConnected()) {
		if( connState() != CS_DISCONNECTED) {
			assert( connState() == CS_REDIRECT);
			if( stateOutPt) {
				*stateOutPt = connState();
			}
			eDisconnect();
		}
		return false;
	}

	// set socket to non-blocking state
	if ( !SetSocketNonBlocking(m_fd)) {
	// error setting socket to non-blocking
		eDisconnect();
		getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
		return false;
	}

	assert( connState() == CS_CONNECTED);
	if( stateOutPt) {
		*stateOutPt = connState();
	}
            
    if (!m_asyncEConnect) {
        EReaderSSL reader(this, m_pSignal);

        while (m_pSignal && !m_serverVersion && isSocketOK()) {
            reader.checkClient();
            m_pSignal->waitForSignal();
            reader.processMsgs();
        }
    }

	// successfully connected
	return isSocketOK();
}

void EClientSocketSSL::encodeMsgLen(std::string& msg, unsigned offset) const
{
	assert( !msg.empty());
	assert( m_useV100Plus);

	assert( sizeof(unsigned) == HEADER_LEN);
	assert( msg.size() > offset + HEADER_LEN);
	unsigned len = msg.size() - HEADER_LEN - offset;
	if( len > MAX_MSG_LEN) {
		m_pEWrapper->error( NO_VALID_ID, BAD_LENGTH.code(), BAD_LENGTH.msg());
		return;
	}

	unsigned netlen = htonl( len);
	memcpy( &msg[offset], &netlen, HEADER_LEN);
}

bool EClientSocketSSL::closeAndSend(std::string msg, unsigned offset)
{
	assert( !msg.empty());
	if( m_useV100Plus) {
		encodeMsgLen( msg, offset);
	}

    int res = bufferedSend(msg);

	if (res < 0)
        return handleSocketError(res);

    return true;
}

void EClientSocketSSL::prepareBufferImpl(std::ostream& buf) const
{
	assert( m_useV100Plus);
	assert( sizeof(unsigned) == HEADER_LEN);

	char header[HEADER_LEN] = { 0 };
	buf.write( header, sizeof(header));
}

void EClientSocketSSL::prepareBuffer(std::ostream& buf) const
{
	if( !m_useV100Plus)
		return;

	prepareBufferImpl( buf);
}

void EClientSocketSSL::eDisconnect()
{
    if (m_pSSL)
        SSL_shutdown(m_pSSL);

    if (m_pCTX)
        SSL_CTX_free(m_pCTX);

	if ( m_fd >= 0 )
		// close socket
			SocketClose( m_fd);
	m_fd = -1;

	eDisconnectBase();
}

bool EClientSocketSSL::isSocketOK() const
{
	return ( m_fd >= 0);
}

int EClientSocketSSL::fd() const
{
	return m_fd;
}

int EClientSocketSSL::receive(char* buf, size_t sz)
{
	if( sz <= 0)
		return 0;

	int nResult = SSL_read(m_pSSL, buf, sz);

	if( nResult == -1 && !handleSocketError(nResult)) {
		return -1;
	}
	if( nResult == 0) {
		onClose();
	}
	if( nResult <= 0) {
		return 0;
	}
	return nResult;
}

void EClientSocketSSL::serverVersion(int version, const char *time) {
    m_serverVersion = version;
    m_TwsTime = time;

    if( usingV100Plus() ? (m_serverVersion < MIN_CLIENT_VER || m_serverVersion > MAX_CLIENT_VER) : m_serverVersion < MIN_SERVER_VER_SUPPORTED ) {
        getWrapper()->error( NO_VALID_ID, UNSUPPORTED_VERSION.code(), UNSUPPORTED_VERSION.msg());
        eDisconnect();
    }

	if (!m_asyncEConnect)
		startApi();
}

void EClientSocketSSL::redirect(const char *host, int port) {
	// handle redirect
	if( (m_hostNorm != this->host() || port != this->port())) {
        if (!m_allowRedirect) {
            getWrapper()->error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());

            return;
        }

        eDisconnect();
		eConnectImpl( clientId(), extraAuth(), 0);
	}
}

bool EClientSocketSSL::handleSSLError(int &ret_code) {
    ret_code = SSL_get_error(m_pSSL, ret_code);

    switch (ret_code) {
    case SSL_ERROR_NONE:
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
		ret_code = 0;
        return true;

	case SSL_ERROR_SYSCALL:
#if defined(IB_POSIX)
		ret_code = errno;
#elif defined(IB_WIN32)
		ret_code = GetLastError();
#else
#   error "Not implemented on this platform"
#endif
		return true;
    }

    return false;
}

bool EClientSocketSSL::handleSocketErrorInternal(int hr) {
#if defined(IB_WIN32)
	if (hr != 0) {
		LPTSTR buf;

		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 0, hr, 0, (LPTSTR)&buf, 0, 0);
		getWrapper()->error( NO_VALID_ID, SOCKET_EXCEPTION.code(),
			SOCKET_EXCEPTION.msg() + buf);
		LocalFree(buf);

		return false;
	}
#endif

    	// no error
	if( errno == 0)
		return true;

	// Socket is already connected
	if( errno == EISCONN) {
		return true;
	}

	if( errno == EWOULDBLOCK)
		return false;

	if( errno == ECONNREFUSED) {
		getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
	}
	else {
		getWrapper()->error( NO_VALID_ID, SOCKET_EXCEPTION.code(),
			SOCKET_EXCEPTION.msg() + strerror(errno));
	}
	// reset errno
	errno = 0;
	eDisconnect();
	return false;
}

bool EClientSocketSSL::handleSocketError(int res)
{
    if (!handleSSLError(res)) {
        getWrapper()->error(NO_VALID_ID, SSL_FAIL.code(), SSL_FAIL.msg() + ERR_error_string(res, 0));

        return false;
    }

    return handleSocketErrorInternal(res);
}

bool EClientSocketSSL::handleSocketError() {
    int res = ERR_get_error();

    if (res) {
        getWrapper()->error(NO_VALID_ID, SSL_FAIL.code(), SSL_FAIL.msg() + ERR_error_string(res, 0));

        return false;
    }

    return handleSocketErrorInternal();  
}

///////////////////////////////////////////////////////////
// callbacks from socket

void EClientSocketSSL::onSend()
{
	if( !handleSocketError())
		return;

	getTransport()->sendBufferedData();
}

void EClientSocketSSL::onClose()
{
	if( !handleSocketError())
		return;

	eDisconnect();
	getWrapper()->connectionClosed();
}

void EClientSocketSSL::onError()
{
	handleSocketError();
}
