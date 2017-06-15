#pragma once

class EMessage;

struct ETransport
{
    virtual int send(EMessage *pMsg) = 0;
    //virtual int sendBufferedData() = 0;
    //virtual bool isOutBufferEmpty() const = 0;
};

