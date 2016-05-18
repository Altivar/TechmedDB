#include "getuserdialog.h"


getuserdialog::getuserdialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{

	ui.setupUi(this);

	m_hasStarted = false;

	connect(ui.pushButton_Start, SIGNAL(clicked()), this, SLOT(OnStartButtonClicked()));

}


getuserdialog::~getuserdialog(void)
{
}

void getuserdialog::OnStartButtonClicked()
{
	m_hasStarted = true;
	close();
}

void getuserdialog::Reset()
{
	m_hasStarted = false;

	ui.checkBox_IdUser->setChecked(false);
	ui.checkBox_lastName->setChecked(false);
	ui.checkBox_firstName->setChecked(false);
	
	ui.lineEdit_IdUser->clear();
	ui.lineEdit_lastName->clear();
	ui.lineEdit_firstName->clear();
}