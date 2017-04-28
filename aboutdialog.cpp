#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QMessageBox>

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
    setModal(true);
    setWindowIcon(QIcon(tr(":/icons/icons/Info.png")));
    ui->lLogo->setPixmap(QPixmap(tr(":/icons/icons/SimScannerLogo.png")));
}

aboutDialog::~aboutDialog()
{
    delete ui;
}
