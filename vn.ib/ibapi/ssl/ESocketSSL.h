#pragma once
#include "../client/ETransport.h"

class ESocketSSL :
    public ETransport
{
    SSL *m_fd;
	std::vector<char> m_outBuffer;

    int bufferedSend(const char* buf, size_t sz);
    int send(const char* buf, size_t sz);
    void CleanupBuffer(std::vector<char>& buffer, int processed);

public:
    ESocketSSL();
    ~ESocketSSL(void);

    int send(EMessage *pMsg);
    bool isOutBufferEmpty() const;
    int sendBufferedData();
    void fd(SSL *fd);
};

