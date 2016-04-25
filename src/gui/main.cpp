#include "techmeddb.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TechmedDB w;
	w.show();
	return a.exec();
}
