#ifndef DATABASEINTERACTOR_H
#define DATABASEINTERACTOR_H

#include <iostream>
#include <QtSql\qsql_sqlite.h>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <QtSql\qsqlerror>
#include <QtSql\qsql_sqlite.h>
#include <qfile.h>
#include <qstring.h>
#include "TDB_DLL_Export.h"

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
	
	int UserConnection(QString id, QString psw);

};

#endif // DATABASEINTERACTOR_H