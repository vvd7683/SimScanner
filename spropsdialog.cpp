#include "spropsdialog.h"
#include "ui_spropsdialog.h"

SectionPropertiesDialog::SectionPropertiesDialog(SSSection &ss_sec, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SPropsDialog),

    chartEntropy(new EntropyChartView(this)),
    chartEntropyDerivative(new EntropyChartView(this)),
    chartMaximumDensity(new EntropyChartView(this)),
    chartMinimumDensity(new EntropyChartView(this)),
    chartExtremumDensity(new EntropyChartView(this)),

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

    QVector<EntropyY>pts;
    EntropyDiagram &diagram = ss_sec.sec_entropy;
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

    for(int i = 0; i < diagram.size(); ++i) pts[i] += diagram[i].maximums_density;//Already contains minimums
    if(!chartExtremumDensity->add_points(pts))
        throw;
    chartExtremumDensity->chart()->setTitle(tr("Extremums density"));

}

SectionPropertiesDialog::~SectionPropertiesDialog()
{
    delete ui;
}
