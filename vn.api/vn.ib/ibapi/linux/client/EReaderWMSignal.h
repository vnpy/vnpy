/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#include "ereadersignal.h"

class EReaderWMSignal :
	public EReaderSignal
{
	HWND m_hWnd;
	int m_msg;

public:
	EReaderWMSignal(HWND hWnd, int msg);

	virtual void issueSignal();
    virtual void waitForSignal();
};

