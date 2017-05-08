#include "addnewdialog.h"
#include "ui_addnewdialog.h"

addNewDialog::addNewDialog(QWidget *parent) :
    QDialog(parent),

    menu_PE(new QPeFileMenu(this)),

    ui(new Ui::addNewDialog)
{
    ui->setupUi(this);
    setModal(true);

    ui->cboxFamily->setCurrentText(tr("Trojan.Generic"));

    ScanModel *positive_model = new ScanModel;
    ui->tvPositiveSamples->setModel(positive_model);
    ui->tvPositiveSamples->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tvPositiveSamples->setColumnWidth(0, 200);

    ui->tvPositiveSamples->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tvPositiveSamples,
            &QTreeView::customContextMenuRequested,
            this, &addNewDialog::tvPositiveContextMenuRequested);


    ScanModel *negative_model = new ScanModel;
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
        if(file_info.isDir())
            ;//menu_Dir->popup(ui->treeView->viewport()->mapToGlobal(pos));
        else {
            try {
                {
                    QPeFile file(file_info);
                }
                menu_PE->PeFileInfo = &file_info;
                menu_PE->popup(ui->tvPositiveSamples->viewport()->mapToGlobal(pos));
            } catch(...) {
                //menu_Other->popup(ui->treeView->viewport()->mapToGlobal(pos));
            }
        }
    }
}

void addNewDialog::trySampleSlot(bool checked) {
    if(menu_PE->PeFileInfo) {
        FilePropertiesDialog(*menu_PE->PeFileInfo, SsMode::ssmEdit, this).exec();
        menu_PE->PeFileInfo = Q_NULLPTR;
    }
}
