/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "EMessage.h"


EMessage::EMessage(const std::vector<char> &data) {
    this->data = data;
}

const char* EMessage::begin(void) const
{
    return data.data();
}

const char* EMessage::end(void) const
{
    return data.data() + data.size();
}
