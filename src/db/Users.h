/**
	@File : Users.h
	@Language : c++
	@Authors :	Fillières Gauthier,
				Aguilar Axel,
				Gaillard Christophe


	@Licence : GNU General Public License

				This file is part of TechmedDB.

				TechmedDB is free software: you can redistribute it and/or modify
				it under the terms of the GNU General Public License as published by
				the Free Software Foundation, either version 3 of the License, or
				(at your option) any later version.

				TechmedDB is distributed in the hope that it will be useful,
				but WITHOUT ANY WARRANTY; without even the implied warranty of
				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
				See the GNU General Public License for more details.

				You should have received a copy of the GNU General Public License
				along with TechmedDB ("gpl_3_0.txt"). If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef USERS_H
#define USERS_H

#include "DB_Base.h"

class Users : public DB_Base
{
private:
	unsigned int m_UserID;
	QPair<unsigned int,QString> m_UserGroupRefAndName;
	QPair<unsigned int,QString> m_UserRightRefAndName;

	QString m_UserFirstName ;
	QString m_UserLastName;
	QString m_UserPassword;
	QString m_UserDescription;

	QMap<unsigned int,QString> m_UserTags;

	void BuildUserTagsMap();


public:
	Users();
	Users(unsigned int ID, QString FirstName, QString LastName, QPair<unsigned int,QString> Group, QPair<unsigned int,QString> Right, QString Password, QString Desc);
	~Users();

	unsigned int GetUserId(){ return m_UserID;}
	QString GetFirstName(){ return m_UserFirstName;}
	QString GetLastName(){ return m_UserLastName;}
	QString GetUserDescription(){ return m_UserDescription;}
	unsigned int GetUserRightCode(){ return m_UserRightRefAndName.first;}
	unsigned int GetUserGroupId(){ return m_UserGroupRefAndName.first;}
	QMap<unsigned int,QString> GetUserTags() { return m_UserTags; }

	/*QVector<Users> GetUserByNames(QString LastName, QString FirstName);
	QVector<Users> GetUserById(unsigned int id);*/


	//virtual QSqlQuery GetAllTable(){ return QSqlQuery("SELECT * FROM " + this->m_TABLENAME ); }
};

#endif // USERS_H
