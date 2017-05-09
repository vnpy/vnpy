#include "StdAfx.h"
#include "TimeCondition.h"

std::string TimeCondition::valueToString() const {
	return m_time;
}

void TimeCondition::valueFromString(const std::string & v) {
	m_time = v;
}

std::string TimeCondition::toString() {
	return "time" + OperatorCondition::toString();
}

std::string TimeCondition::time() {
	return m_time;
}

void TimeCondition::time(const std::string & time) {
	m_time = time;
}
