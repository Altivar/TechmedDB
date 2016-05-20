#include "PasswordManager.h"

#include <qmessagebox.h>

PasswordManager::PasswordManager(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	m_isValidated = false;

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(OnOkButtonClicked()));
	connect(ui.lineEdit_newPsw, SIGNAL(textChanged(const QString&)), this, SLOT(NewPasswordChanged(const QString&)));
	connect(ui.lineEdit_newPsw2, SIGNAL(textChanged(const QString&)), this, SLOT(NewPasswordChanged(const QString&)));


}


PasswordManager::~PasswordManager(void)
{
}

void PasswordManager::Reset()
{
	m_isValidated = false;
	ui.label_content->setPixmap(QPixmap("./images/pascontent.png"));
	ui.lineEdit_newPsw->clear();
	ui.lineEdit_newPsw2->clear();
	ui.lineEdit_currentPsw->clear();
}

void PasswordManager::OnOkButtonClicked()
{
	if(ui.lineEdit_newPsw->text() != ui.lineEdit_newPsw2->text())
	{
		QMessageBox::warning(this, "Password", "Your new password and the confirmation are different !");
		Reset();
		return;
	}
	if(ui.lineEdit_newPsw->text().count() < 4)
	{
		QMessageBox::warning(this, "Password", "Your new password must be at least 4 caracters long !");
		Reset();
		return;
	}

	m_isValidated = true;
}

void PasswordManager::NewPasswordChanged(const QString & text)
{
	
	if(ui.lineEdit_newPsw->text() != ui.lineEdit_newPsw2->text() || ui.lineEdit_newPsw->text().count() < 4)
	{
		ui.label_content->setPixmap(QPixmap("./images/pascontent.png"));
	}
	else if(ui.lineEdit_newPsw->text().count() < 7)
	{
		ui.label_content->setPixmap(QPixmap("./images/moyencontent.png"));
	}
	else
	{
		ui.label_content->setPixmap(QPixmap("./images/content.png"));
	}

}


