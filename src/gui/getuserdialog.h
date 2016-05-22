/**
	@File : getuserdialog.h
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