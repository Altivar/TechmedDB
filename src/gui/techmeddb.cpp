#include "techmeddb.h"

#include "../db/DataBaseInteractor.h"

#include <iostream>

TechmedDB::TechmedDB(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	m_connectionDialog = new connectionDialog(this);
	ConnectionbuttonClicked();
	
	
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

}