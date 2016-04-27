#ifndef TECHMEDDB_H
#define TECHMEDDB_H

#include <QtGui/QMainWindow>
#include "ui_techmeddb.h"

#include "connectiondialog.h"

class TechmedDB : public QMainWindow
{
	Q_OBJECT

public:
	TechmedDB(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TechmedDB();

public slots:
	void ConnectionbuttonClicked();

private:
	Ui::TechmedDBClass ui;

	connectionDialog* m_connectionDialog;

	bool m_isFreeVisit;


};

#endif // TECHMEDDB_H
