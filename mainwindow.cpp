#include "mainwindow.h"
#include "ui_mainwindow.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ss(ssNotInitialized),

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

    ssnnProfiles = DbProfile::loadProfiles();

    SS = ScanState::ssNotInitialized;
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

void MainWindow::on_actionAbout_triggered()
{
    aboutDialog().exec();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_btnScan_clicked()
{
    emit ui->actionScan->triggered();
}

void MainWindow::on_btnStop_clicked()
{
    emit ui->actionStop->triggered();
}

void MainWindow::on_actionNew_triggered()
{
    ScanState ssPrev = SS;
    SS = ScanState::ssEdit;
    addNewDialog dlg;
    if(dlg.exec()) {
        QString &family = dlg.getFamily();
        const int cIdx = dlg.getIndex();

        for(DbProfile::nnType t = DbProfile::nnType::nntAnySection;
            t < DbProfile::nnType::nntCount; t = (DbProfile::nnType)SUCC((int)t))
        {
            for(DbProfile::nnKind k = DbProfile::nnKind::nnkFixed;
                k < DbProfile::nnKind::nnkCount;
                k = (DbProfile::nnKind)SUCC((int)k))
            {
                ssnnProfiles.push_back(new DbProfile(family, cIdx, t, k));
            }
        }
    } else {
        //
    }
    SS = ssPrev;
}

MainWindow::ScanState MainWindow::set_ss(ScanState _ss) {
    ss = _ss;
    switch(ss)
    {
    case MainWindow::ScanState::ssNotInitialized:
        ui->actionQuit->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionHelp_content->setEnabled(true);

        ui->actionEdit->setEnabled(true);
        ui->actionScan->setEnabled(false);
        ui->actionStop->setEnabled(false);
        ui->actionNew->setEnabled(true);
        ui->btnScan->setEnabled(false);
        ui->btnStop->setEnabled(false);
        break;
    case MainWindow::ScanState::ssReady:
        ui->actionQuit->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionHelp_content->setEnabled(true);

        ui->actionEdit->setEnabled(true);
        ui->actionScan->setEnabled(true);
        ui->actionStop->setEnabled(false);
        ui->actionNew->setEnabled(true);
        ui->btnScan->setEnabled(true);
        ui->btnStop->setEnabled(false);
        break;
    case MainWindow::ScanState::ssScan:
        ui->actionQuit->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionHelp_content->setEnabled(true);

        ui->actionEdit->setEnabled(false);
        ui->actionScan->setEnabled(false);
        ui->actionStop->setEnabled(true);
        ui->actionNew->setEnabled(false);
        ui->btnScan->setEnabled(false);
        ui->btnStop->setEnabled(true);
        break;
    case MainWindow::ScanState::ssEdit:
        ui->actionQuit->setEnabled(false);
        ui->actionAbout->setEnabled(false);
        ui->actionHelp_content->setEnabled(false);

        ui->actionEdit->setEnabled(false);
        ui->actionScan->setEnabled(false);
        ui->actionStop->setEnabled(false);
        ui->actionNew->setEnabled(false);
        ui->btnScan->setEnabled(false);
        ui->btnStop->setEnabled(false);
        break;
    case MainWindow::ScanState::ssFailure:
    default:
        ui->actionQuit->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionHelp_content->setEnabled(true);

        ui->actionEdit->setEnabled(false);
        ui->actionScan->setEnabled(false);
        ui->actionStop->setEnabled(false);
        ui->actionNew->setEnabled(false);
        ui->btnScan->setEnabled(false);
        ui->btnStop->setEnabled(false);
        break;
    }
    return ss;
}

void MainWindow::on_actionScan_triggered()
{
    SS = ScanState::ssScan;
    //TODO: scan ui->treeView for checked elements; try checked directories and PE
}

void MainWindow::on_actionStop_triggered()
{
    SS = ScanState::ssReady;
}
