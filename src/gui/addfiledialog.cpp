#include "addfiledialog.h"

#include <qfile.h>
#include <qmessagebox.h>
#include <qdir.h>
#include <qfiledialog.h>

addfiledialog::addfiledialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	
	ui.setupUi(this);

	m_isValidated = false;
	
	connect(ui.pushButton_ok, SIGNAL(clicked()), this, SLOT(OnOkButtonClicked()));
	connect(ui.pushButton_annuler, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.pushButton_file, SIGNAL(clicked()), this, SLOT(OnFileButtonClicked()));
	connect(ui.pushButton_folder, SIGNAL(clicked()), this, SLOT(OnFolderButtonClicked()));
}

addfiledialog::~addfiledialog()
{

}

void addfiledialog::Reset()
{
	ui.lineEdit_filePath->clear();
	ui.lineEdit_idPatient->clear();
	m_patientId = 0;
	m_isValidated = false;
}

void addfiledialog::SetFolderIcon(QString path)
{
	ui.pushButton_folder->setIcon(QIcon(path));
}

void addfiledialog::SetFileIcon(QString path)
{
	ui.pushButton_file->setIcon(QIcon(path));
}

void addfiledialog::OnOkButtonClicked()
{
	
	if(ui.lineEdit_filePath->text().isEmpty() || ui.lineEdit_idPatient->text().isEmpty())
	{
		QMessageBox::warning(this, "Add file", "You have not set all the requested data.");
		return;
	}
	bool ok;
	unsigned int id = ui.lineEdit_idPatient->text().toUInt(&ok, 10);
	if(!ok || id < 1)
	{
		QMessageBox::warning(this, "Add file", "The patient ID is not in the good format.");
		ui.lineEdit_idPatient->clear();
		return;
	}

	m_patientId = id;

	m_isValidated = true;
	close();
}

void addfiledialog::OnFileButtonClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,
     tr("Get Image"), "/home/jana", tr("Image Files (*.dicom *.dcm *.mhd)"));

	if(!fileName.isEmpty())
		ui.lineEdit_filePath->setText(fileName);
}

void addfiledialog::OnFolderButtonClicked()
{
	QString fileName = QFileDialog::getExistingDirectory(this, tr("Get Directory"),
            "",
            QFileDialog::ShowDirsOnly
            | QFileDialog::DontResolveSymlinks);

	if(!fileName.isEmpty())
		ui.lineEdit_filePath->setText(fileName);
}

