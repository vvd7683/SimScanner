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
}

SectionPropertiesDialog::~SectionPropertiesDialog()
{
    delete ui;
}
