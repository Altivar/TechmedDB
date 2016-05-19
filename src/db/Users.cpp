#include "Users.h"


Users::Users()
{
	m_UserID = 0;
	m_UserGroupRefAndName = QPair<unsigned int,QString>(21, "invite");
	m_UserRightRefAndName = QPair<unsigned int,QString>(13, "guest");

	m_UserFirstName = ""; 
	m_UserLastName= "";
	m_UserPassword = "";
	m_UserDescription = "Guest user with minimum right.";

	m_TABLENAME = "User" ;
}
Users::Users(unsigned int ID, QString FirstName, QString LastName, QPair<unsigned int,QString> Group, QPair<unsigned int,QString> Right, QString Password, QString Desc)
{
	m_UserID = ID;
	m_UserGroupRefAndName = Group;
	m_UserRightRefAndName = Right;

	m_UserFirstName = FirstName; 
	m_UserLastName= LastName;
	m_UserPassword = Password;
	m_UserDescription = Desc;

	BuildUserTagsMap();
}

Users::~Users()
{
}

//QVector<Users> Users::GetUserByNames(QString LastName, QString FirstName)
//{ 
	//QString l_QueryStr( "SELECT * FROM " + m_TABLENAME );

	//bool l_NeedInc = false ;
	//if( !FirstName.isEmpty() )
	//{
	//	l_QueryStr+= " WHERE user_firstname = " + FirstName ;
	//	l_NeedInc = true ;
	//}
	//if( !FirstName.isEmpty() )
	//{
	//	if( l_NeedInc )
	//		l_QueryStr+= " AND " ;
	//	else
	//		l_QueryStr+=" WHERE " ;
	//	l_QueryStr+="user_lastname = " + LastName ;
	//}
	//l_QueryStr += " ;";
	//
	//QSqlQuery l_Query = GetFromDB(l_QueryStr);

	//QVector<Users> l_Result ;

	//int id_field		= l_Query.record().indexOf("_id");
	//int firstName_field = l_Query.record().indexOf("user_firstname");
	//int lastName_field	= l_Query.record().indexOf("user_lastname");
	//int groupRef_field	= l_Query.record().indexOf("user_group");
	//int rightRef_field	= l_Query.record().indexOf("user_right");
	//int desc_field		= l_Query.record().indexOf("user_description");
	//int password_field	= l_Query.record().indexOf("user_password");

	//while( l_Query.next() )
	//{
	//	QPair<unsigned int,QString> group(l_Query.value(groupRef_field).toUInt(),l_Query.value(groupRef_field).toString());
	//	QPair<unsigned int,QString> right(l_Query.value(rightRef_field).toUInt(),l_Query.value(rightRef_field).toString());
	//	l_Result.push_back( Users(	l_Query.value(id_field).toUInt(),
	//								l_Query.value(firstName_field).toString(),
	//								l_Query.value(lastName_field).toString(),
	//								group,
	//								right,
	//								l_Query.value(password_field).toString(),
	//								l_Query.value(desc_field).toString() ) ) ;
	//								
	//}
	//return l_Result;
//}
//
//QVector<Users> Users::GetUserById(unsigned int id)
//{
//	//QString l_QueryStr( "SELECT * FROM " + m_TABLENAME + " WHERE _id = " + QString::number(id) + " ;");
//	//QSqlQuery l_Query = GetFromDB(l_QueryStr);
//
//	//QVector<Users> l_Result ;
//
//	//int id_field		= l_Query.record().indexOf("id_user");
//	//int firstName_field = l_Query.record().indexOf("user_firstname");
//	//int lastName_field	= l_Query.record().indexOf("user_lastname");
//	//int groupRef_field	= l_Query.record().indexOf("user_group");
//	//int rightRef_field	= l_Query.record().indexOf("user_right");
//	//int desc_field		= l_Query.record().indexOf("user_description");
//	//int password_field	= l_Query.record().indexOf("user_password");
//
//	//while( l_Query.next() )
//	//{
//	//	QPair<unsigned int,QString> group(l_Query.value(groupRef_field).toUInt(),l_Query.value(groupRef_field).toString());
//	//	QPair<unsigned int,QString> right(l_Query.value(rightRef_field).toUInt(),l_Query.value(rightRef_field).toString());
//	//	l_Result.push_back( Users(	l_Query.value(id_field).toUInt(),
//	//								l_Query.value(firstName_field).toString(),
//	//								l_Query.value(lastName_field).toString(),
//	//								group,
//	//								right,
//	//								l_Query.value(password_field).toString(),
//	//								l_Query.value(desc_field).toString() ) ) ;
//	//}
//	//return l_Result;
//}

void Users::BuildUserTagsMap()
{
	//QString l_QueryStr( "SELECT * FROM User_Tag WHERE user_id = '" + QString::number(m_UserID) + "' ;");
	//QSqlQuery l_Query = GetFromDB(l_QueryStr);	

	//int _id = l_Query.record().indexOf("id_user_tag");
	//int user_id = l_Query.record().indexOf("user_id");
	//int tag_id = l_Query.record().indexOf("tag_id");

	//while( l_Query.next() )
	//{
	//	unsigned int id_tagCurrent = l_Query.value(tag_id).toUInt();

	//	QString l_QueryStrTag( "SELECT tag_name FROM Tag WHERE id_tag = '" + QString::number(id_tagCurrent) + "' ;");
	//	QSqlQuery l_QueryTag = GetFromDB(l_QueryStrTag);
	//	int TagName = l_QueryTag.record().indexOf("tag_name");
	//	l_QueryTag.first() ;

	//	m_UserTags[id_tagCurrent] = l_QueryTag.value(TagName).toString() ;
	//}
}