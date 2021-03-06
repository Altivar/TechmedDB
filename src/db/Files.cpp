#include "Files.h"

Files::Files() :
DB_Base()
{
}

Files::Files(QVariant *FileDesc, 
		bool b_IdFile, 
		bool b_FileUrl, 
		bool b_FileSource,
		bool b_FileAuthor,
		bool b_FilePatient,
		bool b_FileCreationDate,
		bool b_FileLastModificationDate,
		bool b_FileMD5SUM)  :
DB_Base()
{
	int count=0;

	if(b_IdFile)
	{
		m_IdFile=FileDesc[count].toInt();
		count++;
	}
	if(b_FileUrl)
	{
		m_FileUrl=FileDesc[count].toString();
		count++;
	}
	if(b_FileSource)
	{
		m_FileSource=FileDesc[count].toInt();
		count++;
	}
	if(b_FileAuthor)
	{
		m_FileAuthor=FileDesc[count].toInt();
		count++;
	}
	if(b_FilePatient)
	{
		m_FilePatient=FileDesc[count].toInt();
		count++;
	}
	if(b_FileCreationDate)
	{
		m_FileCreationDate=FileDesc[count].toString();
		count++;
	}
	if(b_FileLastModificationDate)
	{
		m_FileLastModificationDate=FileDesc[count].toString();
		count++;
	}
	if(b_FileMD5SUM)
	{
		m_FileMD5SUM=FileDesc[count].toString();
		count++;
	}
}

Files::Files(	unsigned int IdFile,
				QString FileUrl,
				unsigned int FileSource,
				unsigned int FileAuthor,
				unsigned int FilePatient,
				QString FileCreationDate,
				QString FileLastModificationDate,
				QString FileMD5SUM	)  :
DB_Base(),
m_IdFile(IdFile),
m_FileUrl(FileUrl),
m_FileSource(FileSource),
m_FileAuthor(FileAuthor),
m_FilePatient(FilePatient),
m_FileCreationDate(FileCreationDate),
m_FileLastModificationDate(FileLastModificationDate),
m_FileMD5SUM(FileMD5SUM)				
{

}

Files::~Files()
{
}