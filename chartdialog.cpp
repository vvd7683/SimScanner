#include "chartdialog.h"
#include "ui_chartdialog.h"

ChartDialog::ChartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartDialog)
{
    ui->setupUi(this);
}

ChartDialog::~ChartDialog()
{
    delete ui;
}
