/**
	@File : DB_Base.h
	@Language : c++
	@Authors :	Fillières Gauthier,
				Aguilar Axel,
				Gaillard Christophe


	@Licence : GNU General Public License

				This file is part of TechmedDB.

				TechmedDB is free software: you can redistribute it and/or modify
				it under the terms of the GNU General Public License as published by
				the Free Software Foundation, either version 3 of the License, or
				(at your option) any later version.

				TechmedDB is distributed in the hope that it will be useful,
				but WITHOUT ANY WARRANTY; without even the implied warranty of
				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
				See the GNU General Public License for more details.

				You should have received a copy of the GNU General Public License
				along with TechmedDB ("gpl_3_0.txt"). If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef DB_BASE_H
#define DB_BASE_H

#include <iostream>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <QtSql\qsqlrecord.h>
#include <qpair.h>
#include <qstring.h>
#include <qmap.h>
#include <qvector.h>

class DB_Base
{
protected:
	QString m_TABLENAME;
	
public:
	DB_Base();
	virtual ~DB_Base() = 0 ;

	QSqlQuery GetFromDB( QString Querry );
};

#endif // DB_BASE_H
