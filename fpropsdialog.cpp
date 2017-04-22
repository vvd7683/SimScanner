#include "fpropsdialog.h"
#include "ui_fpropsdialog.h"

FilePropertiesDialog::FilePropertiesDialog(QFileInfo &Info, QWidget *parent) :
    QDialog(parent),
    info(Info),
    file(Info.absoluteFilePath()),

    ui(new Ui::FilePropertiesDialog)
{
    ui->setupUi(this);

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(chartEntropy = new QtCharts::QChartView);
    l->addWidget(chartEntropyDerivative = new QtCharts::QChartView);
    ui->gboxEntropy->setLayout(l);
    //TODO: make charts here
    if(file.exists()) {
        ui->leFilePathVal->setText(Info.absoluteFilePath());
        if(file.open(QIODevice::Unbuffered | QIODevice::ReadOnly)) {
            file.size();
            if(PBYTE pHeader = file.map(0, 0x00010000)) {
                if(PIMAGE_NT_HEADERS32 pPE = getPE32(pHeader)) {
                    //
                } else {
                    //
                }
                file.unmap(pHeader);
            }
            file.close();
        } else {
            //
        }
    } else {
        throw;
    }
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}
