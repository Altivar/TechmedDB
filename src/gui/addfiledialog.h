/**
	@File : addfiledialog.h
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
#ifndef ADDFILEDIALOG_H
#define ADDFILEDIALOG_H

#include <QtGui/QDialog>
#include <qstring.h>


#include "ui_addfiledialog.h"

class addfiledialog : public QDialog
{
	Q_OBJECT

public:
	addfiledialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~addfiledialog();

	void Reset();
	void SetFolderIcon(QString path);
	void SetFileIcon(QString path);

	bool HasBenValidated() { return m_isValidated; }

	unsigned int GetPatientId() { return m_patientId; }
	QString GetFileOrFolderPath() { return ui.lineEdit_filePath->text(); }

public slots:
	void OnOkButtonClicked();
	void OnFileButtonClicked();
	void OnFolderButtonClicked();

private:
	Ui::addfileDialog ui;

	bool m_isValidated;

	unsigned int m_patientId;

};

#endif // ADDFILEDIALOG_H
