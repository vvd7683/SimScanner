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

    ui->tvSelectedSamples->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tvSelectedSamples,
            &QTreeView::customContextMenuRequested,
            this,
            &addNewDialog::tvSelectedContextMenuRequested);
    selected_menu.addAction(ui->actionRemove_sample);
    selected_menu.addAction(ui->actionView_PE_properties);
}

addNewDialog::~addNewDialog()
{
    delete ui;

    delete menu_PE;

    delete negative_model;
    delete positive_model;
}

QString addNewDialog::getSampleFamily() {
    return ui->cboxFamily->currentText();
}

int addNewDialog::getSampleIndex() {
    return ui->sboxIndex->value();
}

QVector<QFileInfo> addNewDialog::getSelectedSamples() {
    QVector<QFileInfo> result;
    for(int i = 0; i < ui->tvSelectedSamples->topLevelItemCount(); ++i) {
        if(SelectedSampleItem *item =
                dynamic_cast<SelectedSampleItem *>(
                    ui->tvSelectedSamples->topLevelItem(i)
                    )
                )
        {
            result.push_back(positive_model->get_file_info(item->get_index()));
        }
    }
    return result;
}

QVector<QFileInfo> addNewDialog::getNegativeSamples() {
    QVector<QFileInfo>result;
    foreach(QModelIndex index, negative_model->getChecked()) {
        result.push_back(negative_model->get_file_info(index));
    }
    return result;
}

void addNewDialog::tvSelectedContextMenuRequested(const QPoint &pos) {
    if(sender() == ui->tvSelectedSamples) {
        if(SelectedSampleItem *item =
                dynamic_cast<SelectedSampleItem *>(
                    ui->tvSelectedSamples->itemAt(pos)
                    )
                )
        {
            selected_menu.popup(
                        ui->tvSelectedSamples->viewport(
                            )->mapToGlobal(
                            pos
                            )
                        );
        }
    }
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
    const int c_count = ui->tvSelectedSamples->topLevelItemCount();
    for(int i = 0; i < c_count; ++i) {
        if(SelectedSampleItem *item =
                dynamic_cast<SelectedSampleItem *>(
                    ui->tvSelectedSamples->topLevelItem(i)
                    )
                )
        {
            if(c_idx == item->get_index())
                return;
        }
    }
    QTreeWidgetItem *sample_item = new SelectedSampleItem(c_idx);
    QFileInfo info = positive_model->get_file_info(c_idx);

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

    QTreeWidgetItem *sections_child = new QTreeWidgetItem(sample_item);
    sections_child->setText(0, tr("SECTIONS"));

    QTreeWidgetItem *directories_child = new QTreeWidgetItem(sample_item);
    directories_child->setText(0, tr("DIRECTORIES"));

    QTreeWidgetItem *entropy_child = new QTreeWidgetItem(sample_item);
    entropy_child->setText(0, tr("Entropy"));

    QTreeWidgetItem *nn_child = new QTreeWidgetItem(sample_item);
    nn_child->setText(0, tr("Neuroprofiles"));

    foreach(QString ssNNTypeName, getNnTypes()) {
        QTreeWidgetItem *object_nns = new QTreeWidgetItem(nn_child);
        object_nns->setText(0, ssNNTypeName);
        //TODO: add childs for each type of nn
    }

    ui->tvSelectedSamples->addTopLevelItem(sample_item);
    ui->tvSelectedSamples->setColumnWidth(0, 200);
}

void addNewDialog::slotRemoveSample(const QModelIndex &c_idx) {
    const int c_count = ui->tvSelectedSamples->topLevelItemCount();
    for(int i = 0; i < c_count; ++i) {
        if(SelectedSampleItem *item =
                dynamic_cast<SelectedSampleItem *>(
                    ui->tvSelectedSamples->topLevelItem(i)
                    )
                )
        {
            if(item->get_index() == c_idx) {
                delete ui->tvSelectedSamples->takeTopLevelItem(i);
                break;
            }
        }
    }
}

void addNewDialog::on_actionRemove_sample_triggered()
{
    if(SelectedSampleItem *selected =
            dynamic_cast<SelectedSampleItem *>(ui->tvSelectedSamples->currentItem()))
    {
        positive_model->setData(selected->get_index(),
                                QVariant(Qt::Unchecked),
                                Qt::CheckStateRole);
    }
}

void addNewDialog::on_actionView_PE_properties_triggered()
{
    if(SelectedSampleItem *selected =
            dynamic_cast<SelectedSampleItem *>(ui->tvSelectedSamples->currentItem()))
    {
        switch(FilePropertiesDialog(
                   positive_model->get_file_info(
                       selected->get_index()),
                   SsMode::ssmEdit,
                   this).exec(
                   )
               )
        {
        case QDialog::Accepted:
        case QDialog::Rejected:
        default:
            break;
        }
    }
}
