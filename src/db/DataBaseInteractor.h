#ifndef DATABASEINTERACTOR_H
#define DATABASEINTERACTOR_H



class DataBaseInteractor
{
	
private:
	DataBaseInteractor();
	~DataBaseInteractor();

public:
	static DataBaseInteractor* Instance();
	static void ReleaseInstance();

};

#endif // DATABASEINTERACTOR_H
