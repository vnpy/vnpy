#include "StdAfx.h"
#include "OrderCondition.h"
#include "executioncondition.h"
#include "MarginCondition.h"
#include "TimeCondition.h"
#include "PercentChangeCondition.h"
#include "PriceCondition.h"
#include "VolumeCondition.h"
#include "EDecoder.h"
#include "EClient.h"

const char* OrderCondition::readExternal(const char* ptr, const char* endPtr) {
	std::string connector;

	DECODE_FIELD(connector)

	conjunctionConnection(connector == "a");

	return ptr;
}

void OrderCondition::writeExternal(std::ostream & msg) const {
	ENCODE_FIELD(conjunctionConnection() ? "a" : "o")
}

std::string OrderCondition::toString() {
	return conjunctionConnection() ? "<AND>" : "<OR>";
}

bool OrderCondition::conjunctionConnection() const {
	return m_isConjunctionConnection;
}

void OrderCondition::conjunctionConnection(bool isConjunctionConnection) {
	m_isConjunctionConnection = isConjunctionConnection;
}

OrderCondition::OrderConditionType OrderCondition::type() { return m_type; }

OrderCondition *OrderCondition::create(OrderConditionType type) {
	OrderCondition *rval = 0;

	switch (type) {
	case Execution:
		rval = new ExecutionCondition();
		break;

	case Margin:
		rval = new MarginCondition();
		break;

	case PercentChange:
		rval = new PercentChangeCondition();
		break;

	case Price:
		rval = new PriceCondition();
		break;

	case Time:
		rval = new TimeCondition();
		break;

	case Volume:
		rval = new VolumeCondition();
		break;
	}

	if (rval != 0)
		rval->m_type = type;

	return rval;
}
