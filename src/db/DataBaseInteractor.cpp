#include "DataBaseInteractor.h"



static DataBaseInteractor* _instance = 0;


DataBaseInteractor::DataBaseInteractor()
{
	m_DataBaseFullName = "TechmedDB.db";
	m_DataBasePath = ".\\..\\..\\..\\src\\db\\";


	QString l_DataBaseFullPathName = m_DataBasePath+m_DataBaseFullName;
	m_DataBase = QSqlDatabase::addDatabase("QSQLITE",l_DataBaseFullPathName);

	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;
}

DataBaseInteractor::~DataBaseInteractor()
{
}

bool DataBaseInteractor::ConnectDataBase()
{
	if( m_DataBase.isOpen() )
	{
		std::cout << "DataBase is already connected, it will be disconnected and reconnected !" << std::endl ;
		m_DataBase.close() ;
	}

	QString l_DataBaseFullPathName = m_DataBasePath+m_DataBaseFullName;
	m_DataBase.setDatabaseName(l_DataBaseFullPathName);
	bool result = m_DataBase.open() ;

	if( !result)
	{
		std::cout << "DataBase connection error." << std::endl ;
		std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;

		QFile l_File( l_DataBaseFullPathName );
		if( l_File.exists() )
			std::cout << l_DataBaseFullPathName.toStdString() << " file exist." << std::endl ;
		else
			std::cout << l_DataBaseFullPathName.toStdString() << " file does not exist." << std::endl ;
		return false;
	}
	std::cout << "DataBase is connected !" << std::endl ;
	return result ;
}

void DataBaseInteractor::DisconnectDataBase()
{
	if( m_DataBase.isOpen() )
	{
		m_DataBase.close() ;
	}
	std::cout << "DataBase disconnected." << std::endl ;
}

QString DataBaseInteractor::GetDatabaseName()
{
	return m_DataBaseFullName ;
}
bool DataBaseInteractor::SetDatabaseName(QString FullName)
{
	if( FullName.contains(".db") || FullName.contains(".db3") || FullName.contains(".sqlite") )
	{
		m_DataBaseFullName = FullName ;
		return true ;
	}
	else
	{
		std::cout << "Error when setting the Database name, with the name : " << FullName.toStdString() << std::endl ;
		return false ;
	}
}

QString DataBaseInteractor::GetDatabasePath()
{
	return m_DataBasePath ;
}
bool DataBaseInteractor::SetDatabasePath(QString Path)
{
	if( Path.contains("\\") || Path.contains("/") )
	{
		m_DataBasePath = Path ;
		return true ;
	}
	else
	{
		std::cout << "Error when setting the Database path, with the path : " << Path.toStdString() << std::endl ;
		return false ;
	}
}
	


DataBaseInteractor* DataBaseInteractor::Instance()
{
	if(!_instance)
		_instance = new DataBaseInteractor();
	return _instance;
}
void DataBaseInteractor::ReleaseInstance()
{
	_instance->DisconnectDataBase();
	delete _instance;
	_instance = 0;
}


int DataBaseInteractor::UserConnection(QString id, QString psw)
{

	QString query =	"SELECT user_right FROM User WHERE id_user='" + id + "' AND user_passeword='" + psw + "'";
	QSqlQuery response = DataBaseInteractor::Instance()->m_DataBase.exec(query);

	if(response.next())
		return response.value(0).toInt() - SecurityTagGuest;

	return -1;
}

void DataBaseInteractor::FileResearch(unsigned int idPatient,
	unsigned int idFile,
	unsigned int idAuthor)
{

	int resultSize;
	int column;
	bool alreadyDone = false;

	QVariant *fileDesc;
	std::vector<Files> resultTable;

	QString query =	"SELECT id_file, file_url, file_source, file_author, file_patient, file_creation_date, file_last_modification_date, file_md5sum FROM File ";

	column=8;
	fileDesc = new QVariant[column];

	if ( idPatient != 0 )
	{
		if(!alreadyDone)
			query = query + "WHERE ";
		else
			query = query + "AND ";
		query = query +  "file_patient = '" + QString::number(idPatient) + "'";

		alreadyDone = true;
	}

	if ( idFile != 0 )
	{
		if(!alreadyDone)
			query = query + "WHERE ";
		else
			query = query + "AND ";
		query = query +  "id_file = '" + QString::number(idFile) + "'";

		alreadyDone = true;
	}

	if ( idAuthor != 0 )
	{
		if(!alreadyDone)
			query = query + "WHERE ";
		else
			query = query + "AND ";
		query += "file_author = '" + QString::number(idAuthor) + "'";

		alreadyDone = true;
	}

	
	QSqlQuery response = DataBaseInteractor::Instance()->m_DataBase.exec(query);
	
	std::cout << "Query response :" << std::endl;
	while(response.next())
	{
		std::cout << "File !" << std::endl;
		for(int i=0 ; i < column ; i++)
		{
			fileDesc[i]=response.value(i);
		}
		resultTable.push_back(Files(fileDesc));
	}
}