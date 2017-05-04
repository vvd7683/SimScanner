#include "addnewdialog.h"
#include "ui_addnewdialog.h"

addNewDialog::addNewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewDialog)
{
    ui->setupUi(this);
    setModal(true);

    ui->cboxFamily->setCurrentText(tr("Trojan.Generic"));

    ScanModel *positive_model = new ScanModel;
    ui->tvPositiveSamples->setModel(positive_model);
    ui->tvPositiveSamples->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tvPositiveSamples->setColumnWidth(0, 200);

    ScanModel *negative_model = new ScanModel;
    ui->tvNegativeSamples->setModel(negative_model);
    ui->tvNegativeSamples->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tvNegativeSamples->setColumnWidth(0, 200);
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
