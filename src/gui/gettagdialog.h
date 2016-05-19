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

