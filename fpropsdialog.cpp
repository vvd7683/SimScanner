#include "fpropsdialog.h"
#include "ui_fpropsdialog.h"

FilePropertiesDialog::FilePropertiesDialog(QFileInfo &Info, QWidget *parent) :
    QDialog(parent),
    file(Info),

    ui(new Ui::FilePropertiesDialog),

    chartEntropy(new QtCharts::QChartView),
    chartEntropyDerivative(new QtCharts::QChartView)
{
    ui->setupUi(this);
    setModal(true);

    ui->tabFileProperties->setTabText(0, tr("File properties"));
    ui->tabFileProperties->setTabText(1, tr("PE header"));
    ui->tabFileProperties->setTabText(2, tr("Entropy chart"));

    ui->tabPeProperties->setTabText(0, tr("Common headers"));
    ui->tabPeProperties->setTabText(1, tr("Sections"));
    ui->tabPeProperties->setTabText(2, tr("Directories"));

    ui->tblFileHeader;
    ui->tblOptionalHeader;

    QVBoxLayout *l = new QVBoxLayout;

    l->addWidget(chartEntropy);
    l->addWidget(chartEntropyDerivative);

    ui->gboxEntropy->setLayout(l);

    ui->leFilePathVal->setText(Info.absoluteFilePath());
    ui->lFileSizeVal->setText(QString().sprintf("%llu bytes", Info.size()));
    ui->lDateTimeVal->setText(Info.created().toString());
    //TODO: make charts here
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}
