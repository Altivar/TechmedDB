#ifndef TECHMEDDB_H
#define TECHMEDDB_H

#include <QtGui/QMainWindow>
#include "ui_techmeddb.h"

#include "connectiondialog.h"
#include "getfiledialog.h"
#include "getuserdialog.h"
#include "gettagdialog.h"
#include "PasswordManager.h"
#include "addfiledialog.h"

class TechmedDB : public QMainWindow
{
	Q_OBJECT

public:
	TechmedDB(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TechmedDB();

	

public slots:
	void ConnectionbuttonClicked();
	void GetFileButtonClicked();
	void GetUserButtonClicked();
	void GetTagButtonClicked();
	void ChangePasswordButtonClicked();
	void AddFileButtonClicked();


private:
	void ConnectAsUser(int user);

	Ui::TechmedDBClass ui;

	connectionDialog* m_connectionDialog;
	getfiledialog* m_getfileDialog;
	getuserdialog* m_getuserDialog;
	gettagdialog* m_gettagDialog;
	PasswordManager* m_passwordManager;
	addfiledialog* m_addfileDialog;


	bool m_isFreeVisit;



};

#endif // TECHMEDDB_H
