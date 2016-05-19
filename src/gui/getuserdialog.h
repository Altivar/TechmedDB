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

	bool IsIDChecked() { return ui.checkBox_IdUser->isChecked(); }
	bool IsLastNameChecked() { return ui.checkBox_lastName->isChecked(); }
	bool IsFirstNameChecked() { return ui.checkBox_firstName->isChecked(); }

	unsigned int GetID() { return ui.lineEdit_IdUser->text().toUInt(); }
	QString GetLastName() { return ui.lineEdit_lastName->text(); }
	QString GetFirstName() { return ui.lineEdit_firstName->text(); }

public slots:
	void OnStartButtonClicked();

private:
	Ui::getuserdialogClass ui;

	bool m_hasStarted;



};

#endif // GETUSERDIALOG_H