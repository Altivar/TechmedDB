/**
	@File : PasswordManager.h
	@Language : c++
	@Authors :	Fillières Gauthier,
				Aguilar Axel,
				Gaillard Christophe


	@Licence : GNU General Public License

				This file is part of TechmedDB.

				TechmedDB is free software: you can redistribute it and/or modify
				it under the terms of the GNU General Public License as published by
				the Free Software Foundation, either version 3 of the License, or
				(at your option) any later version.

				TechmedDB is distributed in the hope that it will be useful,
				but WITHOUT ANY WARRANTY; without even the implied warranty of
				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
				See the GNU General Public License for more details.

				You should have received a copy of the GNU General Public License
				along with TechmedDB ("gpl_3_0.txt"). If not, see <http://www.gnu.org/licenses/>.
**/
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
