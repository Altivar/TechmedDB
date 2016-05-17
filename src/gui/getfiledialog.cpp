#include "getfiledialog.h"

getfiledialog::getfiledialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	connect(ui.pushButton_Start, SIGNAL(clicked()), this, SLOT(close()));
}

getfiledialog::~getfiledialog()
{

}


QStringList getfiledialog::GetTags()
{
	QStringList list;
	if(!ui.lineEdit_Tag1->text().trimmed().isEmpty())
		list.append(ui.lineEdit_Tag1->text().trimmed());
	if(!ui.lineEdit_Tag2->text().trimmed().isEmpty())
		list.append(ui.lineEdit_Tag2->text().trimmed());
	if(!ui.lineEdit_Tag3->text().trimmed().isEmpty())
		list.append(ui.lineEdit_Tag3->text().trimmed());

	return list;
}

unsigned int getfiledialog::GetPatientID()
{
	bool ok;
	unsigned int id = ui.lineEdit_IdPatient->text().toUInt(&ok,10);
	if(ok)
		return id;
	
	return 0;
}

unsigned int getfiledialog::GetFileID()
{
	bool ok;
	unsigned int id = ui.lineEdit_IdFile->text().toUInt(&ok,10);
	if(ok)
		return id;
	
	return 0;
}

unsigned int getfiledialog::GetAuthorID()
{
	bool ok;
	unsigned int id = ui.lineEdit_IdAuthor->text().toUInt(&ok,10);
	if(ok)
		return id;
	
	return 0;
}



