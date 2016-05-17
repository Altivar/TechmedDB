#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqlrecord.h>
#include <QtSql\qsqltablemodel>
#include <qstring.h>
#include <qmap.h>
#include <qvector.h>
#include <qpair.h>
#include "DB_Base.h"

class Users : DB_Base
{
private:
	unsigned int m_UserID;
	QPair<unsigned int,QString> m_UserGroupRefAndName;
	QPair<unsigned int,QString> m_UserRightRefAndName;

	QString m_UserFirstName; 
	QString m_UserLastName;
	QString m_UserPassword;
	QString m_UserDescription;

	QMap<unsigned int,QString> m_UserTags;

	void BuildUserTagsMap();


public:
	Users();
	Users(unsigned int ID, QString FirstName, QString LastName, QPair<unsigned int,QString> Group, QPair<unsigned int,QString> Right, QString Password, QString Desc);
	~Users();

	QString GetFirstName(){ return m_UserFirstName;}
	QString GetLastName(){ return m_UserLastName;}
	QMap<unsigned int,QString> GetUserTags() { return m_UserTags; }

	QVector<Users> GetUserByNames(QString FirstName, QString LasName);
	QVector<Users> GetUserById(unsigned int id);
};

#endif // USERS_H
