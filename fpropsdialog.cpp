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
    chartMinimumDensity(new EntropyChartView(this)),
    chartExtremumDensity(new EntropyChartView(this)),

    structureTree(new StructureTree(this))
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

    //ui->tabFileProperties->setTabText(0, tr("File properties"));
    ui->tabFileProperties->setTabIcon(0, QIcon(tr(":/icons/icons/File.png")));
    //ui->tabFileProperties->setTabText(1, tr("PE header"));
    ui->tabFileProperties->setTabIcon(1, QIcon(tr(":/icons/icons/Grid.png")));
    //ui->tabFileProperties->setTabText(2, tr("Entropy chart"));
    ui->tabFileProperties->setTabIcon(2, QIcon(tr(":/icons/icons/3d_bar_chart.png")));

    setWindowTitle(Info.absoluteFilePath());

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
    chartExtremumDensity->setVisible(false);
    lDensity->addWidget(chartExtremumDensity);

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

    for(int i = 0; i < diagram.size(); ++i) pts[i] += diagram[i].maximums_density;//Already contains minimums
    if(!chartExtremumDensity->add_points(pts))
        throw;
    chartExtremumDensity->chart()->setTitle(tr("Extremums density"));

    init_sections();
    init_directories();

    ui->tabStructure->layout()->addWidget(structureTree);
    connect(structureTree, &StructureTree::itemSelectionChanged, this, &FilePropertiesDialog::on_structureTree_itemSelectionChanged);
}

FilePropertiesDialog::~FilePropertiesDialog()
{
    delete ui;
}

void FilePropertiesDialog::init_sections() {
    QTreeWidgetItem *topSectionsItem = new QTreeWidgetItem(structureTree);
    structureTree->addTopLevelItem(topSectionsItem);
    topSectionsItem->setText(0, tr("SECTIONS"));
    SectionMap &sections = pe_file.getSections();
    ui->lSectionsCountVal->setText(QString().sprintf("%d", sections.size()));
    foreach(SSSection ss_sec, sections) {
        QTreeWidgetItem *child = new QTreeWidgetItem(topSectionsItem);
        child->setText(0, ss_sec.SectionName);
        //topSectionsItem->addChild(child);
        QTreeWidgetItem *chars_child = new QTreeWidgetItem(child);
        chars_child->setText(0, tr("Flags"));
        chars_child->setText(1, QString().sprintf("0x%08X", ss_sec.pSection->Characteristics));
        if(isExecutable(ss_sec.pSection))
            chars_child->setText(2, chars_child->text(2).append(tr("executable; ")));
        if(!isWriteable(ss_sec.pSection))
            chars_child->setText(2, chars_child->text(2).append(tr("read-only; ")));
        //child->addChild(chars_child);
        QTreeWidgetItem *rva_child = new QTreeWidgetItem(child);
        rva_child->setText(0, tr("Relative address"));
        rva_child->setText(1, QString().sprintf("0x%08X", ss_sec.pSection->VirtualAddress));
        rva_child->setText(2, QString().sprintf("[Flat address 0x%08X]",
                                                pe_file.getImageBase() +
                                                ss_sec.pSection->VirtualAddress));
        //child->addChild(rva_child);
        QTreeWidgetItem *vsz_child = new QTreeWidgetItem(child);
        vsz_child->setText(0, tr("Memory size"));
        vsz_child->setText(1, QString().sprintf("0x%08X",
                                                ss_sec.pSection->Misc.VirtualSize));
        vsz_child->setText(2, QString().sprintf("[Aligned 0x%08X]",
                                                pe_file.memAlign(ss_sec.pSection->Misc.VirtualSize)));
        //child->addChild(vsz_child);
        QTreeWidgetItem *entropy_child = new QTreeWidgetItem(child);
        entropy_child->setText(0, tr("Entropy"));
        entropy_child->setText(1, QString().sprintf("%f",
                                                ss_sec.entropy_val));
        entropy_child->setText(2, QString("Total entropy of section"));

        //TODO: use or not?
        EntropyChartItem *entropy_chart_item = new EntropyChartItem(entropy_child);
        entropy_chart_item->setText(0, QString("Entropy chart"));
        connect(structureTree,
                &StructureTree::signalMouseMove,
                entropy_chart_item->chartView,
                &EntropyChartItem::TreeChart::hoverItem);

        EntropyChartItem *derivative_chart_item = new EntropyChartItem(entropy_child);
        derivative_chart_item->setText(0, QString("Entropy Derivative"));
        connect(structureTree,
                &StructureTree::signalMouseMove,
                derivative_chart_item->chartView,
                &EntropyChartItem::TreeChart::hoverItem);
        EntropyChartItem *extremums_chart_item = new EntropyChartItem(entropy_child);
        extremums_chart_item->setText(0, QString("Extremums Density"));
        connect(structureTree,
                &StructureTree::signalMouseMove,
                extremums_chart_item->chartView,
                &EntropyChartItem::TreeChart::hoverItem);
    }
    topSectionsItem->setExpanded(true);
}

void FilePropertiesDialog::init_directories() {
    QTreeWidgetItem *topDirectoriesItem = new QTreeWidgetItem(structureTree);
    structureTree->addTopLevelItem(topDirectoriesItem);
    topDirectoriesItem->setText(0, tr("DIRECTORIES"));
    DirectoryMap &directories = pe_file.getDirectories();
    ui->lDirectoriesCountVal->setText(QString().sprintf("%d", directories.size()));
    foreach(SSDirectory ss_dir, directories) {
        QTreeWidgetItem *child = new QTreeWidgetItem(topDirectoriesItem);
        child->setText(0, QString().sprintf("%d", ss_dir.index));
        child->setText(1, ss_dir.DirectoryName());
        child->setText(2, ss_dir.DirectoryComment());
        QTreeWidgetItem *rva_child = new QTreeWidgetItem(child);
        rva_child->setText(0, "Relative address");
        rva_child->setText(1, QString().sprintf("0x%08X", ss_dir.Directory->VirtualAddress));
        rva_child->setText(2, QString().sprintf("[Flat address 0x%08X]",
                                                pe_file.getImageBase() +
                                                ss_dir.Directory->VirtualAddress));
        QTreeWidgetItem *vsz_child = new QTreeWidgetItem(child);
        vsz_child->setText(0, "Size");
        vsz_child->setText(1, QString().sprintf("0x%08X", ss_dir.Directory->Size));
        vsz_child->setText(2, QString().sprintf("[Aligned 0x%08X]",
                                                pe_file.memAlign(ss_dir.Directory->Size)));
    }
    topDirectoriesItem->setExpanded(true);
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

void FilePropertiesDialog::on_rbExtremums_toggled(bool checked)
{
    chartExtremumDensity->setVisible(checked);
}

void FilePropertiesDialog::on_structureTree_itemSelectionChanged()
{
}
