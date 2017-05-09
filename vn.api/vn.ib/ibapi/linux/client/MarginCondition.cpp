#include "StdAfx.h"
#include "MarginCondition.h"
#include <sstream>

std::string MarginCondition::valueToString() const {
	std::stringstream tmp;

	tmp << m_percent;

	return tmp.str();
}

void MarginCondition::valueFromString(const std::string & v) {
	std::stringstream tmp;
	
	tmp << v;
	tmp >> m_percent;
}

std::string MarginCondition::toString() {
	return "the margin cushion percent" + OperatorCondition::toString();
}

int MarginCondition::percent() {
	return m_percent;
}

void MarginCondition::percent(int percent) {
	m_percent = percent;
}
