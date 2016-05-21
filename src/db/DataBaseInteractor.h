/**
	@File : DataBaseInteractor.h
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

#ifndef DATABASEINTERACTOR_H
#define DATABASEINTERACTOR_H

#include <iostream>
#include <vector>
#include <QtSql\qsql_sqlite.h>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <QtSql\qsqlerror>
#include <QtSql\qsql_sqlite.h>
#include <qfile.h>
#include <qstring.h>
#include <qstandarditemmodel.h>
#include "TDB_DLL_Export.h"

#include "Files.h"
#include "Users.h"
#include "Tags.h"

enum USER_RIGHT
{
	ERROR_NO_RIGHT = 0,
	GUEST_USER = 1,
	STANDARD_USER,
	ADMINISTRATOR_USER
};

#if TDB_DLL
class DLLEXPORT DataBaseInteractor
{
#else
class DataBaseInteractor
{
#endif

private:
	QString m_DataBasePath;
	QString m_DataBaseFullName;

	QSqlDatabase m_DataBase;

	QMap<unsigned int,USER_RIGHT> m_UsersRightMap ;
	Users m_CurrentUser ;

	QStandardItemModel *m_ItemModel ;

private:
	DataBaseInteractor();
	~DataBaseInteractor();

public:
	static DataBaseInteractor* Instance();
	static void ReleaseInstance();

	bool ConnectDataBase();
	void DisconnectDataBase();

	QString GetDatabaseName();
	bool SetDatabaseName(QString FullName);
	QString GetDatabasePath();
	bool SetDatabasePath(QString Path);

	bool IsConnected(){ return m_DataBase.isOpen(); }
	QSqlDatabase* GetDatabase(){ return &m_DataBase;}
	
	// get security level of user
	int UserConnection(QString id, QString psw);
	void UserChangePassword(QString oldPsw, QString NewPsw);

	// Queries
	bool FileResearch(const QStringList& tagList, unsigned int idPatient = 0, unsigned int idFile = 0, unsigned int idAuthor = 0);
	bool UserResearch(unsigned int idUser = 0, QString LastName = QString::null, QString FirstName = QString::null );
	unsigned int GetIdByTag(QString tag = QString::null);
	QStringList GetTagById(unsigned int idTag = 0);
	bool AddFile(QString filePath, unsigned int patientId);

	// Getter to the QStandardItemModel to set to the QTableView in the ui if a query is ok, to set the result in the tableview
	QStandardItemModel* GetItemModel(){ return m_ItemModel ; }

};

#endif // DATABASEINTERACTOR_H