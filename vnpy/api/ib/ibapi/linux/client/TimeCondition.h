#pragma once
#include "OperatorCondition.h"

class TWSAPIDLLEXP TimeCondition : public OperatorCondition {
	friend OrderCondition;

	std::string m_time;

protected:
	TimeCondition() { }

	virtual std::string valueToString() const;
	virtual void valueFromString(const std::string &v);

public:
	static const OrderConditionType conditionType = OrderConditionType::Time;

	virtual std::string toString();

	std::string time();
	void time(const std::string &time);
};