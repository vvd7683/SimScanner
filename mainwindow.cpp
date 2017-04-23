#include "mainwindow.h"
#include "ui_mainwindow.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    menu_PE(new QPeFileMenu(this)),
    menu_Dir(new QMenu(this)),
    menu_Other(new QMenu(this)),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //tinyxml2::XMLDocument test;
    //OpenNN::NeuralNetwork nn;

    setWindowIcon(QIcon(tr(":/icons/icons/SimScanner.png")));

    ScanModel *model = new ScanModel;
    ui->treeView->setModel(model);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::tvContextMenuRequested);
//Temporary
    QAction *fileInfoAction = new QAction("File information", this);
    connect(fileInfoAction, &QAction::triggered, this, &MainWindow::peInfoExecute);
    menu_PE->addAction(fileInfoAction);
    menu_PE->addAction(new QAction("View PE", this));

    menu_Dir->addAction(new QAction("Scan immediately", this));
    //menu_Dir->addAction(new QAction("Add", this));

    menu_Other->addAction(new QAction("Action 1", this));
    menu_Other->addAction(new QAction("Action 2", this));
    menu_Other->addAction(new QAction("Action 3", this));
}

void MainWindow::peInfoExecute(bool checked) {
    if(menu_PE->PeFileInfo) {
        FilePropertiesDialog(*menu_PE->PeFileInfo).exec();
        menu_PE->PeFileInfo = Q_NULLPTR;
    }
}

void MainWindow::tvContextMenuRequested(const QPoint &pos) {
    if(sender() == ui->treeView) {
        QAbstractItemModel *model = ui->treeView->model();
        QModelIndex idx = ui->treeView->indexAt(pos);
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
            menu_Dir->popup(ui->treeView->viewport()->mapToGlobal(pos));
        else {
            try {
                {
                    QPeFile file(file_info);
                }
                menu_PE->PeFileInfo = &file_info;
                menu_PE->popup(ui->treeView->viewport()->mapToGlobal(pos));
            } catch(...) {
                menu_Other->popup(ui->treeView->viewport()->mapToGlobal(pos));
            }
/*
            QFile _file(file_info.absoluteFilePath());
            if(_file.exists() &&
                    _file.open(QIODevice::Unbuffered |
                               QIODevice::ReadOnly))
            {
                if(PBYTE pHeader = _file.map(0, 0x00010000)) {
                    if(PIMAGE_NT_HEADERS32 pPE = getPE32(pHeader)) {
                        menu_PE->PeFileInfo = &file_info;
                        menu_PE->popup(ui->treeView->viewport()->mapToGlobal(pos));
                    } else {
                        menu_Other->popup(ui->treeView->viewport()->mapToGlobal(pos));
                    }
                    _file.unmap(pHeader);
                }
                _file.close();
            }
*/
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox().exec();
}
