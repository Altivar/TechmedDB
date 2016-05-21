/**
	@File : Tags.h
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

#ifndef TAG_H
#define TAG_H

#include <iostream>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <qstring.h>
#include "DB_Base.h"

class Tag : DB_Base
{

public:
	Tag();
	Tag(unsigned int id, QString name, unsigned int type, unsigned int reference);
	~Tag();

	unsigned int GetId() { return m_id; }
	QString GetName() { return m_name; }
	unsigned int GetType() { return m_type; }
	unsigned int GetReference() { return m_reference; }


private:
	unsigned int m_id;
	QString m_name;
	unsigned int m_type;
	unsigned int m_reference;

};

#endif // TAG_H
