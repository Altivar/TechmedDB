#ifndef TECHMEDDB_H
#define TECHMEDDB_H

#include <QtGui/QMainWindow>
#include "ui_techmeddb.h"

#include "connectiondialog.h"
#include "getfiledialog.h"
#include "PasswordManager.h"

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

private:
	void ConnectAsUser(int user);

	Ui::TechmedDBClass ui;

	connectionDialog* m_connectionDialog;
	getfiledialog* m_getfileDialog;
	PasswordManager* m_passwordManager;

	bool m_isFreeVisit;



};

#endif // TECHMEDDB_H
