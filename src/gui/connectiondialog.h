#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QtGui/QDialog>
#include <qstring.h>


#include "ui_connectiondialog.h"

class connectionDialog : public QDialog
{
	Q_OBJECT

public:
	connectionDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~connectionDialog();

	QString GetConnectionId() { return m_id; }
	QString GetConnectionPassword() { return m_password; }
	bool IsFreeVisitSelected() { return m_isFreeVisitSelected; }

	void ResetDialog();

public slots:
	void FreeButtonClicked();
	void ConnectButtonClicked();


private:
	Ui::Dialog ui;

	QString m_id;
	QString m_password;
	bool m_isFreeVisitSelected;


};

#endif // CONNECTIONDIALOG_H
