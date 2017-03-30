#include "fpropsdialog.h"
#include "ui_fpropsdialog.h"

FilePropertiesDialog::FilePropertiesDialog(QFileInfo &Info, QWidget *parent) :
    QDialog(parent),
    info(Info),

    ui(new Ui::FilePropertiesDialog)
{
    ui->setupUi(this);

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(chartEntropy = new QtCharts::QChartView);
    l->addWidget(chartEntropyDerivative = new QtCharts::QChartView);
    ui->gboxEntropy->setLayout(l);
    //TODO: make charts here
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}
