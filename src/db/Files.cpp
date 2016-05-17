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



//QVector<Files> Files::GetFileFromIds( unsigned int IdFile,unsigned int IdPatient,unsigned int IdAuthor )
//{
	//QString l_QueryStr( "SELECT * FROM " + m_TABLENAME + " WHERE id_File = " + QString::number(IdFile) + " AND file_patient = " + QString::number(IdPatient)  + " AND file_author = " + QString::number(IdAuthor) + " ;");
	//QSqlQuery l_Query = QSqlQuery(l_QueryStr);

	//QVector<Files> l_Result ;

	//int id_file_field						= l_Query.record().indexOf("id_File");
	//int url_field							= l_Query.record().indexOf("file_url");
	//int sourcefile_field					= l_Query.record().indexOf("file_source");
	//int file_author_field					= l_Query.record().indexOf("file_author");
	//int file_patient_field					= l_Query.record().indexOf("file_patient");
	//int file_creation_date_field			= l_Query.record().indexOf("file_creation_date");
	//int file_last_modification_date_field	= l_Query.record().indexOf("file_last_modification_date");
	//int file_md5sum_field					= l_Query.record().indexOf("file_md5sum");


	//while( l_Query.next() )
	//{
	//	l_Result.push_back( Files(	l_Query.value(id_file_field).toUInt(),
	//								l_Query.value(url_field).toString(),
	//								l_Query.value(sourcefile_field).toUInt(),
	//								l_Query.value(file_author_field).toUInt(),
	//								l_Query.value(file_patient_field).toUInt(),
	//								l_Query.value(file_creation_date_field).toString(),
	//								l_Query.value(file_last_modification_date_field).toString(),
	//								l_Query.value(file_md5sum_field).toString()
	//							 )) ;
	//								
	//}
	//return l_Result;
//}