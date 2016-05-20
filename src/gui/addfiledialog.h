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
