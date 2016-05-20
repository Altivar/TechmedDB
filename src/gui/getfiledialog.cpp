#include "getfiledialog.h"

getfiledialog::getfiledialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	m_hasExit = true;

	connect(ui.pushButton_Start, SIGNAL(clicked()), this, SLOT(LaunchRequest()));
}

getfiledialog::~getfiledialog()
{

}

void getfiledialog::ResetFileDialog()
{
	m_hasExit = true;
}

QStringList getfiledialog::GetTags()
{
	
	QStringList list;
	if(!IsFileTagActive())
		return list;
	
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

void getfiledialog::LaunchRequest()
{
	m_hasExit = false;
	close();
}

