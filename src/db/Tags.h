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

#ifndef TAGS_H
#define TAGS_H

#include "DB_Base.h"

class Tags : public DB_Base
{

private:
	unsigned int m_id;
	QString m_name;
	unsigned int m_type;
	unsigned int m_reference;

public:
	Tags();
	Tags(unsigned int id, QString name, unsigned int type, unsigned int reference);
	~Tags();

	unsigned int GetId() { return m_id; }
	QString GetName() { return m_name; }
	unsigned int GetType() { return m_type; }
	unsigned int GetReference() { return m_reference; }


};

#endif // TAGS_H
