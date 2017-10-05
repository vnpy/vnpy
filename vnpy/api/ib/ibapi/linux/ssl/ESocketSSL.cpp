#include "StdAfx.h"
#include "../client/EMessage.h"
#include "ESocketSSL.h"

#include <assert.h>

ESocketSSL::ESocketSSL() {
}

void ESocketSSL::fd(SSL *fd) {
    m_fd = fd;
}

ESocketSSL::~ESocketSSL(void) {
}

int ESocketSSL::send(EMessage *pMsg) {
    return bufferedSend(pMsg->begin(), pMsg->end() - pMsg->begin());
}

int ESocketSSL::bufferedSend(const char* buf, size_t sz)
{
	if( sz <= 0)
		return 0;

	if( !m_outBuffer.empty()) {
		m_outBuffer.insert( m_outBuffer.end(), buf, buf + sz);
		return sendBufferedData();
	}

	int nResult = send(buf, sz);

	if( nResult < (int)sz) {
		int sent = (std::max)( nResult, 0);
		m_outBuffer.insert( m_outBuffer.end(), buf + sent, buf + sz);
	}

	return nResult;
}

int ESocketSSL::sendBufferedData()
{
	if( m_outBuffer.empty())
		return 0;

	int nResult = send( &m_outBuffer[0], m_outBuffer.size());
	if( nResult <= 0) {
		return nResult;
	}
	CleanupBuffer( m_outBuffer, nResult);
	return nResult;
}

int ESocketSSL::send(const char* buf, size_t sz)
{
	if( sz <= 0)
		return 0;

	int nResult = ::SSL_write( m_fd, buf, sz);

	if( nResult == -1) {
		return -1;
	}
	if( nResult <= 0) {
		return 0;
	}
	return nResult;
}

static const size_t BufferSizeHighMark = 1 * 1024 * 1024; // 1Mb

void ESocketSSL::CleanupBuffer(std::vector<char>& buffer, int processed)
{
	assert( buffer.empty() || processed <= (int)buffer.size());

	if( buffer.empty())
		return;

	if( processed <= 0)
		return;

	if( (size_t)processed == buffer.size()) {
		if( buffer.capacity() >= BufferSizeHighMark) {
			std::vector<char>().swap(buffer);
		}
		else {
			buffer.clear();
		}
	}
	else {
		buffer.erase( buffer.begin(), buffer.begin() + processed);
	}
}

bool ESocketSSL::isOutBufferEmpty() const
{
	return m_outBuffer.empty();
}
