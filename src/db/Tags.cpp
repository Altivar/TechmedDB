#include "Tags.h"


Tag::Tag()
	: DB_Base()
{
	m_id = 0;
	m_name = "";
	m_type = 0;
	m_reference = 0;
}

Tag::Tag(unsigned int id, QString name, unsigned int type, unsigned int reference)
	: DB_Base()
	, m_id(id)
	, m_name(name)
	, m_type(type)
	, m_reference(reference)
{
}

Tag::~Tag()
{
}