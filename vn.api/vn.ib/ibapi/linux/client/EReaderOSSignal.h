/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#include "EReaderSignal.h"
#include "StdAfx.h"
#include <stdexcept>

#if !defined(INFINITE)
#define INFINITE ((unsigned long)-1)
#endif

class TWSAPIDLLEXP EReaderOSSignal :
	public EReaderSignal
{
#if defined(IB_POSIX)
    pthread_cond_t m_evMsgs;
    pthread_mutex_t m_mutex;
#elif defined(IB_WIN32)
	HANDLE m_evMsgs;
#else
#   error "Not implemented on this platform"
#endif
    unsigned long m_waitTimeout; // in milliseconds

public:
	EReaderOSSignal(unsigned long waitTimeout = INFINITE) throw (std::runtime_error);
	~EReaderOSSignal(void);

	virtual void issueSignal();
	virtual void waitForSignal();
};

