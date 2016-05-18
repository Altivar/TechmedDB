#include "DB_Base.h"

DB_Base::DB_Base()
{
}

DB_Base::~DB_Base()
{
}

QSqlQuery DB_Base::GetFromDB( QString Querry )
{
	return QSqlQuery(Querry) ;
}