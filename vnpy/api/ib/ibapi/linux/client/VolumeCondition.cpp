#include "StdAfx.h"
#include "VolumeCondition.h"
#include <sstream>

std::string VolumeCondition::valueToString() const {
	std::stringstream tmp;

	tmp << m_volume;

	return tmp.str();
}

void VolumeCondition::valueFromString(const std::string & v) {
	std::stringstream tmp;

	tmp << v;
	tmp >> m_volume;
}

int VolumeCondition::volume() {
	return m_volume;
}

void VolumeCondition::volume(int volume) {
	m_volume = volume;
}
