#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
    setModal(true);
    //setWindowTitle();
}

aboutDialog::~aboutDialog()
{
    delete ui;
}
