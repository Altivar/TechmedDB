#include <iostream>
#include <QSqlDatabase>
#include <QFile>
#include <qstringlist.h>
#include <qapplication.h>
#include <conio.h>
#include <string>


#include <qsqlquery.h>





/*** FONCTIONS ***/
bool CreerBase()
{
	// CREE LA BASE DE DONNEES SI ELLE N'EXISTE PAS
	std::cout << "Initialisation de la base..." << std::endl;

	QSqlQuery query;
	bool ok = query.exec("PRAGMA foreign_keys = ON;");
    if (!ok) 
	{
		std::cerr << "Erreur lors de l'ajout du support des clés étrangères" << std::endl;   
		return false;
	}
    
	ok = query.exec("CREATE TABLE IF NOT EXISTS type (id_type INTEGER PRIMARY KEY AUTOINCREMENT, id_tag INTEGER, nom varchar(128) NOT NULL, description varchar(512), FOREIGN KEY(id_tag) REFERENCES tag(id_tag))");
    if(!ok) 
    {
        std::cerr << "ERREUR DE CREATION DE TABLE type"<<std::endl;
        return false;
    }

	ok = query.exec("CREATE TABLE IF NOT EXISTS tag (id_tag INTEGER PRIMARY KEY AUTOINCREMENT,  value varchar(128) NOT NULL, id_type INTEGER NOT NULL, id_tag_ref INTEGER, FOREIGN KEY(id_type) REFERENCES type(id_type), FOREIGN KEY(id_tag_ref) REFERENCES tag(id_tag))");
    if(!ok) 
    {
        std::cerr << "ERREUR DE CREATION DE TABLE tag"<<std::endl;
        return false;
    }

    ok = query.exec("CREATE TABLE IF NOT EXISTS data (id_data INTEGER PRIMARY KEY AUTOINCREMENT,  ref_image varchar(1024) NOT NULL)");
    if(!ok) 
    {
        std::cerr << "ERREUR DE CREATION DE TABLE data"<<std::endl;
        return false;
    }
    
	ok = query.exec("CREATE TABLE IF NOT EXISTS datas_tag (id_data INTEGER NOT NULL,  id_tag INTEGER NOT NULL, FOREIGN KEY(id_data) REFERENCES data(id_data),FOREIGN KEY(id_tag) REFERENCES tag(id_tag))");
    if(!ok) 
    {
        std::cerr << "ERREUR DE CREATION DE TABLE datas_tag"<<std::endl;
        return false;
    }
    
	ok = query.exec("CREATE TABLE IF NOT EXISTS user (id_user INTEGER PRIMARY KEY AUTOINCREMENT, name varchar(64) NOT NULL, password varchar(64) NOT NULL)");
    if(!ok) 
    {
        std::cerr << "ERREUR DE CREATION DE TABLE dico_tag"<<std::endl;
        return false;
    }

	ok = query.exec("CREATE TABLE IF NOT EXISTS users_tag (id_user INTEGER NOT NULL,  id_tag INTEGER NOT NULL, FOREIGN KEY(id_user) REFERENCES user(id_user),FOREIGN KEY(id_tag) REFERENCES tag(id_tag))");
    if(!ok) 
    {
        std::cerr << "ERREUR DE CREATION DE TABLE datas_tag"<<std::endl;
        return false;
    }

	return true;
}

bool NettoyerTable( const QString & table )
{
	QSqlQuery query;
	return query.exec(QString("DELETE FROM %1;").arg(table));
}
bool NettoyerTables(  )
{
	QStringList tableList;
	tableList << "data" << "type" << "tag" << "datas_tag" << "user" << "users_tag";
	for(QStringList::const_iterator elem = tableList.begin(); elem != tableList.end(); elem++)
	{
		if(!NettoyerTable(*elem))
		{
			std::cerr << "Erreur pendant le nettoyage de la table '" << (*elem).toStdString() << "'..." << std::endl;
			return false;
		}
	}

	return true;
}
/*** FONCTIONS ***/





int main(int argc, char** argv) {
    QApplication app(argc, argv);
	


	char* filename = "TechmedDB.db";
	
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    
	// verifie si le fichier est ouvert correctement
	bool ok = db.open();   
    if (!ok) {
        std::cout << "Can't open file..." << std::endl;
        return 1;
    }


	// creation de la base
	if(!CreerBase())
	{
		_getch();
		return 1;
	}



	// nettoyage des table
    std::cout << "nettoyage des tables..." << std::endl;
	if(!NettoyerTables())
	{
		_getch();
		return 1;
	}




	QSqlQuery query;

	_getch();

	return 0;
}