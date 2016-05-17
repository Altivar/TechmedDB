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

	QString l_QueryStr( "SELECT * FROM Files WHERE id_File = " + QString::number(idFile) + " AND file_patient = " + QString::number(idPatient)  + " AND file_author = " + QString::number(idAuthor) + " ;");
	QSqlQuery l_Query = DataBaseInteractor::Instance()->GetDatabase()->exec(l_QueryStr);

	QVector<Files> l_Result ;

	int id_file_field						= l_Query.record().indexOf("id_File");
	int url_field							= l_Query.record().indexOf("file_url");
	int sourcefile_field					= l_Query.record().indexOf("file_source");
	int file_author_field					= l_Query.record().indexOf("file_author");
	int file_patient_field					= l_Query.record().indexOf("file_patient");
	int file_creation_date_field			= l_Query.record().indexOf("file_creation_date");
	int file_last_modification_date_field	= l_Query.record().indexOf("file_last_modification_date");
	int file_md5sum_field					= l_Query.record().indexOf("file_md5sum");


	while( l_Query.next() )
	{
		l_Result.push_back( Files(	l_Query.value(id_file_field).toUInt(),
									l_Query.value(url_field).toString(),
									l_Query.value(sourcefile_field).toUInt(),
									l_Query.value(file_author_field).toUInt(),
									l_Query.value(file_patient_field).toUInt(),
									l_Query.value(file_creation_date_field).toString(),
									l_Query.value(file_last_modification_date_field).toString(),
									l_Query.value(file_md5sum_field).toString()
								 )) ;
									
	}

	// for debug
	QVector<Files>::iterator aIt = l_Result.begin();
	for(aIt; aIt != l_Result.end(); aIt++)
	{
		std::cout << "File : " << (*aIt).GetId() << std::endl ;
		std::cout << "		with the path : " << (*aIt).GetURL().toStdString() << std::endl ;
	}
}