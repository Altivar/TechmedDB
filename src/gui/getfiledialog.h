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

private:
	Ui::getfiledialogClass ui;
};

#endif // GETFILEDIALOG_H
