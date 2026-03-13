#include<sstream>
#include"Vec2.hpp"

class Action
{
	std::string m_name = "NONE";
	std::string m_type = "NONE";
	Vec2		m_pos = Vec2(0, 0);

public:

	Action() = default;

	Action(const std::string& name, const std::string& type)
		: m_name(name)
		, m_type(type)
	{}

	Action(const std::string& name, Vec2 pos)
		: m_name(name)
		, m_pos(pos)
	{}

	Action(const std::string& name, const std::string& type, Vec2 pos)
		: m_name(name)
		, m_type(type)
		, m_pos(pos)
	{}

	

	const std::string& name() const
	{
		return m_name;
	}
	
	const std::string& type() const
	{
		return m_type;
	}

	const Vec2& pos() const
	{
		return m_pos;
	}

	std::string Action::toString() const
	{
		std::stringstream ss;
		ss << name() << " " << type() << " " << (int)m_pos.x << " " << (int)m_pos.y ;
		return ss.str();
	}
};