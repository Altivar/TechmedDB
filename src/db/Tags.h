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
