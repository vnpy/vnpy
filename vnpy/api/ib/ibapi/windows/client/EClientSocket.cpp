/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"


#include "EPosixClientSocketPlatform.h"
#include "EClientSocket.h"

#include "TwsSocketClientErrors.h"
#include "EWrapper.h"
#include "EDecoder.h"
#include "EReaderSignal.h"
#include "EReader.h"
#include "EMessage.h"

#include <string.h>
#include <assert.h>
#include <ostream>

const int MIN_SERVER_VER_SUPPORTED    = 38; //all supported server versions are defined in EDecoder.h

///////////////////////////////////////////////////////////
// member funcs
EClientSocket::EClientSocket(EWrapper *ptr, EReaderSignal *pSignal) : EClient( ptr, new ESocket())
{
	m_fd = SocketsInit() ? -1 : -2;
    m_allowRedirect = false;
    m_asyncEConnect = false;
    m_pSignal = pSignal;
}

EClientSocket::~EClientSocket()
{
	if( m_fd != -2)
		SocketsDestroy();
}

bool EClientSocket::asyncEConnect() const {
    return m_asyncEConnect;
}

void EClientSocket::asyncEConnect(bool val) {
    m_asyncEConnect = val;
}

bool EClientSocket::eConnect( const char *host, unsigned int port, int clientId, bool extraAuth)
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

ESocket *EClientSocket::getTransport() {
    assert(dynamic_cast<ESocket*>(m_transport.get()) != 0);

    return static_cast<ESocket*>(m_transport.get());
}

bool EClientSocket::eConnectImpl(int clientId, bool extraAuth, ConnState* stateOutPt)
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

    getTransport()->fd(m_fd);

	// set client id
	setClientId( clientId);
	setExtraAuth( extraAuth);

    int res = sendConnectRequest();

    if (res < 0 && !handleSocketError())
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
        EReader reader(this, m_pSignal);

		reader.putMessageToQueue();

        while (m_pSignal && !m_serverVersion && isSocketOK()) {
            reader.checkClient();
            m_pSignal->waitForSignal();
            reader.processMsgs();
        }
    }

	// successfully connected
	return isSocketOK();
}

void EClientSocket::encodeMsgLen(std::string& msg, unsigned offset) const
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

bool EClientSocket::closeAndSend(std::string msg, unsigned offset)
{
	assert( !msg.empty());
	if( m_useV100Plus) {
		encodeMsgLen( msg, offset);
	}

	if (bufferedSend(msg) == -1)
        return handleSocketError();

    return true;
}

void EClientSocket::prepareBufferImpl(std::ostream& buf) const
{
	assert( m_useV100Plus);
	assert( sizeof(unsigned) == HEADER_LEN);

	char header[HEADER_LEN] = { 0 };
	buf.write( header, sizeof(header));
}

void EClientSocket::prepareBuffer(std::ostream& buf) const
{
	if( !m_useV100Plus)
		return;

	prepareBufferImpl( buf);
}

void EClientSocket::eDisconnect()
{
	if ( m_fd >= 0 )
		// close socket
			SocketClose( m_fd);
	m_fd = -1;

	eDisconnectBase();
}

bool EClientSocket::isSocketOK() const
{
	return ( m_fd >= 0);
}

int EClientSocket::fd() const
{
	return m_fd;
}

int EClientSocket::receive(char* buf, size_t sz)
{
	if( sz <= 0)
		return 0;

	int nResult = ::recv( m_fd, buf, sz, 0);

	if( nResult == -1 && !handleSocketError()) {
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

void EClientSocket::serverVersion(int version, const char *time) {
    m_serverVersion = version;
    m_TwsTime = time;

    if( usingV100Plus() ? (m_serverVersion < MIN_CLIENT_VER || m_serverVersion > MAX_CLIENT_VER) : m_serverVersion < MIN_SERVER_VER_SUPPORTED ) {
        getWrapper()->error( NO_VALID_ID, UNSUPPORTED_VERSION.code(), UNSUPPORTED_VERSION.msg());
        eDisconnect();
    }

	if (!m_asyncEConnect)
		startApi();
}

void EClientSocket::redirect(const char *host, int port) {
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

bool EClientSocket::handleSocketError()
{
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


///////////////////////////////////////////////////////////
// callbacks from socket

void EClientSocket::onSend()
{
	if( !handleSocketError())
		return;

	getTransport()->sendBufferedData();
}

void EClientSocket::onClose()
{
	if( !handleSocketError())
		return;

	eDisconnect();
	getWrapper()->connectionClosed();
}

void EClientSocket::onError()
{
	handleSocketError();
}