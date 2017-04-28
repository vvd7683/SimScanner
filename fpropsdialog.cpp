#include "fpropsdialog.h"
#include "ui_fpropsdialog.h"

FilePropertiesDialog::FilePropertiesDialog(QFileInfo &Info, QWidget *parent) :
    QDialog(parent),
    pe_file(Info),

    ui(new Ui::FilePropertiesDialog),

    chartEntropy(new EntropyChartView(this)),
    chartEntropyDerivative(new EntropyChartView(this))
{
    ui->setupUi(this);
    setModal(true);

    setWindowIcon(QIcon(tr(":/icons/icons/Target.png")));

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
    ui->tabFileProperties->setTabIcon(0, QIcon(tr(":/icons/icons/File.png")));
    ui->tabFileProperties->setTabText(1, tr("PE header"));
    ui->tabFileProperties->setTabIcon(1, QIcon(tr(":/icons/icons/Grid.png")));
    ui->tabFileProperties->setTabText(2, tr("Entropy chart"));
    ui->tabFileProperties->setTabIcon(2, QIcon(tr(":/icons/icons/3d_bar_chart.png")));

    setWindowTitle(Info.absoluteFilePath());

    ui->tabPeProperties->setTabText(0, tr("Common headers"));
    ui->tabPeProperties->setTabText(1, tr("Sections"));
    ui->tabPeProperties->setTabText(2, tr("Directories"));

    ui->tblFileHeader->setItem(0, 0,
                               new QTableWidgetItem(
                                   QString().sprintf("0x%04X", pe_file.getMachine())));
    ui->tblFileHeader->setItem(0, 1,
                               new QTableWidgetItem(pe_file.getMachineString()));
    ui->tblFileHeader->setItem(1, 0,
                               new QTableWidgetItem(
                                   QString().sprintf("0x%04X", pe_file.getFlags())));
    ui->tblFileHeader->setItem(1, 1,
                               new QTableWidgetItem(pe_file.getFlagsString()));
    ui->tblFileHeader->setItem(2, 0,
                               new QTableWidgetItem(
                                   QString().sprintf("%d bytes", pe_file.getOptHeaderSz())));

    ui->lMachineVal->setText(
                pe_file.getMachineString());
    ui->lSubsystemVal->setText(
                pe_file.getSubsystemString());
    ui->lSectionsCountVal->setText(
                QString().sprintf("%d", 0));
    ui->lDirectoriesCountVal->setText(
                QString().sprintf("%d", 0));

    ui->tblOptionalHeader->setItem(0, 0,
                                   new QTableWidgetItem(
                                       QString().sprintf(
                                           "0x%08X", pe_file.getImageBase())));
    ui->tblOptionalHeader->setItem(1, 0,
                                   new QTableWidgetItem(
                                       QString().sprintf(
                                           "0x%08X", pe_file.getImageSize())));
    const DWORD cEntry = pe_file.getEntry();
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
                Info.absoluteFilePath(
                    )
                );
    ui->lFileSizeVal->setText(
                QString(
                    ).sprintf(
                    "%llu bytes",
                    Info.size(
                        )
                    )
                );
    ui->lDateTimeVal->setText(
                Info.created().toString());
    EntropyDiagram &entropy = pe_file.getEntropy();
    foreach(const EntropyPoint pt, entropy) {
        if(!chartEntropy->add_point(pt))
            throw;
    }
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}

