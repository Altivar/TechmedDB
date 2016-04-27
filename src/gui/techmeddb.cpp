#include "techmeddb.h"

#include "../db/DataBaseInteractor.h"

#include <iostream>

TechmedDB::TechmedDB(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);


	m_isFreeVisit = false;


	m_connectionDialog = new connectionDialog(this);
	ConnectionbuttonClicked();
	
	connect(ui.actionConnect, SIGNAL(triggered()), this, SLOT(ConnectionbuttonClicked()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(close()));

}

TechmedDB::~TechmedDB()
{
	DataBaseInteractor::ReleaseInstance();
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


}