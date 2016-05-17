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
void TechmedDB::ConnectAsUser(int user)
{
	ui.pushButton_gettag->setVisible(user > 0);
	ui.pushButton_getuser->setVisible(user > 0);
	ui.label_set->setVisible(user > 0);
	ui.pushButton_setfile->setVisible(user > 0);
	ui.pushButton_settag->setVisible(user > 0);
	ui.pushButton_setuser->setVisible(user > 1);
	ui.line->setVisible(user > 0);
	ui.line_2->setVisible(user > 0);	
	ui.pushButton_changepassword->setVisible(user > 0);
}


//////////////////////////////////////////////////
/////              PUBLIC SLOTS              /////
//////////////////////////////////////////////////
void TechmedDB::ConnectionbuttonClicked()
{
	
	bool isConnected = false;
	int result = 0;
	do
	{
		m_connectionDialog->ResetDialog();
		m_connectionDialog->exec();

		if(m_connectionDialog->IsFreeVisitSelected())
			break;

		// test connection here
		result = DataBaseInteractor::Instance()->UserConnection(m_connectionDialog->GetConnectionId(), m_connectionDialog->GetConnectionPassword());
		std::cout << result << std::endl;

		if(result == -1)
			continue;

		isConnected = true;
		
	}
	while(m_connectionDialog->IsFreeVisitSelected() != true && !isConnected);


	// update application mode
	m_isFreeVisit = m_connectionDialog->IsFreeVisitSelected();
	if(m_isFreeVisit)
	{
		ui.actionConnect->setText("Connexion");
	}
	else
	{
		ui.actionConnect->setText("Changer d'utilisateur");
	}
	
	ConnectAsUser(result);
	


}

void TechmedDB::GetFileButtonClicked()
{

	m_getfileDialog->ResetFileDialog();
	m_getfileDialog->exec();

	std::cout << std::endl << "Get file dialog : " << std::endl;
	std::cout << "File Tag : " << ((m_getfileDialog->IsFileTagActive())?"Checked":"Not checked") << std::endl;
	std::cout << "Patient ID : " << ((m_getfileDialog->IsPatientIDActive())?"Checked":"Not checked") << std::endl;
	std::cout << "File ID : " << ((m_getfileDialog->IsFileIDActive())?"Checked":"Not checked") << std::endl;
	std::cout << "Author ID : " << ((m_getfileDialog->IsAuthorIDActive())?"Checked":"Not checked") << std::endl << std::endl;

	if(m_getfileDialog->HasExit())
		return;

	DataBaseInteractor::Instance()->FileResearch(
		((m_getfileDialog->IsPatientIDActive())?m_getfileDialog->GetPatientID():0),
		((m_getfileDialog->IsFileIDActive())?m_getfileDialog->GetFileID():0),
		((m_getfileDialog->IsAuthorIDActive())?m_getfileDialog->GetAuthorID():0));



}

void TechmedDB::GetUserButtonClicked()
{

}

void TechmedDB::GetTagButtonClicked()
{

}
