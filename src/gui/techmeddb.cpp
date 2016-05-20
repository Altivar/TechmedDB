#include "techmeddb.h"

#include "../db/DataBaseInteractor.h"

#include <qmessagebox.h>

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
	m_getuserDialog = new getuserdialog(this);
	m_gettagDialog = new gettagdialog(this);
	m_passwordManager = new PasswordManager(this);
	m_addfileDialog = new addfiledialog(this);
	m_addfileDialog->SetFolderIcon("./images/folder.png");
	m_addfileDialog->SetFileIcon("./images/file.png");
	
	connect(ui.actionConnect, SIGNAL(triggered()), this, SLOT(ConnectionbuttonClicked()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(close()));

	connect(ui.pushButton_getfile, SIGNAL(clicked()), this, SLOT(GetFileButtonClicked()));
	connect(ui.pushButton_getuser, SIGNAL(clicked()), this, SLOT(GetUserButtonClicked()));
	connect(ui.pushButton_gettag, SIGNAL(clicked()), this, SLOT(GetTagButtonClicked()));
	connect(ui.pushButton_changepassword, SIGNAL(clicked()), this, SLOT(ChangePasswordButtonClicked()));
	connect(ui.pushButton_setfile, SIGNAL(clicked()), this, SLOT(AddFileButtonClicked()));
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
	ui.pushButton_gettag->setVisible(user >= STANDARD_USER);
	ui.pushButton_getuser->setVisible(user >= STANDARD_USER);
	ui.label_set->setVisible(user >= STANDARD_USER);
	ui.pushButton_setfile->setVisible(user >= STANDARD_USER);
	ui.pushButton_settag->setVisible(user >= STANDARD_USER);
	ui.pushButton_setuser->setVisible(user >= ADMINISTRATOR_USER);
	ui.line->setVisible(user >= STANDARD_USER);
	ui.line_2->setVisible(user >= STANDARD_USER);	
	ui.pushButton_changepassword->setVisible(user >= STANDARD_USER);
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

		if(result == ERROR_NO_RIGHT)
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
		m_getfileDialog->GetTags(),
		((m_getfileDialog->IsPatientIDActive())?m_getfileDialog->GetPatientID():0),
		((m_getfileDialog->IsFileIDActive())?m_getfileDialog->GetFileID():0),
		((m_getfileDialog->IsAuthorIDActive())?m_getfileDialog->GetAuthorID():0));



}

void TechmedDB::GetUserButtonClicked()
{
	
	m_getuserDialog->Reset();
	m_getuserDialog->exec();

	if(!m_getuserDialog->HasBeenStarted())
		return;

	// request
	DataBaseInteractor::Instance()->UserResearch(
		((m_getuserDialog->IsIDChecked())?m_getuserDialog->GetID():0),
		((m_getuserDialog->IsLastNameChecked())?m_getuserDialog->GetLastName():""),
		((m_getuserDialog->IsFirstNameChecked())?m_getuserDialog->GetFirstName():""));

}

void TechmedDB::GetTagButtonClicked()
{

	m_gettagDialog->Reset();
	m_gettagDialog->exec();

	bool ok;
	unsigned int id = m_gettagDialog->GetTag().toUInt(&ok, 10);
	if(ok)
	{
		QStringList list = DataBaseInteractor::Instance()->GetTagById(id);
		std::cout << "Tags found :" << std::endl;
		for(int i = 0; i < list.size(); i++)
		{
			std::cout << list.at(i).toStdString() << std::endl;
		}
	}
	else
	{
		unsigned int tagid = DataBaseInteractor::Instance()->GetIdByTag(m_gettagDialog->GetTag());
		std::cout << "Id : " << tagid << std::endl;
	}


}

void TechmedDB::ChangePasswordButtonClicked()
{
	m_passwordManager->Reset();
	m_passwordManager->exec();

	DataBaseInteractor::Instance()->UserChangePassword( m_passwordManager->GetCurrentPassword(), m_passwordManager->GetNewPassword() ) ;
}

void TechmedDB::AddFileButtonClicked()
{
	m_addfileDialog->Reset();
	m_addfileDialog->exec();


}
