#include "techmeddb.h"
#include "../db/DataBaseInteractor.h"

TechmedDB::TechmedDB(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);


}

TechmedDB::~TechmedDB()
{
	DataBaseInteractor::ReleaseInstance();
}
