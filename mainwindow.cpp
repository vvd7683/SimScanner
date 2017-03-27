#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(tr(":/icons/icons/SimScanner.png")));

    ScanModel *model = new ScanModel;
    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox().exec();
}
