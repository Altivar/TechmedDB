#include "connectiondialog.h"

connectionDialog::connectionDialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	
	ui.setupUi(this);

	m_id = "";
	ResetDialog();

	connect(ui.pushButton_Connect, SIGNAL(clicked()), this, SLOT(ConnectButtonClicked()));
	connect(ui.pushButton_Free, SIGNAL(clicked()), this, SLOT(FreeButtonClicked()));

}

connectionDialog::~connectionDialog()
{

}

void connectionDialog::ResetDialog()
{
	m_password = "";
	ui.lineEdit_Password->setText("");
	m_isFreeVisitSelected = false;
}

void connectionDialog::ConnectButtonClicked()
{
	m_id = ui.lineEdit_Id->text();
	m_password = ui.lineEdit_Password->text();
	this->close();
}

void connectionDialog::FreeButtonClicked()
{
	m_isFreeVisitSelected = true;
	this->close();
}