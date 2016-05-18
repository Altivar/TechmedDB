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
#include "TDB_DLL_Export.h"

#include "Files.h"
#include "Users.h"

enum RightAccess
{
	Visitor = 0,
	Contributor,
	Admin
};

const int SecurityTagGuest = 13;


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

	// Querry
	bool FileResearch(unsigned int idPatient = 0, unsigned int idFile = 0, unsigned int idAuthor = 0 );
	bool UserResearch(unsigned int idUser = 0, QString LastName = QString::null, QString FirstName = QString::null );

};

#endif // DATABASEINTERACTOR_H