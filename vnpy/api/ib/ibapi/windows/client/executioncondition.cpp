#include "StdAfx.h"
#include "executioncondition.h"
#include "EDecoder.h"
#include "EClient.h"

const char* ExecutionCondition::readExternal(const char* ptr, const char* endPtr) {
	if (!(ptr = OrderCondition::readExternal(ptr, endPtr)))
		return 0;

	DECODE_FIELD(m_secType)
	DECODE_FIELD(m_exchange);
	DECODE_FIELD(m_symbol);

	return ptr;
}

std::string ExecutionCondition::toString() {
	return "trade occurs for " + m_symbol + " symbol on " + m_exchange + " exchange for " + m_secType + " security type";
}

void ExecutionCondition::writeExternal(std::ostream & msg) const {
	OrderCondition::writeExternal(msg);

	ENCODE_FIELD(m_secType);
	ENCODE_FIELD(m_exchange);
	ENCODE_FIELD(m_symbol);
}

std::string ExecutionCondition::exchange() {
	return m_exchange;
}

void ExecutionCondition::exchange(const std::string &exchange) {
	m_exchange = exchange;
}

std::string ExecutionCondition::secType() {
	return m_secType;
}

void ExecutionCondition::secType(const std::string &secType) {
	m_secType = secType;
}

std::string ExecutionCondition::symbol() {
	return m_symbol;
}

void ExecutionCondition::symbol(const std::string &symbol) {
	m_symbol = symbol;
}
