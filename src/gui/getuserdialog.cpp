#include "getuserdialog.h"


getuserdialog::getuserdialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{

	ui.setupUi(this);

	m_hasStarted = false;

}


getuserdialog::~getuserdialog(void)
{
}

void getuserdialog::OnStartButtonClicked()
{
	m_hasStarted = true;
}

void getuserdialog::Reset()
{
	
}