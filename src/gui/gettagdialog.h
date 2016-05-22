/**
	@File : gettagdialog.h
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
#ifndef GETTAGDIALOG_H
#define GETTAGDIALOG_H

#include <QtGui/QDialog>
#include "ui_gettagdialog.h"


class gettagdialog : public QDialog
{

	Q_OBJECT

public:
	gettagdialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~gettagdialog(void);

	void Reset();

	QString GetTag() { return ui.lineEdit_tag->text(); }

public slots:
	void OnStartButtonClicked();

private:
	Ui::tagSearchDialog ui;

	bool m_hasStarted;

};

#endif // GETTAGDIALOG_H

