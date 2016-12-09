/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef eposixclientsocket_def
#define eposixclientsocket_def

#include "../client/EClient.h"
#include "../client/EClientMsgSink.h"
#include "ESocketSSL.h"
#include "../client/EMutex.h"

class EWrapper;
class EReaderSignal;

class TWSAPISSLDLLEXP EClientSocketSSL : public EClient, public EClientMsgSink
{
protected:
    virtual void prepareBufferImpl(std::ostream&) const;
	virtual void prepareBuffer(std::ostream&) const;
	virtual bool closeAndSend(std::string msg, unsigned offset = 0);

public:

	explicit EClientSocketSSL(EWrapper *ptr, EReaderSignal *pSignal = 0);
	~EClientSocketSSL();

	bool eConnect( const char *host, unsigned int port, int clientId = 0, bool extraAuth = false);
	// override virtual funcs from EClient
	void eDisconnect();

	bool isSocketOK() const;
	int fd() const;
    bool asyncEConnect() const;
    void asyncEConnect(bool val);
    ESocketSSL *getTransport();

private:

	bool eConnectImpl(int clientId, bool extraAuth, ConnState* stateOutPt);

private:
	void encodeMsgLen(std::string& msg, unsigned offset) const;
    bool handleSSLError(int &ret_code);
	bool handleSocketErrorInternal(int hr = 0);

public:
	bool handleSocketError();
	bool handleSocketError(int res);
	int receive( char* buf, size_t sz);

public:
	// callback from socket
	void onSend();
	void onError();

private:

	void onClose();
    void ImportRootCertificatesFromWindowsCertStore();

    static void lockingFunc(int mode, int type, const char *file, int line);
    static unsigned long thIdFunc();

    static std::vector<EMutex> sslLocks;

    SSL *m_pSSL;
    SSL_CTX *m_pCTX;
	int m_fd;
    bool m_allowRedirect;
    const char* m_hostNorm;
    bool m_asyncEConnect;
    EReaderSignal *m_pSignal;

//EClientMsgSink implementation
public:
    void serverVersion(int version, const char *time);
    void redirect(const char *host, int port);    
};

#endif
