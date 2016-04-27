#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <qstring.h>
#include <qmap.h>
#include <qvector.h>
#include <qpair.h>

class Users
{
private:
	QSqlDatabase *m_DataBasePtr;

	unsigned int m_UserID;
	QPair<unsigned int,QString> m_UserGroupRefAndName;
	QPair<unsigned int,QString> m_UserRightRefAndName;

	QString m_UserFirstName; 
	QString m_UserLastName;
	QString m_UserPassword;
	QString m_UserDescription;

	QMap<unsigned int,QString> m_UserTags;


public:
	Users();
	~Users();
};

#endif // USERS_H
