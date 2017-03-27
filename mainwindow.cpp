#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    menu_PE(new QMenu(this)),
    menu_Dir(new QMenu(this)),
    menu_Other(new QMenu(this)),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(tr(":/icons/icons/SimScanner.png")));

    ScanModel *model = new ScanModel;
    ui->treeView->setModel(model);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::tvContextMenuRequested);
//Temporary
    menu_PE->addAction(new QAction("File information", this));
    menu_PE->addAction(new QAction("View PE", this));

    menu_Dir->addAction(new QAction("Scan immediately", this));
    //menu_Dir->addAction(new QAction("Add", this));

    menu_Other->addAction(new QAction("Action 1", this));
    menu_Other->addAction(new QAction("Action 2", this));
    menu_Other->addAction(new QAction("Action 3", this));
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
            //TODO: check format
            menu_Other->popup(ui->treeView->viewport()->mapToGlobal(pos));
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
