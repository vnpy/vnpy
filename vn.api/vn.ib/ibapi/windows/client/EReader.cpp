/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "shared_ptr.h"
#include "Contract.h"
#include "EDecoder.h"
#include "EMutex.h"
#include "EReader.h"
#include "EClientSocket.h"
#include "EPosixClientSocketPlatform.h"
#include "EReaderSignal.h"
#include "EMessage.h"
#include "DefaultEWrapper.h"

#define IN_BUF_SIZE_DEFAULT 8192

static DefaultEWrapper defaultWrapper;

EReader::EReader(EClientSocket *clientSocket, EReaderSignal *signal)
	: processMsgsDecoder_(clientSocket->EClient::serverVersion(), clientSocket->getWrapper(), clientSocket) {
		m_isAlive = true;
        m_pClientSocket = clientSocket;       
		m_pEReaderSignal = signal;
		m_needsWriteSelect = false;
		m_nMaxBufSize = IN_BUF_SIZE_DEFAULT;
		m_buf.reserve(IN_BUF_SIZE_DEFAULT);
}

EReader::~EReader(void) {
    m_isAlive = false;

#if defined(IB_WIN32)
    WaitForSingleObject(m_hReadThread, INFINITE);
#endif
}

void EReader::checkClient() {
	m_needsWriteSelect = !m_pClientSocket->getTransport()->isOutBufferEmpty();
}

void EReader::start() {
#if defined(IB_POSIX)
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create( &thread, &attr, readToQueueThread, this );
    pthread_attr_destroy(&attr);
#elif defined(IB_WIN32)
    m_hReadThread = CreateThread(0, 0, readToQueueThread, this, 0, 0);
#else
#   error "Not implemented on this platform"
#endif
}

#if defined(IB_POSIX)
void * EReader::readToQueueThread(void * lpParam)
#elif defined(IB_WIN32)
DWORD WINAPI EReader::readToQueueThread(LPVOID lpParam)
#else
#   error "Not implemented on this platform"
#endif
{
	EReader *pThis = reinterpret_cast<EReader *>(lpParam);

	pThis->readToQueue();
	return 0;
}

void EReader::readToQueue() {
	EMessage *msg = 0;

	while (m_isAlive) {
		if (m_buf.size() == 0 && !processNonBlockingSelect() && m_pClientSocket->isSocketOK())
			continue;

        if (!putMessageToQueue())
			break;
	}

	m_pClientSocket->handleSocketError();
	m_pEReaderSignal->issueSignal(); //letting client know that socket was closed
}

bool EReader::putMessageToQueue() {
	EMessage *msg = 0;

	if (m_pClientSocket->isSocketOK())
		msg = readSingleMsg();

	if (msg == 0)
		return false;

	m_csMsgQueue.Enter();
	m_msgQueue.push_back(ibapi::shared_ptr<EMessage>(msg));
	m_csMsgQueue.Leave();
	m_pEReaderSignal->issueSignal();

	return true;
}

bool EReader::processNonBlockingSelect() {
	fd_set readSet, writeSet, errorSet;
	struct timeval tval;

	tval.tv_usec = 100 * 1000; //100 ms
	tval.tv_sec = 0;

	if( m_pClientSocket->fd() >= 0 ) {

		FD_ZERO( &readSet);
		errorSet = writeSet = readSet;

		FD_SET( m_pClientSocket->fd(), &readSet);

		if (m_needsWriteSelect)
			FD_SET( m_pClientSocket->fd(), &writeSet);

		FD_SET( m_pClientSocket->fd(), &errorSet);

		int ret = select( m_pClientSocket->fd() + 1, &readSet, &writeSet, &errorSet, &tval);

		if( ret == 0) { // timeout
			return false;
		}

		if( ret < 0) {	// error
			m_pClientSocket->eDisconnect();
			return false;
		}

		if( m_pClientSocket->fd() < 0)
			return false;

		if( FD_ISSET( m_pClientSocket->fd(), &errorSet)) {
			// error on socket
			m_pClientSocket->onError();
		}

		if( m_pClientSocket->fd() < 0)
			return false;

		if( FD_ISSET( m_pClientSocket->fd(), &writeSet)) {
			// socket is ready for writing
			onSend();
		}

		if( m_pClientSocket->fd() < 0)
			return false;

		if( FD_ISSET( m_pClientSocket->fd(), &readSet)) {
			// socket is ready for reading
			onReceive();
		}

		return true;
	}

	return false;
}

