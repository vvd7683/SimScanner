#include "fpropsdialog.h"
#include "ui_chartdialog.h"

FilePropertiesDialog::FilePropertiesDialog(QFileInfo &Info, QWidget *parent) :
    QDialog(parent),
    info(Info),

    ui(new Ui::FilePropertiesDialog)
{
    ui->setupUi(this);
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}
