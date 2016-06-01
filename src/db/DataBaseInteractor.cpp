#include "DataBaseInteractor.h"
#include <QtSql/QSqlRecord>


#include <qmessagebox.h>

#include <qstringlist.h>
#include <qdatetime.h>

static DataBaseInteractor* _instance = 0;


DataBaseInteractor::DataBaseInteractor() :
m_ItemModel(1,1)
{
	m_DataBaseFullName = "TechmedDB.db";
	//m_DataBasePath = ".\\..\\..\\..\\src\\db\\";
	m_DataBasePath = ".\\";

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
			m_UsersRightMap[l_Query.value(id_Tag_field).toUInt()]=STANDARD_USER;
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

void DataBaseInteractor::UserChangePassword(QString oldPsw, QString NewPsw)
{
	QMessageBox qmb;
	qmb.setWindowTitle("Password");
							
	if( m_CurrentUser.GetUserRightCode() >= STANDARD_USER )
	{
		QString query =	"SELECT user_passeword FROM User WHERE id_user = " + QString::number( m_CurrentUser.GetUserId() ) + " ;" ;

		QSqlQuery response = DataBaseInteractor::Instance()->m_DataBase.exec(query);
		int password_field	= response.record().indexOf("user_passeword");

		if( response.next() )
		{
			QString l_mdp = response.value(password_field).toString() ;

			if( l_mdp == oldPsw )
			{
				query = "UPDATE User SET user_passeword = '" + NewPsw + "' WHERE id_user = " + QString::number( m_CurrentUser.GetUserId() ) + " ;" ;
				DataBaseInteractor::Instance()->m_DataBase.exec(query);
				
				qmb.setText(QString("Password updated !"));
				qmb.setIcon(QMessageBox::Information);
			}
			else
			{		
				qmb.setText(QString("Error, wrong current password."));
				qmb.setIcon(QMessageBox::Warning);
			}
		}
		else
		{
			qmb.setText(QString("Unable to update password."));
			qmb.setIcon(QMessageBox::Warning);
		}
		std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;
	}
	else
	{
		qmb.setText(QString("You have not the right to change the password."));
		qmb.setIcon(QMessageBox::Warning);
	}

	qmb.exec();
}
//////////////////////////////////////////////////
/////                QUERIES                 /////
//////////////////////////////////////////////////
bool DataBaseInteractor::FileResearch(const QStringList& tagList, unsigned int idPatient, unsigned int idFile, unsigned int idAuthor)
{

	QString l_QueryStr( "SELECT File.* FROM File ") ;
	std::vector<int> tagRef;
	if(!tagList.empty())
	{
		for(int i = 0; i < tagList.size(); i++)
		{
			int ref = GetIdByTag(tagList.at(i));
			if(ref <= 0)
			{
				std::cout << "Unknown tag \"" << tagList.at(i).toStdString() << "\" : ignored " << std::endl;
				continue;
			}
			tagRef.push_back(ref);
		}
	}
	if(!tagRef.empty())
		l_QueryStr += "NATURAL JOIN File_Tag ";
		
	bool l_NeedInc = false ;

	if( idFile != 0 )
	{
		l_QueryStr += "WHERE id_File = '" + QString::number(idFile) + "'" ;
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
		l_QueryStr += "file_patient = '" + QString::number(idPatient) + "'" ;
		l_NeedInc = true;
	} 
	if( idAuthor != 0)
	{
		if( l_NeedInc )
		{
			l_QueryStr+= " AND " ;
		}
		else
		{
			l_QueryStr += "WHERE " ;
		}
		l_QueryStr += "file_author = '" + QString::number(idAuthor) + "'" ;
		l_NeedInc = true;
	}
	for(unsigned int i = 0; i < tagRef.size(); i++)
	{
		if( l_NeedInc )
		{
			l_QueryStr+= " AND " ;
		}
		else
		{
			l_QueryStr += "WHERE " ;
		}
		l_QueryStr += "File_Tag.id_tag = '" + QString::number(tagRef.at(i)) + "'" ;
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
	
	m_ItemModel.clear();
	m_ItemModel.setRowCount(l_Result.size() );
	m_ItemModel.setColumnCount(8);
	QStringList Titles;
	Titles << "id_File" << "file's url" << " original source file" << "Author id" << "Patient id" << "Creation date" << "Last modification date" << "MD5Sum" ;
	m_ItemModel.setHorizontalHeaderLabels(Titles) ;
	int i = 0;
	for(QVector<Files>::iterator aIt = l_Result.begin(); aIt != l_Result.end(); aIt++, ++i)
	{
		QStandardItem *itemId=new QStandardItem;
		QStandardItem *itemURL=new QStandardItem;
		QStandardItem *itemSrc=new QStandardItem;
		QStandardItem *itemAuthor=new QStandardItem;
		QStandardItem *itemPatient=new QStandardItem;
		QStandardItem *itemCreation=new QStandardItem;
		QStandardItem *itemModification=new QStandardItem;
		QStandardItem *itemMd5Sum=new QStandardItem;
		
		itemId->setText(QString::number((*aIt).GetId()));
		m_ItemModel.setItem(i, 0, itemId);
		
		itemURL->setText((*aIt).GetURL());
		m_ItemModel.setItem(i, 1, itemURL);

		itemSrc->setText(QString::number((*aIt).GetSourceFile()));
		m_ItemModel.setItem(i, 2, itemSrc);

		itemAuthor->setText(QString::number((*aIt).GetAuthorId()));
		m_ItemModel.setItem(i, 3, itemAuthor);

		itemPatient->setText(QString::number((*aIt).GetPatientId()));
		m_ItemModel.setItem(i, 4, itemPatient);

		itemCreation->setText((*aIt).GetFileCreationDate());
		m_ItemModel.setItem(i, 5, itemCreation);

		itemModification->setText((*aIt).GetFileLastModificationDate());
		m_ItemModel.setItem(i, 6, itemModification);

		itemMd5Sum->setText((*aIt).GetFileMD5Sum());
		m_ItemModel.setItem(i, 7, itemMd5Sum);
	}
	
	// for debug
	std::cout << l_Result.size() << " files found!" << std::endl ;

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
		l_QueryStr+= " WHERE id_user = '" + QString::number(idUser) + "'" ;
		l_NeedInc = true ;
	}
	if( !FirstName.isEmpty() )
	{
		if( l_NeedInc )
			l_QueryStr+= " AND " ;
		else
			l_QueryStr+=" WHERE " ;
		l_QueryStr+="user_firstname = '" + FirstName + "'" ;
	}
	if( !LastName.isEmpty() )
	{
		if( l_NeedInc )
			l_QueryStr+= " AND " ;
		else
			l_QueryStr+=" WHERE " ;
		l_QueryStr+="user_lastname = '" + LastName + "'" ;
	}
	l_QueryStr+=";";

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

	m_ItemModel.clear();
	m_ItemModel.setRowCount(l_Result.size() );
	m_ItemModel.setColumnCount(5);
	QStringList Titles;
	Titles << "id_user" << "Last Name" << "First name" << "User group" << "User description" ;
	m_ItemModel.setHorizontalHeaderLabels(Titles) ;
	int i = 0;
	for(QVector<Users>::iterator aIt = l_Result.begin(); aIt != l_Result.end(); aIt++, ++i)
	{
		QStandardItem *itemId=new QStandardItem;
		QStandardItem *itemLname=new QStandardItem;
		QStandardItem *itemFname=new QStandardItem;
		QStandardItem *itemGroup=new QStandardItem;
		QStandardItem *itemDesc=new QStandardItem;
		
		itemId->setText(QString::number((*aIt).GetUserId()));
		m_ItemModel.setItem(i, 0, itemId);
		
		itemLname->setText((*aIt).GetLastName());
		m_ItemModel.setItem(i, 1, itemLname);

		itemFname->setText((*aIt).GetFirstName());
		m_ItemModel.setItem(i, 2, itemFname);

		itemGroup->setText(QString::number((*aIt).GetUserGroupId()));
		m_ItemModel.setItem(i, 3, itemGroup);

		itemDesc->setText((*aIt).GetUserDescription());
		m_ItemModel.setItem(i, 4, itemDesc);
	}
	std::cout << l_Result.size() << " users found." << std::endl ;
	if( l_Result.size() > 0 )
		return true;
	else 
		return false;
}

unsigned int DataBaseInteractor::GetIdByTag(QString tag)
{

	QString l_QueryStr( "SELECT id_tag, tag_reference FROM Tag" );

	if( !tag.isEmpty() )
	{
		l_QueryStr+= " WHERE tag_name = '" + tag + "'" ;
	}
	l_QueryStr+=";";

	QSqlQuery l_Query = m_DataBase.exec(l_QueryStr);

	int ref_field	= l_Query.record().indexOf("tag_reference");
	int id_field	= l_Query.record().indexOf("id_tag");

	unsigned int reference, idTag;
	if( l_Query.next() )
	{
		idTag = l_Query.value(id_field).toUInt();
		reference = l_Query.value(ref_field).toUInt();
	}
	else
	{
		std::cout << std::endl << "Error : tag not found !" << std::endl ;
		return 0;
	}
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;

	return reference > 0 ? reference : idTag ;

}

bool DataBaseInteractor::GetTags()
{
	QString l_QueryStr( "SELECT * FROM Tag" );
	QSqlQuery l_Query = m_DataBase.exec(l_QueryStr);

	int id_field   = l_Query.record().indexOf("id_tag");
	int name_field = l_Query.record().indexOf("tag_name");
	int type_field = l_Query.record().indexOf("tag_type");
	int ref_field  = l_Query.record().indexOf("tag_reference");

	QVector<Tags> l_Result ;
	while( l_Query.next() )
	{
		if( l_Query.value(type_field).toUInt() != 5 || m_UsersRightMap[m_CurrentUser.GetUserRightCode()] == ADMINISTRATOR_USER )
		{
			l_Result.push_back( Tags(	l_Query.value(id_field).toUInt(),
										l_Query.value(name_field).toString(),
										l_Query.value(type_field).toUInt(),
										l_Query.value(ref_field).toUInt() ) ) ;
		}
	}
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;
	
	QStringList tagNames;

	m_ItemModel.clear();
	m_ItemModel.setRowCount(l_Result.size() );
	m_ItemModel.setColumnCount(4);
	QStringList Titles;
	Titles << "Tag's id" << "Tag Name" << "Tag type" << "Reference's tag id" ;
	m_ItemModel.setHorizontalHeaderLabels(Titles) ;
	int i = 0;
	for(QVector<Tags>::iterator aIt = l_Result.begin(); aIt != l_Result.end(); aIt++, ++i)
	{
		QStandardItem *itemId=new QStandardItem;
		QStandardItem *itemname=new QStandardItem;
		QStandardItem *itemType=new QStandardItem;
		QStandardItem *itemRef=new QStandardItem;
		
		itemId->setText(QString::number((*aIt).GetId()));
		m_ItemModel.setItem(i, 0, itemId);
		
		itemname->setText((*aIt).GetName());
		m_ItemModel.setItem(i, 1, itemname);

		itemType->setText(QString::number((*aIt).GetType()));
		m_ItemModel.setItem(i, 2, itemType);

		itemRef->setText(QString::number((*aIt).GetReference()));
		m_ItemModel.setItem(i, 3, itemRef);

		tagNames.append((*aIt).GetName());
	}
		
	std::cout << l_Result.size() << " tags found." << std::endl ;
	if( l_Result.size() > 0 )
		return true;
	else 
		return false;
}


bool DataBaseInteractor::GetTagById(unsigned int idTag)
{
	QString l_QueryStr( "SELECT tag_reference FROM Tag" );

	if( idTag > 0 )
	{
		l_QueryStr+= " WHERE id_tag = '" + QString::number(idTag) + "'" ;
	}
	l_QueryStr+=";";

	QSqlQuery l_Query = m_DataBase.exec(l_QueryStr);	

	int ref_field	= l_Query.record().indexOf("tag_reference");

	unsigned int reference = 0;
	if( l_Query.next() )
	{
		reference = l_Query.value(ref_field).toUInt();
	}
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;



	l_QueryStr = "SELECT * FROM Tag";
	if( reference > 0 )
	{
		l_QueryStr+= " WHERE id_tag = '" + QString::number(reference) + "' OR tag_reference = '" + QString::number(reference) + "'";
	}
	else
	{
		l_QueryStr+= " WHERE id_tag = '" + QString::number(idTag) + "' OR tag_reference = '" + QString::number(idTag) + "'";
	}
	l_QueryStr+=";";
	l_Query = m_DataBase.exec(l_QueryStr);

	int id_field		= l_Query.record().indexOf("id_tag");
	int name_field = l_Query.record().indexOf("tag_name");
	int type_field	= l_Query.record().indexOf("tag_type");
	ref_field	= l_Query.record().indexOf("tag_reference");

	QVector<Tags> l_Result ;
	while( l_Query.next() )
	{
		if( l_Query.value(type_field).toUInt() != 5 || m_UsersRightMap[m_CurrentUser.GetUserRightCode()] == ADMINISTRATOR_USER )
		{
			l_Result.push_back( Tags(	l_Query.value(id_field).toUInt(),
										l_Query.value(name_field).toString(),
										l_Query.value(type_field).toUInt(),
										l_Query.value(ref_field).toUInt() ) ) ;
		}
	}
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;
	
	QStringList tagNames;

	m_ItemModel.clear();
	m_ItemModel.setRowCount(l_Result.size() );
	m_ItemModel.setColumnCount(4);
	QStringList Titles;
	Titles << "Tag's id" << "Tag Name" << "Tag type" << "Reference's tag id" ;
	m_ItemModel.setHorizontalHeaderLabels(Titles) ;
	int i = 0;
	for(QVector<Tags>::iterator aIt = l_Result.begin(); aIt != l_Result.end(); aIt++, ++i)
	{
		QStandardItem *itemId=new QStandardItem;
		QStandardItem *itemname=new QStandardItem;
		QStandardItem *itemType=new QStandardItem;
		QStandardItem *itemRef=new QStandardItem;
		
		itemId->setText(QString::number((*aIt).GetId()));
		m_ItemModel.setItem(i, 0, itemId);
		
		itemname->setText((*aIt).GetName());
		m_ItemModel.setItem(i, 1, itemname);

		itemType->setText(QString::number((*aIt).GetType()));
		m_ItemModel.setItem(i, 2, itemType);

		itemRef->setText(QString::number((*aIt).GetReference()));
		m_ItemModel.setItem(i, 3, itemRef);

		tagNames.append((*aIt).GetName());
	}
		
	std::cout << l_Result.size() << " tags found." << std::endl ;
	if( l_Result.size() > 0 )
		return true;
	else 
		return false;
}

bool DataBaseInteractor::AddFile(QString filePath, unsigned int patientId)
{
	
	QString l_QueryStr( "INSERT INTO File (file_url, file_author, file_patient, file_creation_date, file_last_modification_date, file_md5sum) VALUES ('") ;
	
	// file path
	l_QueryStr += filePath;
	l_QueryStr += "', '";
	// author id
	l_QueryStr += QString::number(m_CurrentUser.GetUserId());
	l_QueryStr += "', '";
	// patient id
	l_QueryStr += QString::number(patientId);
	l_QueryStr += "', '";
	
	
	// compute correct date
	QString date = QString::number(QDate::currentDate().day());
	date += "-";
	date += QString::number(QDate::currentDate().month());
	date += "-";
	date += QString::number(QDate::currentDate().year());

	// creation date
	l_QueryStr += date;
	l_QueryStr += "', '";
	// last modif date (creation date)
	l_QueryStr += date;
	l_QueryStr += "', '";
	// md5sum
	l_QueryStr += "AAAAA";
	l_QueryStr += "');";

	QSqlQuery l_Query = m_DataBase.exec(l_QueryStr);
	
	std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;

	return true;

}

bool DataBaseInteractor::AddUser(QString LastName, QString FirstName, QString Desc, QString psw, unsigned int GroupId, USER_RIGHT Right)
{
	if( m_UsersRightMap[m_CurrentUser.GetUserRightCode()] == ADMINISTRATOR_USER )
	{
		QString l_QueryStr( "INSERT INTO User (user_lastname, user_firstname, user_group, user_right, user_description,user_passeword) VALUES ('") ;
		l_QueryStr += LastName;
		l_QueryStr += "', '";
		l_QueryStr += FirstName;
		l_QueryStr += "', '";
		l_QueryStr += QString::number(GroupId);
		l_QueryStr += "', '";
		unsigned int defaultKey = m_UsersRightMap.key(GUEST_USER);
		l_QueryStr += QString::number( m_UsersRightMap.key( Right, defaultKey ) );
		l_QueryStr += "', '";
		l_QueryStr += Desc;
		l_QueryStr += "', '";
		l_QueryStr += psw;
		l_QueryStr += "');";

		QSqlQuery l_Query = m_DataBase.exec(l_QueryStr);	
		std::cout << m_DataBase.lastError().text().toStdString() << std::endl ;
		return true;
	}
	else
	{
		std::cout << " You are not administrator, so you can not add an user, please contact your administrator." << std::endl ;
		return false;
	}
}
