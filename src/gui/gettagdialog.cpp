#include "gettagdialog.h"


gettagdialog::gettagdialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	
	ui.setupUi(this);

	m_hasStarted = false;

	connect(ui.pushButton_Start, SIGNAL(clicked()), this, SLOT(OnStartButtonClicked()));

}


gettagdialog::~gettagdialog(void)
{
}

void gettagdialog::OnStartButtonClicked()
{
	m_hasStarted = true;
	close();
}

void gettagdialog::Reset()
{
	m_hasStarted = false;
	ui.lineEdit_tag->clear();
}
