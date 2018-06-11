#pragma once
#include "OrderCondition.h"

class TWSAPIDLLEXP OperatorCondition : public OrderCondition {
	bool m_isMore;

protected:
	virtual std::string valueToString() const = 0;
	virtual void valueFromString(const std::string &v) = 0;

public:
	virtual const char* readExternal(const char* ptr, const char* endPtr);
	virtual std::string toString();
	virtual void writeExternal(std::ostream &out) const;

	bool isMore();
	void isMore(bool isMore);
};