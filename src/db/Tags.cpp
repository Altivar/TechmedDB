#include "Tags.h"


Tags::Tags()
	: DB_Base()
{
	m_id = 0;
	m_name = "";
	m_type = 0;
	m_reference = 0;
}

Tags::Tags(unsigned int id, QString name, unsigned int type, unsigned int reference) :
DB_Base(),
m_id(id),
m_name(name),
m_type(type),
m_reference(reference)
{
}

Tags::~Tags()
{
}