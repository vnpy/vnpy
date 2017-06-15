#pragma once
#include <string>
#include "OrderCondition.h"

class TWSAPIDLLEXP ExecutionCondition : public OrderCondition {
	friend OrderCondition;

	std::string m_exchange;
	std::string m_secType;
	std::string m_symbol;

public:
	static const OrderConditionType conditionType = OrderConditionType::Execution;

protected:
	ExecutionCondition() { }

public:
	virtual const char* readExternal(const char* ptr, const char* endPtr);
	virtual std::string toString();
	virtual void writeExternal(std::ostream &out) const;

	std::string exchange();
	void exchange(const std::string &exchange);
	std::string secType();
	void secType(const std::string &secType);
	std::string symbol();
	void symbol(const std::string &symbol);
};