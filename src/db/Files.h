#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery>
#include <QtSql\qsqltablemodel>
#include <qstring.h>

class Files
{
private:
	int m_IdFile;
	QString m_FileUrl;
	int m_FileSource;
	int m_FileAuthor;
	int m_FilePatient;
	QString m_FileCreationDate;
	QString m_FileLastModificationDate;
	QString m_FileMD5SUM;

	
public:
	Files(QVariant* FileDesc, 
		bool b_IdFile = 1, 
		bool b_FileUrl = 1, 
		bool b_FileSource = 1,
		bool b_FileAuthor = 1,
		bool b_FilePatient = 1,
		bool b_FileCreationDate = 1,
		bool b_FileLastModificationDate = 1,
		bool b_FileMD5SUM = 1
		);
	~Files();
};

#endif // FILES_H
