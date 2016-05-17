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
