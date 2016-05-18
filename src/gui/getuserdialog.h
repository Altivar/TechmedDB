#ifndef GETUSERDIALOG_H
#define GETUSERDIALOG_H

#include <QtGui/QDialog>
#include "ui_getuserdialog.h"



class getuserdialog : public QDialog
{

	Q_OBJECT

public:
	getuserdialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~getuserdialog(void);
	
	bool HasBeenStarted() { return m_hasStarted; }
	void Reset();


public slots:
	void OnStartButtonClicked();

private:
	Ui::getuserdialogClass ui;

	bool m_hasStarted;



};

#endif // GETUSERDIALOG_H