#pragma once
#include <ios>

struct IExternalizable
{
	virtual const char* readExternal(const char* ptr, const char* endPtr) = 0;
	virtual void writeExternal(std::ostream &out) const = 0;
};

