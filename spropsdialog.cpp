#include "spropsdialog.h"
#include "ui_spropsdialog.h"

SectionPropertiesDialog::SectionPropertiesDialog(SSSection &ss_sec, SsMode mode, QWidget *parent) :
    QChartDialog(mode, parent),
    ui(new Ui::SPropsDialog),

    sec_menu(new QMenu(this)),
    dir_menu(new QMenu(this)),
    secs_menu(new QMenu(this)),
    dirs_menu(new QMenu(this)),

    sec(ss_sec)
{
    ui->setupUi(this);

    ui->tblSection->setItem(0, 0,
                            new QTableWidgetItem(sec.SectionName));
    ui->tblSection->setItem(1, 0,
                            new QTableWidgetItem(
                                QString(
                                    ).sprintf(
                                    "0x%08X",
                                    sec.pSection->Characteristics
                                    )
                                )
                            );
    ui->tblSection->setItem(2, 0,
                            new QTableWidgetItem(
                                QString(
                                    ).sprintf(
                                    "0x%08X",
                                    sec.pSection->VirtualAddress
                                    )
                                )
                            );
    ui->tblSection->setItem(3, 0,
                            new QTableWidgetItem(
                                QString(
                                    ).sprintf(
                                    "%d (0x%08X) bytes",
                                    sec.pSection->Misc.VirtualSize,
                                    sec.pSection->Misc.VirtualSize
                                    )
                                )
                            );
    ui->tblSection->setItem(4, 0,
                            new QTableWidgetItem(
                                QString(
                                    ).sprintf(
                                    "0x%08X",
                                    sec.pSection->PointerToRawData
                                    )
                                )
                            );
    ui->tblSection->setItem(5, 0,
                            new QTableWidgetItem(
                                QString(
                                    ).sprintf(
                                    "%d (0x%08X) bytes",
                                    sec.pSection->SizeOfRawData,
                                    sec.pSection->SizeOfRawData
                                    )
                                )
                            );
    ui->tblSection->setItem(6, 0,
                            new QTableWidgetItem(
                                QString(
                                    ).sprintf(
                                    "%f",
                                    sec.entropy_val
                                    )
                                )
                            );
    ui->tblSection->setColumnWidth(0, 200);
    ui->tblSection->horizontalHeader(
                )->setStretchLastSection(true);

    QVBoxLayout *lEntropy = new QChartLayout;

    lEntropy->addWidget(chartEntropy);
    chartEntropyDerivative->setVisible(false);
    lEntropy->addWidget(chartEntropyDerivative);

    QVBoxLayout *lDensity = new QChartLayout;
    lDensity->addWidget(chartMaximumDensity);
    chartMinimumDensity->setVisible(false);
    lDensity->addWidget(chartMinimumDensity);
    chartExtremumDensity->setVisible(false);
    lDensity->addWidget(chartExtremumDensity);

    ui->frameEntropy->setLayout(lEntropy);
    ui->frameDensity->setLayout(lDensity);

    EntropyDiagram &diagram = ss_sec.sec_entropy;
    setCharts(diagram);
}

SectionPropertiesDialog::~SectionPropertiesDialog()
{
    delete ui;
}

void SectionPropertiesDialog::on_rbEntropy_toggled(bool checked)
{
    chartEntropy->setVisible(checked);
}

void SectionPropertiesDialog::on_rbDerivative_toggled(bool checked)
{
    chartEntropyDerivative->setVisible(checked);
}

void SectionPropertiesDialog::on_rbMaximums_toggled(bool checked)
{
    chartMaximumDensity->setVisible(checked);
}

void SectionPropertiesDialog::on_rbMinimums_toggled(bool checked)
{
    chartMinimumDensity->setVisible(checked);
}

void SectionPropertiesDialog::on_rbExtremums_toggled(bool checked)
{
    chartExtremumDensity->setVisible(checked);
}
