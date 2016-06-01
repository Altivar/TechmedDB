/**
	@File : connectiondialog.h
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
#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QtGui/QDialog>
#include <qstring.h>


#include "ui_connectionDialog.h"

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
