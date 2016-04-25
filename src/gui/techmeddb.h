#ifndef TECHMEDDB_H
#define TECHMEDDB_H

#include <QtGui/QMainWindow>
#include "ui_techmeddb.h"

class TechmedDB : public QMainWindow
{
	Q_OBJECT

public:
	TechmedDB(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TechmedDB();

private:
	Ui::TechmedDBClass ui;
};

#endif // TECHMEDDB_H
