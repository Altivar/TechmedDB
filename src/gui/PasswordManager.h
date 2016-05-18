#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QtGui/QDialog>
#include "ui_changePswDialog.h"


class PasswordManager : public QDialog
{

	Q_OBJECT

public:
	PasswordManager(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PasswordManager(void);

	QString GetCurrentPassword() { return ui.lineEdit_currentPsw->text(); }
	QString GetNewPassword() { return ui.lineEdit_newPsw->text(); }

	bool HasBeenValidated() { return m_isValidated; }

	void Reset();

public slots:
	void OnOkButtonClicked();
	void NewPasswordChanged(const QString & text);

private:
	Ui::changePswDialogClass ui;

	bool m_isValidated;
	
};


#endif // PASSWORDMANAGER_H
