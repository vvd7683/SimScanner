#include "addnewdialog.h"
#include "ui_addnewdialog.h"

addNewDialog::addNewDialog(QWidget *parent) :
    QDialog(parent),

    menu_PE(new QPeFileMenu(this)),

    negative_model(new ScanModel),
    positive_model(new ScanModel),

    ui(new Ui::addNewDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/icons/actionNew.png"));

    ui->cboxFamily->setCurrentText(tr("Trojan.Generic"));

    ui->tvPositiveSamples->setModel(positive_model);
    ui->tvPositiveSamples->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tvPositiveSamples->setColumnWidth(0, 200);

    ui->tvPositiveSamples->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tvPositiveSamples,
            &QTreeView::customContextMenuRequested,
            this, &addNewDialog::tvPositiveContextMenuRequested);


    ui->tvNegativeSamples->setModel(negative_model);
    ui->tvNegativeSamples->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tvNegativeSamples->setColumnWidth(0, 200);

    QAction *trySampleAction = new QAction("Try sample", this);
    connect(trySampleAction, &QAction::triggered, this, &addNewDialog::trySampleSlot);
    menu_PE->addAction(trySampleAction);
    //menu_PE->addAction(new QAction("View PE", this));

    connect(positive_model,
            &ScanModel::signalAppendFile,
            this,
            &addNewDialog::slotAppendSample);
    connect(positive_model,
            &ScanModel::signalRemoveFile,
            this,
            &addNewDialog::slotRemoveSample);
}

addNewDialog::~addNewDialog()
{
    delete ui;

    delete menu_PE;

    delete negative_model;
    delete positive_model;
}

QString addNewDialog::getFamily() {
    return ui->cboxFamily->currentText();
}

int addNewDialog::getIndex() {
    return ui->sboxIndex->value();
}

void addNewDialog::tvPositiveContextMenuRequested(const QPoint &pos) {
    if(sender() == ui->tvPositiveSamples) {
        ScanModel *model = dynamic_cast<ScanModel *>(ui->tvPositiveSamples->model());
        if(!model)
            return;
        QModelIndex idx = ui->tvPositiveSamples->indexAt(pos);
        if(idx.column())
            return;
        QFileInfo file_info = model->get_file_info(idx);
        if(file_info.isDir()) {
            //menu_Dir->popup(ui->treeView->viewport()->mapToGlobal(pos));
        } else {
            try {
                {
                    QPeFile file(file_info);
                }
                menu_PE->PeFileInfo = &file_info;
                menu_PE->popup(ui->tvPositiveSamples->viewport()->mapToGlobal(pos));
            } catch(...) {
                //menu_Other->popup(ui->treeView->viewport()->mapToGlobal(pos));
                menu_PE->PeFileInfo = Q_NULLPTR;
            }
        }
    }
}

void addNewDialog::trySampleSlot(bool checked) {
    if(QFileInfo *info = menu_PE->PeFileInfo) {
        switch(FilePropertiesDialog(*info, SsMode::ssmEdit, this).exec())
        {
        case QDialog::Accepted:
        {
            QModelIndex idx = ui->tvPositiveSamples->currentIndex();
            positive_model->setData(idx,
                                    QVariant(Qt::Checked),
                                    Qt::CheckStateRole);
            break;
        }
        case QDialog::Rejected:
        default:
            break;
        }
        menu_PE->PeFileInfo = Q_NULLPTR;
    }
}

void addNewDialog::slotAppendSample(const QModelIndex &c_idx) {
    QFileInfo info = positive_model->get_file_info(c_idx);
    QTreeWidgetItem *sample_item = new SelectedSampleItem(info);

    sample_item->setText(0, info.fileName());
    sample_item->setText(1,
                         QString(
                             ).sprintf(
                             "%d bytes",
                             info.size(
                                 )
                             )
                         );
    sample_item->setText(2, info.absoluteFilePath());
    ui->tvSelectedSamples->addTopLevelItem(sample_item);
}

void addNewDialog::slotRemoveSample(const QModelIndex &c_idx) {
    QFileInfo info = positive_model->get_file_info(c_idx);
    const int c_count = ui->tvSelectedSamples->topLevelItemCount();
    for(int i = 0; i < c_count; ++i) {
        if(SelectedSampleItem *item =
                dynamic_cast<SelectedSampleItem *>(
                    ui->tvSelectedSamples->topLevelItem(i)
                    )
                )
        {
            if(item->get_info() == info) {
                ui->tvSelectedSamples;//TODO: remove element
            }
        }
    }
}
