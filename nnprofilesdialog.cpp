#include "nnprofilesdialog.h"
#include "ui_nnprofilesdialog.h"

NnProfilesDialog::NnProfilesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NnProfilesDialog)
{
    ui->setupUi(this);
}

NnProfilesDialog::~NnProfilesDialog()
{
    delete ui;
}
