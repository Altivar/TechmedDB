#include "DataBaseInteractor.h"



static DataBaseInteractor* _instance = 0;


DataBaseInteractor::DataBaseInteractor()
{
	m_DataBaseFullName = "TechmedDB.db";
	m_DataBasePath = ".\\..\\..\\..\\src\\db\\";


	QString l_DataBaseFullPathName = m_DataBasePath+m_DataBaseFullName;
	m_DataBase = QSqlDatabase::addDatabase("QSQLITE",l_DataBaseFullPathName);
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

	// fill the global data from the database
	QString l_QueryStr( "SELECT * FROM Tag WHERE tag_type = 5 ;") ;
	QSqlQuery l_Query = m_DataBase.exec(l_QueryStr);
	int id_Tag_field  = l_Query.record().indexOf("id_Tag");
	int TagName_field = l_Query.record().indexOf("tag_name");
	int TagType_field = l_Query.record().indexOf("tag_type");
	int TagRef_field  = l_Query.record().indexOf("tag_reference");
	QStringList l_UsersTypes ;
	l_UsersTypes << "guest" << "user" << "admin" ;
	while( l_Query.next() )
	{
		switch( l_UsersTypes.indexOf( l_Query.value(TagName_field).toString() ) )
		{
		case 0: 
			m_UsersRightMap[l_Query.value(id_Tag_field).toUInt()]=GUEST_USER;
			break ;
		case 1: 
			m_UsersRightMap[l_Query.value(id_Tag_field).toUInt()]=STANDAR_USER;
			break ;
		case 2:
			m_UsersRightMap[l_Query.value(id_Tag_field).toUInt()]=ADMINISTRATOR_USER;
			break ;
		default :
			std::cout << "User right unknow ! It is be setted to guest." << std::endl ;
			m_UsersRightMap[l_Query.value(id_Tag_field).toUInt()]=GUEST_USER;
			break;
		}		
	}
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;
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
	bool IsById;
	int l_id = id.toUInt( &IsById ) ;
	QString query =	"SELECT * FROM User WHERE ";

	if( IsById )
	{
		query += "id_user = " + QString::number(l_id) ;
		//std::cout << id.toStdString() << " Is a id." << std::endl;
	}
	else
	{
		// parse if a separator caracter is detected to split lastname and firstname
		char l_separator = 33 ;
		QStringList l_Name ;
		l_Name = id.split( l_separator ) ;
		while(l_Name.size() < 2 && l_separator < 65 )
		{
			l_Name = id.split( l_separator ) ; //
			if( l_separator == 38 || l_separator == 44 )
			{
				l_separator += 2;
			}
			else
				l_separator++ ;
		}
		if( l_Name.size() == 2 )
		{
			query += "user_lastname = '" + l_Name.at(0) + "' AND " ;
			query += "user_firstname = '" + l_Name.at(1) + "'" ;
		}
		else
		{
			std::cout << "Invalid name format, check if you enter the lastname and the first name with a valid special caracter to separate them ( default use '.')." << std::endl ;
			return ERROR_NO_RIGHT;
		}
		//std::cout << id.toStdString() << " Is a name." << std::endl;
	}

	query += " ;";

	QSqlQuery response = DataBaseInteractor::Instance()->m_DataBase.exec(query);

	int id_field		= response.record().indexOf("id_user");
	int firstName_field = response.record().indexOf("user_firstname");
	int lastName_field	= response.record().indexOf("user_lastname");
	int groupRef_field	= response.record().indexOf("user_group");
	int rightRef_field	= response.record().indexOf("user_right");
	int desc_field		= response.record().indexOf("user_description");
	int password_field	= response.record().indexOf("user_passeword");

	while( response.next() )
	{
		std::cout << " User Found." << std::endl ;
		QString l_mdp = response.value(password_field).toString() ;
		if( l_mdp == psw )
		{
			unsigned int l_user_group_ref = response.value(groupRef_field).toUInt();
			QPair<unsigned int,QString> group(l_user_group_ref,QString::number(l_user_group_ref));

			unsigned int l_user_rigth_ref = response.value(rightRef_field).toUInt();
			QPair<unsigned int,QString> right(l_user_rigth_ref,QString::number(l_user_rigth_ref));

			m_CurrentUser = Users(	response.value(id_field).toUInt(),
									response.value(firstName_field).toString(),
									response.value(lastName_field).toString(),
									group,
									right,
									l_mdp,
									response.value(desc_field).toString() ) ;
			std::cout << " Password is ok for the user :" << m_CurrentUser.GetLastName().toStdString() << "  " << m_CurrentUser.GetFirstName().toStdString() << std::endl;
			return m_UsersRightMap[l_user_rigth_ref] ;
		}
	}
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;

	return ERROR_NO_RIGHT;
}

