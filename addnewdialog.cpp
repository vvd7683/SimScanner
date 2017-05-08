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
        QAbstractItemModel *model = ui->tvPositiveSamples->model();
        QModelIndex idx = ui->tvPositiveSamples->indexAt(pos);
        if(idx.column())
            //idx = model->index(idx.row(), 0);
            return;
        //QModelIndex idx = model->index(item_index.row(), 0);

        QString s;
        while(true) {
            s = model->data(idx).toString() + s;
            idx = idx.parent();
            if(idx.parent() == idx)
                break;
            s = tr("\\") + s;
        }
        if(s[PRED(s.length())] == QChar(':')) {
            s += tr("\\");
        }

        QFileInfo file_info(s);
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
            QTreeWidgetItem *sample_item = new SelectedSampleItem(*info);
            ui->tvSelectedSamples->addTopLevelItem(sample_item);
            positive_model->setData(ui->tvPositiveSamples->currentIndex(),
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
