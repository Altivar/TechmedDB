/**
	@File : getfiledialog.h
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
#ifndef GETFILEDIALOG_H
#define GETFILEDIALOG_H

#include <QtGui/QDialog>
#include "ui_getfiledialog.h"

class getfiledialog : public QDialog
{
	Q_OBJECT

public:
	getfiledialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~getfiledialog();

	void ResetFileDialog();

	bool IsFileTagActive() { return ui.checkBox_TagsFile->isChecked(); }
	bool IsPatientIDActive() { return ui.checkBox_IdPatient->isChecked(); }
	bool IsFileIDActive() { return ui.checkBox_IdFile->isChecked(); }
	bool IsAuthorIDActive() { return ui.checkBox_IdAuthor->isChecked(); } 

	QStringList GetTags();
	unsigned int GetPatientID();
	unsigned int GetFileID();
	unsigned int GetAuthorID();

	bool HasExit() { return m_hasExit; }

public slots:
	void LaunchRequest();

private:
	Ui::getfiledialogClass ui;

	bool m_hasExit;

};

#endif // GETFILEDIALOG_H
