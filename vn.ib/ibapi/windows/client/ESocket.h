#pragma once
#include "ETransport.h"

class ESocket :
    public ETransport
{
    int m_fd;
	std::vector<char> m_outBuffer;

    int bufferedSend(const char* buf, size_t sz);
    int send(const char* buf, size_t sz);
    void CleanupBuffer(std::vector<char>& buffer, int processed);

public:
    ESocket();
    ~ESocket(void);

    int send(EMessage *pMsg);
    bool isOutBufferEmpty() const;
    int sendBufferedData();
    void fd(int fd);
};

