#include "techmeddb.h"

#include "../db/DataBaseInteractor.h"

#include <qmessagebox.h>
#include <qsizepolicy.h>

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
			result = GUEST_USER;
		else
		{
			// test connection here
			result = DataBaseInteractor::Instance()->UserConnection(m_connectionDialog->GetConnectionId(), m_connectionDialog->GetConnectionPassword());
		}
		switch( result )
		{
		case ERROR_NO_RIGHT :
			std::cout << "Not Connected" << std::endl;
			continue;
			break;
		case GUEST_USER :
			std::cout << "Connected as guest user" << std::endl;
			isConnected = true;
			break;
		case STANDARD_USER :
			std::cout << "Connected as standard user" << std::endl;
			break;
		case ADMINISTRATOR_USER :
			std::cout << "Connected as administrator" << std::endl;
			break;
		}
		

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

	if( DataBaseInteractor::Instance()->FileResearch(	m_getfileDialog->GetTags(),
														((m_getfileDialog->IsPatientIDActive())?m_getfileDialog->GetPatientID():0),
														((m_getfileDialog->IsFileIDActive())?m_getfileDialog->GetFileID():0),
														((m_getfileDialog->IsAuthorIDActive())?m_getfileDialog->GetAuthorID():0)) )
	{
		ui.QueryView->setModel( DataBaseInteractor::Instance()->GetItemModel() ) ;
		ui.QueryView->resizeColumnsToContents();
		ui.QueryView->setEditTriggers( QAbstractItemView::NoEditTriggers ) ;
		ui.QueryView->update() ;
		ui.QueryView->show() ;
	}



}

void TechmedDB::GetUserButtonClicked()
{
	
	m_getuserDialog->Reset();
	m_getuserDialog->exec();

	if(!m_getuserDialog->HasBeenStarted())
		return;

	// request
	if( DataBaseInteractor::Instance()->UserResearch(
													((m_getuserDialog->IsIDChecked())?m_getuserDialog->GetID():0),
													((m_getuserDialog->IsLastNameChecked())?m_getuserDialog->GetLastName():""),
													((m_getuserDialog->IsFirstNameChecked())?m_getuserDialog->GetFirstName():"")) )
	{
		ui.QueryView->setModel( DataBaseInteractor::Instance()->GetItemModel() ) ;
		ui.QueryView->resizeColumnsToContents();
		ui.QueryView->setEditTriggers( QAbstractItemView::NoEditTriggers ) ;
		ui.QueryView->update() ;
		ui.QueryView->show() ;
	}
}

void TechmedDB::GetTagButtonClicked()
{

	m_gettagDialog->Reset();
	m_gettagDialog->exec();

	bool ok;
	unsigned int id = m_gettagDialog->GetTag().toUInt(&ok, 10);
	if( m_gettagDialog->GetTag().isEmpty() )
	{
		if( DataBaseInteractor::Instance()->GetTags() )
		{
			ui.QueryView->setModel( DataBaseInteractor::Instance()->GetItemModel() ) ;
			ui.QueryView->resizeColumnsToContents();
			ui.QueryView->setEditTriggers( QAbstractItemView::NoEditTriggers ) ;
			ui.QueryView->update() ;
			ui.QueryView->show() ;
		}
	}
	else
	{
		if(ok)
		{
			if( DataBaseInteractor::Instance()->GetTagById(id) )
			{
				ui.QueryView->setModel( DataBaseInteractor::Instance()->GetItemModel() ) ;
				ui.QueryView->resizeColumnsToContents();
				ui.QueryView->setEditTriggers( QAbstractItemView::NoEditTriggers ) ;
				ui.QueryView->update() ;
				ui.QueryView->show() ;
			}
		}
		else
		{
			unsigned int tagid = DataBaseInteractor::Instance()->GetIdByTag(m_gettagDialog->GetTag());
			std::cout << "Id : " << tagid << std::endl;

			if( DataBaseInteractor::Instance()->GetTagById(tagid) )
			{
				ui.QueryView->setModel( DataBaseInteractor::Instance()->GetItemModel() ) ;
				ui.QueryView->resizeColumnsToContents();
				ui.QueryView->setEditTriggers( QAbstractItemView::NoEditTriggers ) ;
				ui.QueryView->update() ;
				ui.QueryView->show() ;
			}
		}
	}

}

void TechmedDB::ChangePasswordButtonClicked()
{
	m_passwordManager->Reset();
	m_passwordManager->exec();

	if(m_passwordManager->HasBeenValidated())
		DataBaseInteractor::Instance()->UserChangePassword( m_passwordManager->GetCurrentPassword(), m_passwordManager->GetNewPassword() ) ;
}

void TechmedDB::AddFileButtonClicked()
{
	m_addfileDialog->Reset();
	m_addfileDialog->exec();

	if(!m_addfileDialog->HasBenValidated())
		return;

	DataBaseInteractor::Instance()->AddFile(m_addfileDialog->GetFileOrFolderPath(), m_addfileDialog->GetPatientId());

	QMessageBox::about(this, "Add file", "Data has been added to database");
}

