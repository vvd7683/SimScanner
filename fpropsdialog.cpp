#include "fpropsdialog.h"
#include "ui_fpropsdialog.h"

#include <QMessageBox>

FilePropertiesDialog::FilePropertiesDialog(QFileInfo &Info, QWidget *parent) :
    QDialog(parent),
    pe_file(Info),

    ui(new Ui::FilePropertiesDialog),

    chartEntropy(new EntropyChartView(this)),
    chartEntropyDerivative(new EntropyChartView(this)),
    chartMaximumDensity(new EntropyChartView(this)),
    chartMinimumDensity(new EntropyChartView(this))
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

    QVBoxLayout *lEntropy = new QChartLayout;

    lEntropy->addWidget(chartEntropy);
    chartEntropyDerivative->setVisible(false);
    lEntropy->addWidget(chartEntropyDerivative);

    QVBoxLayout *lDensity = new QChartLayout;
    lDensity->addWidget(chartMaximumDensity);
    chartMinimumDensity->setVisible(false);
    lDensity->addWidget(chartMinimumDensity);

    ui->frameEntropy->setLayout(lEntropy);
    ui->frameDensity->setLayout(lDensity);

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
    QVector<EntropyY>pts;
    EntropyDiagram &diagram = pe_file.getEntropy();
    pts.resize(diagram.size());
    for(int i = 0; i < diagram.size(); ++i) pts[i] = diagram[i].entropy_value;
    if(!chartEntropy->add_points(pts))
        throw;

    for(int i = 0; i < diagram.size(); ++i) pts[i] = diagram[i].entropy_derivative_value;
    if(!chartEntropyDerivative->add_points(pts))
        throw;
    chartEntropyDerivative->chart()->setTitle(tr("Entropy derivative chart"));

    for(int i = 0; i < diagram.size(); ++i) pts[i] = diagram[i].maximums_density;
    if(!chartMaximumDensity->add_points(pts))
        throw;
    chartMaximumDensity->chart()->setTitle(tr("Maximums density"));


    for(int i = 0; i < diagram.size(); ++i) pts[i] = diagram[i].minimums_density;
    if(!chartMinimumDensity->add_points(pts))
        throw;
    chartMinimumDensity->chart()->setTitle(tr("Minimums density"));
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}


void FilePropertiesDialog::on_rbDerivative_toggled(bool checked)
{
    chartEntropyDerivative->setVisible(checked);
}

void FilePropertiesDialog::on_rbEntropy_toggled(bool checked)
{
    chartEntropy->setVisible(checked);
}

void FilePropertiesDialog::on_rbMaximums_toggled(bool checked)
{
    chartMaximumDensity->setVisible(checked);
}

void FilePropertiesDialog::on_rbMinimums_toggled(bool checked)
{
    chartMinimumDensity->setVisible(checked);
}