bool DataBaseInteractor::FileResearch(unsigned int idPatient, unsigned int idFile, unsigned int idAuthor)
{

	QString l_QueryStr( "SELECT * FROM File ") ;
	bool l_NeedInc = false ;

	if( idFile != 0 )
	{
		l_QueryStr += "WHERE id_File = " + QString::number(idFile) ;
		l_NeedInc = true;
	}
	if( idPatient != 0)
	{
		if( l_NeedInc )
		{
			l_QueryStr+= " AND " ;
			l_NeedInc = false ;
		}	
		else
		{
			l_QueryStr += "WHERE " ;
		}
		l_QueryStr += "file_patient = " + QString::number(idPatient) ;
		l_NeedInc = true;
	} 
	if( idAuthor != 0)
	{
		if( l_NeedInc )
		{
			l_QueryStr+= " AND " ;
			l_NeedInc = false ;
		}else
		{
			l_QueryStr += "WHERE " ;
		}
		l_QueryStr += "file_author = " + QString::number(idAuthor) ;
		l_NeedInc = true;
	}
	l_QueryStr+= " ;";
	QSqlQuery l_Query = m_DataBase.exec(l_QueryStr);

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
		std::cout << "File(s) founded !" << std::endl ;
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
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;

	// for debug
	std::cout << l_Result.size() << " files found!" << std::endl ;
	QVector<Files>::iterator aIt = l_Result.begin();
	for(aIt; aIt != l_Result.end(); aIt++)
	{
		std::cout << " + File : " << (*aIt).GetId() << std::endl ;
		std::cout << " ---> with the path : " << (*aIt).GetURL().toStdString() << std::endl ;
	}

	if( l_Result.size() > 0 )
		return true;
	else 
		return false;
}

bool DataBaseInteractor::UserResearch(unsigned int idUser, QString LastName, QString FirstName )
{
	QString l_QueryStr( "SELECT * FROM User" );

	bool l_NeedInc = false ;
	if( idUser > 0 )
	{
		l_QueryStr+= " WHERE id_user = " + QString::number(idUser) ;
		l_NeedInc = true ;
	}
	if( !FirstName.isEmpty() )
	{
		if( l_NeedInc )
			l_QueryStr+= " AND " ;
		else
			l_QueryStr+=" WHERE " ;
		l_QueryStr+="user_firstname = " + FirstName ;
	}
	if( !FirstName.isEmpty() )
	{
		if( l_NeedInc )
			l_QueryStr+= " AND " ;
		else
			l_QueryStr+=" WHERE " ;
		l_QueryStr+="user_lastname = " + LastName ;
	}
	l_QueryStr += " ;";
	
	QSqlQuery l_Query = m_DataBase.exec(l_QueryStr);

	QVector<Users> l_Result ;

	int id_field		= l_Query.record().indexOf("id_user");
	int firstName_field = l_Query.record().indexOf("user_firstname");
	int lastName_field	= l_Query.record().indexOf("user_lastname");
	int groupRef_field	= l_Query.record().indexOf("user_group");
	int rightRef_field	= l_Query.record().indexOf("user_right");
	int desc_field		= l_Query.record().indexOf("user_description");
	int password_field	= l_Query.record().indexOf("user_passeword");

	while( l_Query.next() )
	{
		QPair<unsigned int,QString> group(l_Query.value(groupRef_field).toUInt(),l_Query.value(groupRef_field).toString());
		QPair<unsigned int,QString> right(l_Query.value(rightRef_field).toUInt(),l_Query.value(rightRef_field).toString());
		l_Result.push_back( Users(	l_Query.value(id_field).toUInt(),
									l_Query.value(firstName_field).toString(),
									l_Query.value(lastName_field).toString(),
									group,
									right,
									l_Query.value(password_field).toString(),
									l_Query.value(desc_field).toString() ) ) ;
									
	}
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;

	//for debug
	std::cout << l_Result.size() << " User found!" << std::endl ;
	QVector<Users>::iterator aIt = l_Result.begin();
	for(aIt; aIt != l_Result.end(); aIt++)
	{
		std::cout << " + User : " << (*aIt).GetUserId() << std::endl ;
		std::cout << " ---> " << (*aIt).GetLastName().toStdString() << "  " << (*aIt).GetFirstName().toStdString() << std::endl ;
	}
	
	if( l_Result.size() > 0 )
		return true;
	else 
		return false;
}