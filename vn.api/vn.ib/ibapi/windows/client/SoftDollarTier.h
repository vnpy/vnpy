#pragma once

class TWSAPIDLLEXP SoftDollarTier
{
	std::string m_name, m_val, m_displayName;

public:
	SoftDollarTier(const std::string& name = "", const std::string& val = "", const std::string& displayName = "");

	std::string name() const;
	std::string val() const;
	std::string displayName() const;

	//·â×°Ìí¼Ó
	bool operator==(const SoftDollarTier & a)
	{
		return a.name() == this->name();
	}

	bool operator!=(const SoftDollarTier & a)
	{
		return a.name() != this->name();
	}
};

