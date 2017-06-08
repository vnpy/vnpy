/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once

#include "StdAfx.h"

class TWSAPIDLLEXP EMutex
{
#if defined(IB_POSIX)
    pthread_mutex_t cs;
#elif defined(IB_WIN32)
    CRITICAL_SECTION cs;
#else
#   error "Not implemented on this platform"
#endif

public:
    EMutex();
    ~EMutex();
    bool TryEnter();
    void Enter();
    void Leave();
};

