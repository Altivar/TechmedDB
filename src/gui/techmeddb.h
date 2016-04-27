#ifndef TECHMEDDB_H
#define TECHMEDDB_H

#include <QtGui/QMainWindow>
#include "ui_techmeddb.h"

#include "connectiondialog.h"
#include "getfiledialog.h"

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


private:
	void ConnectAsUser(bool user);

	Ui::TechmedDBClass ui;

	connectionDialog* m_connectionDialog;
	getfiledialog* m_getfileDialog;

	bool m_isFreeVisit;


};

#endif // TECHMEDDB_H
