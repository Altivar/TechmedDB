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
}

Users::~Users()
{
}