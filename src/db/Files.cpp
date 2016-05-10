#include "Files.h"

Files::Files(QVariant *FileDesc, 
		bool b_IdFile, 
		bool b_FileUrl, 
		bool b_FileSource,
		bool b_FileAuthor,
		bool b_FilePatient,
		bool b_FileCreationDate,
		bool b_FileLastModificationDate,
		bool b_FileMD5SUM)
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

Files::~Files()
{
}