void EReader::onSend() {
	m_pEReaderSignal->issueSignal();
}

void EReader::onReceive() {
	int nOffset = m_buf.size();

	m_buf.resize(m_nMaxBufSize);
	
	int nRes = m_pClientSocket->receive(m_buf.data() + nOffset, m_buf.size() - nOffset);

	if (nRes <= 0)
		return;

 	m_buf.resize(nRes + nOffset);	
}

bool EReader::bufferedRead(char *buf, int size) {
	while (size > 0) {
		while (m_buf.size() < size && m_buf.size() < m_nMaxBufSize)
			if (!processNonBlockingSelect() && !m_pClientSocket->isSocketOK())
				return false;

		int nBytes = min(m_nMaxBufSize, size);

		std::copy(m_buf.begin(), m_buf.begin() + nBytes, buf);
		std::copy(m_buf.begin() + nBytes, m_buf.end(), m_buf.begin());
		m_buf.resize(m_buf.size() - nBytes);

		size -= nBytes;
		buf += nBytes;
	}

	return true;
}

EMessage * EReader::readSingleMsg() {
	if (m_pClientSocket->usingV100Plus()) {
		int msgSize;

		if (!bufferedRead((char *)&msgSize, sizeof(msgSize)))
			return 0;

		msgSize = htonl(msgSize);

		if (msgSize <= 0 || msgSize > MAX_MSG_LEN)
			return 0;

		std::vector<char> buf = std::vector<char>(msgSize);

		if (!bufferedRead(buf.data(), buf.size()))
			return 0;

		return new EMessage(buf);
	}
	else {
		const char *pBegin = 0;
		const char *pEnd = 0;
		int msgSize = 0;

		while (msgSize == 0)
		{
			if (m_buf.size() >= m_nMaxBufSize * 3/4) 
				m_nMaxBufSize *= 2;

			if (!processNonBlockingSelect() && !m_pClientSocket->isSocketOK())
				return 0;
		
			pBegin = m_buf.data();
			pEnd = pBegin + m_buf.size();
			msgSize = EDecoder(m_pClientSocket->EClient::serverVersion(), &defaultWrapper).parseAndProcessMsg(pBegin, pEnd);
		}
	
		std::vector<char> msgData(msgSize);

		if (!bufferedRead(msgData.data(), msgSize))
			return 0;

		if (m_buf.size() < IN_BUF_SIZE_DEFAULT && m_buf.capacity() > IN_BUF_SIZE_DEFAULT)
		{
			m_buf.resize(m_nMaxBufSize = IN_BUF_SIZE_DEFAULT);
			m_buf.shrink_to_fit();
		}

		EMessage * msg = new EMessage(msgData);

		return msg;
	}
}

ibapi::shared_ptr<EMessage> EReader::getMsg(void) {
	m_csMsgQueue.Enter();

	if (m_msgQueue.size() == 0) {
		m_csMsgQueue.Leave();

		return ibapi::shared_ptr<EMessage>();
	}

	ibapi::shared_ptr<EMessage> msg = m_msgQueue.front();

	m_msgQueue.pop_front();
	m_csMsgQueue.Leave();

	return msg;
}


void EReader::processMsgs(void) {
	m_pClientSocket->onSend();
	checkClient();

	ibapi::shared_ptr<EMessage> msg = getMsg();

	if (!msg.get())
		return;

	const char *pBegin = msg->begin();

	while (processMsgsDecoder_.parseAndProcessMsg(pBegin, msg->end()) > 0) {
		msg = getMsg();

		if (!msg.get())
			break;

		pBegin = msg->begin();
	} 
}
