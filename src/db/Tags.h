#ifndef TAGS_H
#define TAGS_H

#include <iostream>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <qstring.h>

class Tags
{
private:
	QSqlDatabase *m_DataBasePtr;
	
public:
	Tags();
	~Tags();
};

#endif // TAGS_H
