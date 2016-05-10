#ifndef DATABASEINTERACTOR_H
#define DATABASEINTERACTOR_H

#include <iostream>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <qstring.h>

class DataBaseInteractor
{
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

};

#endif // DATABASEINTERACTOR_H
