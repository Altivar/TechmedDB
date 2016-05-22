/**
	@File : Files.h
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

#ifndef FILES_H
#define FILES_H

#include "DB_Base.h"

class Files : public DB_Base
{
private:
	unsigned int m_IdFile;
	QString m_FileUrl;
	unsigned int m_FileSource;
	unsigned int m_FileAuthor;
	unsigned int m_FilePatient;
	QString m_FileCreationDate;
	QString m_FileLastModificationDate;
	QString m_FileMD5SUM;

	
public:
	Files();
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
	Files(	unsigned int IdFile,
			QString FileUrl,
			unsigned int FileSource,
			unsigned int FileAuthor,
			unsigned int FilePatient,
			QString FileCreationDate,
			QString FileLastModificationDate,
			QString FileMD5SUM
		);
	~Files();
	
	QString GetURL(){ return m_FileUrl; }
	//void SetURL(QString url){ m_FileUrl = url; }
	
	unsigned int GetSourceFile(){ return m_FileSource; }
	//void SetSourceFile(unsigned int src){ m_FileSource = src; }

	QString GetFileCreationDate(){ return m_FileCreationDate; }
	//void SetFileCreationDate(QString date){ m_FileCreationDate = date; }
	
	QString GetFileLastModificationDate(){ return m_FileLastModificationDate; }
	//void GetFileLastModificationDate(QString date){ m_FileLastModificationDate = date; }

	QString GetFileMD5Sum(){ return m_FileMD5SUM; }
	//void SetFileMD5Sum(QString md5sum){ m_FileMD5SUM = md5sum; }
	
	unsigned int GetId(){ return m_IdFile; }
	//void SetId(unsigned int id){ m_IdFile = id; }
	
	unsigned int GetAuthorId(){ return m_FileAuthor; }
	//void SetAuthorId(unsigned int authorId){ m_FileAuthor = authorId; }
	
	unsigned int GetPatientId(){ return m_FilePatient; }
	//void SetPatientId(unsigned int idPatient){ m_FilePatient = idPatient; }
};

#endif // FILES_H
