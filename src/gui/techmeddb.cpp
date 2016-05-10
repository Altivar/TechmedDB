#include "techmeddb.h"

#include "../db/DataBaseInteractor.h"

#include <iostream>

TechmedDB::TechmedDB(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
		
	DataBaseInteractor::Instance()->ConnectDataBase();
	ui.setupUi(this);


	m_isFreeVisit = false;


	m_connectionDialog = new connectionDialog(this);
	ConnectionbuttonClicked();
	m_getfileDialog = new getfiledialog(this);
	
	connect(ui.actionConnect, SIGNAL(triggered()), this, SLOT(ConnectionbuttonClicked()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(close()));

	connect(ui.pushButton_getfile, SIGNAL(clicked()), this, SLOT(GetFileButtonClicked()));
	connect(ui.pushButton_getuser, SIGNAL(clicked()), this, SLOT(GetUserButtonClicked()));
	connect(ui.pushButton_gettag, SIGNAL(clicked()), this, SLOT(GetTagButtonClicked()));

}

TechmedDB::~TechmedDB()
{
	DataBaseInteractor::ReleaseInstance();
}



//////////////////////////////////////////////////
/////            PRIVATE METHODS             /////
//////////////////////////////////////////////////
void TechmedDB::ConnectAsUser(bool user)
{
	ui.pushButton_gettag->setVisible(user);
	ui.pushButton_getuser->setVisible(user);
	ui.label_set->setVisible(user);
	ui.pushButton_setfile->setVisible(user);
	ui.pushButton_settag->setVisible(user);
	ui.pushButton_setuser->setVisible(user);
	ui.line->setVisible(user);
	ui.line_2->setVisible(user);
	ui.pushButton_changepassword->setVisible(user);
}


//////////////////////////////////////////////////
/////              PUBLIC SLOTS              /////
//////////////////////////////////////////////////
void TechmedDB::ConnectionbuttonClicked()
{
	
	bool isConnected = false;
	do
	{
		m_connectionDialog->ResetDialog();
		m_connectionDialog->exec();

		// test connection here

	}
	while(m_connectionDialog->IsFreeVisitSelected() != true);


	// update application mode
	m_isFreeVisit = m_connectionDialog->IsFreeVisitSelected();
	if(m_isFreeVisit)
		ui.actionConnect->setText("Connexion");
	else
		ui.actionConnect->setText("Changer d'utilisateur");

	//ConnectAsUser(!m_isFreeVisit);


}

void TechmedDB::GetFileButtonClicked()
{
	m_getfileDialog->exec();
}

void TechmedDB::GetUserButtonClicked()
{

}

void TechmedDB::GetTagButtonClicked()
{

}
