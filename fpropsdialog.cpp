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

    ui->tblFileHeader->verticalHeader(
                )->setFixedWidth(200);
    ui->tblOptionalHeader->verticalHeader(
                )->setFixedWidth(200);
    ui->tblFileHeader->horizontalHeader(
                )->setStretchLastSection(true);
    ui->tblOptionalHeader->horizontalHeader(
                )->setStretchLastSection(true);
    ui->tblFileHeader->setColumnWidth(1, 200);
    ui->tblOptionalHeader->setColumnWidth(1, 200);

    ui->tabFileProperties->setTabText(0, tr("File properties"));
    ui->tabFileProperties->setTabText(1, tr("PE header"));
    ui->tabFileProperties->setTabText(2, tr("Entropy chart"));

    ui->tabPeProperties->setTabText(0, tr("Common headers"));
    ui->tabPeProperties->setTabText(1, tr("Sections"));
    ui->tabPeProperties->setTabText(2, tr("Directories"));

    ui->tblFileHeader->setItem(0, 0,
                               new QTableWidgetItem(
                                   QString().sprintf("0x%04X", file.getMachine())));
    ui->tblFileHeader->setItem(0, 1,
                               new QTableWidgetItem(file.getMachineString()));
    ui->tblFileHeader->setItem(1, 0,
                               new QTableWidgetItem(
                                   QString().sprintf("0x%04X", file.getFlags())));
    ui->tblFileHeader->setItem(1, 1,
                               new QTableWidgetItem(file.getFlagsString()));
    ui->tblFileHeader->setItem(2, 0,
                               new QTableWidgetItem(
                                   QString().sprintf("%d bytes", file.getOptHeaderSz())));

    ui->lMachineVal->setText(
                file.getMachineString());
    ui->lSubsystemVal->setText(
                file.getSubsystemString());
    ui->lSectionsCountVal->setText(
                QString().sprintf("%d", 0));
    ui->lDirectoriesCountVal->setText(
                QString().sprintf("%d", 0));

    ui->tblOptionalHeader->setItem(0, 0,
                                   new QTableWidgetItem(
                                       QString().sprintf(
                                           "0x%08X", file.getImageBase())));
    ui->tblOptionalHeader->setItem(1, 0,
                                   new QTableWidgetItem(
                                       QString().sprintf(
                                           "0x%08X", file.getImageSize())));
    const DWORD cEntry = file.getEntry();
    ui->tblOptionalHeader->setItem(2, 0,
                                   new QTableWidgetItem(
                                       QString().sprintf(
                                           "0x%08X", cEntry)));
    if(cEntry) {
        //TODO: check for valid entry point
    } else {
        ui->tblOptionalHeader->setItem(2, 1,
                                       new QTableWidgetItem(tr("No entry point")));
    }

    QVBoxLayout *l = new QVBoxLayout;

    l->addWidget(chartEntropy);
    l->addWidget(chartEntropyDerivative);

    ui->gboxEntropy->setLayout(l);

    ui->leFilePathVal->setText(
                Info.absoluteFilePath());
    ui->lFileSizeVal->setText(
                QString().sprintf("%llu bytes", Info.size()));
    ui->lDateTimeVal->setText(
                Info.created().toString());
    //TODO: make charts here
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}
