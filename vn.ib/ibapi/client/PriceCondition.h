#pragma once
#include "ContractCondition.h"

class TWSAPIDLLEXP PriceCondition : public ContractCondition {
	friend OrderCondition;

	double m_price;
	int m_triggerMethod;

	virtual std::string valueToString() const;
	virtual void valueFromString(const std::string &v);

protected:
	PriceCondition() { };

public:
	static const OrderConditionType conditionType = OrderConditionType::Price;
	enum Method {
		Default = 0,
		DoubleBidAsk = 1,
		Last = 2,
		DoubleLast = 3,
		BidAsk = 4,
		LastBidAsk = 7,
		MidPoint = 8
	};

	double price();
	void price(double price);

	virtual std::string toString();
	virtual const char* readExternal(const char* ptr, const char* endPtr);
	virtual void writeExternal(std::ostream & out) const;

	Method triggerMethod();
	std::string strTriggerMethod();
	void triggerMethod(Method triggerMethod);
};