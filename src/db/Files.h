#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <qstring.h>

class Files
{
private:
	QSqlDatabase *m_DataBasePtr;
	
public:
	Files();
	~Files();
};

#endif // FILES_H
