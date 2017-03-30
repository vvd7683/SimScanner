#include "fpropsdialog.h"
#include "ui_fpropsdialog.h"

FilePropertiesDialog::FilePropertiesDialog(QFileInfo &Info, QWidget *parent) :
    QDialog(parent),
    info(Info),

    ui(new Ui::FilePropertiesDialog)
{
    ui->setupUi(this);

    //TODO: make charts here
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}
