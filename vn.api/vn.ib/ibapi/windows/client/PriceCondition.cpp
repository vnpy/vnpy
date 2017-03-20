#include "StdAfx.h"
#include "PriceCondition.h"
#include <sstream>
#include "EDecoder.h"
#include "EClient.h"

std::string PriceCondition::valueToString() const {
	std::stringstream tmp;

	tmp << m_price;

	return tmp.str();
}

void PriceCondition::valueFromString(const std::string & v) {
	std::stringstream tmp;

	tmp << v;
	tmp >> m_price;
}

double PriceCondition::price() {
	return m_price;
}

void PriceCondition::price(double price) {
	m_price = price;
}

std::string PriceCondition::toString() {
	return strTriggerMethod() + " " + ContractCondition::toString();
}

PriceCondition::Method PriceCondition::triggerMethod() {
	return (Method)m_triggerMethod;
}

std::string PriceCondition::strTriggerMethod() {
	static std::string mthdNames[] = { "default", "double bid/ask", "last", "double last", "bid/ask", "", "", "last of bid/ask", "mid-point" };

	return mthdNames[triggerMethod()];
}

void PriceCondition::triggerMethod(Method triggerMethod) {
	m_triggerMethod = triggerMethod;
}

const char* PriceCondition::readExternal(const char* ptr, const char* endPtr) {
	if (!(ptr = ContractCondition::readExternal(ptr, endPtr)))
		return 0;

	DECODE_FIELD(m_triggerMethod)

	return ptr;
}

void PriceCondition::writeExternal(std::ostream & msg) const {
	ContractCondition::writeExternal(msg);

	ENCODE_FIELD(m_triggerMethod);
}
