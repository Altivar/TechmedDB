/**
	@File : Techmeddb.h
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

#ifndef TECHMEDDB_H
#define TECHMEDDB_H

#include <QtGui/QMainWindow>
#include "ui_techmeddb.h"

#include "connectiondialog.h"
#include "getfiledialog.h"
#include "getuserdialog.h"
#include "gettagdialog.h"
#include "PasswordManager.h"
#include "addfiledialog.h"

class TechmedDB : public QMainWindow
{
	Q_OBJECT

public:
	TechmedDB(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TechmedDB();

	

public slots:
	void ConnectionbuttonClicked();
	void GetFileButtonClicked();
	void GetUserButtonClicked();
	void GetTagButtonClicked();
	void ChangePasswordButtonClicked();
	void AddFileButtonClicked();


private:
	void ConnectAsUser(int user);

	Ui::TechmedDBClass ui;

	connectionDialog* m_connectionDialog;
	getfiledialog* m_getfileDialog;
	getuserdialog* m_getuserDialog;
	gettagdialog* m_gettagDialog;
	PasswordManager* m_passwordManager;
	addfiledialog* m_addfileDialog;


	bool m_isFreeVisit;



};

#endif // TECHMEDDB_H
