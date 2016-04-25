#include "DataBaseInteractor.h"


static DataBaseInteractor* _instance = 0;


DataBaseInteractor::DataBaseInteractor()
{
}

DataBaseInteractor::~DataBaseInteractor()
{
}
	


DataBaseInteractor* DataBaseInteractor::Instance()
{
	if(!_instance)
		_instance = new DataBaseInteractor();
	return _instance;
}
void DataBaseInteractor::ReleaseInstance()
{
	delete _instance;
	_instance = 0;
}
