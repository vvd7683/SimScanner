#include "addnewdialog.h"
#include "ui_addnewdialog.h"

addNewDialog::addNewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewDialog)
{
    ui->setupUi(this);
    setModal(true);
}

addNewDialog::~addNewDialog()
{
    delete ui;
}

QString addNewDialog::getFamily() {
    return ui->cboxFamily->currentText();
}

int addNewDialog::getIndex() {
    return ui->sboxIndex->value();
}
