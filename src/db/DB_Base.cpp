#include "DB_Base.h"

DB_Base::DB_Base()
{
	m_DataBasePtr = DataBaseInteractor::Instance()->GetDatabase();
}

DB_Base::~DB_Base()
{
}

QSqlQuery DB_Base::GetFromDB( QString Querry )
{
	return QSqlQuery(Querry) ;
}