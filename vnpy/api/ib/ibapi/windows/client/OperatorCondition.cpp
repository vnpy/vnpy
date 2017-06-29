#include "StdAfx.h"
#include "OperatorCondition.h"
#include "EDecoder.h"
#include "EClient.h"

const char* OperatorCondition::readExternal(const char* ptr, const char* endPtr) {
	if (!(ptr = OrderCondition::readExternal(ptr, endPtr)))
		return 0;

	DECODE_FIELD(m_isMore);

	std::string str;

	DECODE_FIELD(str);

	valueFromString(str);

	return ptr;
}

std::string OperatorCondition::toString() {
	return " is " + std::string(isMore() ? ">= " : "<= ") + valueToString();
}

void OperatorCondition::writeExternal(std::ostream & msg) const {
	OrderCondition::writeExternal(msg);

	ENCODE_FIELD(m_isMore);
	ENCODE_FIELD(valueToString());
}

bool OperatorCondition::isMore() {
	return m_isMore;
}

void OperatorCondition::isMore(bool isMore) {
	m_isMore = isMore;
}
