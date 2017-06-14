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

    setWindowIcon(QIcon(tr(":/icons/icons/SimScanner.png")));

    ScanModel *model = new ScanModel;
    ui->treeView->setModel(model);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::tvContextMenuRequested);

    QAction *fileInfoAction = new QAction("File information", this);
    connect(fileInfoAction, &QAction::triggered, this, &MainWindow::peInfoExecute);
    menu_PE->addAction(fileInfoAction);
    menu_PE->addAction(new QAction("View PE", this));

    menu_Dir->addAction(new QAction("Scan immediately", this));
    //menu_Dir->addAction(new QAction("Add", this));

    ui->actionAbout->setIcon(QIcon(tr(":/icons/icons/Info.png")));
    ui->actionHelp_content->setIcon(QIcon(tr(":/icons/icons/Help.png")));
    ui->actionQuit->setIcon(QIcon(tr(":/icons/icons/quit.png")));
//Temporary
    menu_Other->addAction(new QAction("Action 1", this));
    menu_Other->addAction(new QAction("Action 2", this));
    menu_Other->addAction(new QAction("Action 3", this));

    SS = ScanState::ssNotInitialized;

    ui->treeView->setColumnWidth(0, 200);

    ui->twModes->findChild<QTabBar *>()->hide();
}

void MainWindow::peInfoExecute(bool checked) {
    if(QFileInfo *info = menu_PE->PeFileInfo) {
        FilePropertiesDialog(*info, SsMode::ssmScan, this).exec();
        menu_PE->PeFileInfo = Q_NULLPTR;
    }
}

void MainWindow::setStatus(QString &status) {
    ui->statusBar->showMessage(status, 2000);
    QStringListModel *model = nullptr;
    if(ui->lvResults->model())
        model = dynamic_cast<QStringListModel *>(ui->lvResults->model());
    if(!model) {
        model = new QStringListModel(this);
        ui->lvResults->setModel(model);
    }
    model->insertRow(model->rowCount());
    model->setData(model->index(
                       PRED(
                           model->rowCount(
                               )
                           ), 0
                       ), status
                   );
}

void MainWindow::tvContextMenuRequested(const QPoint &pos) {
    if(sender() == ui->treeView) {
        ScanModel *model = dynamic_cast<ScanModel *>(ui->treeView->model());
        QModelIndex idx = ui->treeView->indexAt(pos);
        if(idx.column())
            //idx = model->index(idx.row(), 0);
            return;
        //QModelIndex idx = model->index(item_index.row(), 0);

        QFileInfo file_info = model->get_file_info(idx);
        if(file_info.isDir()) {
            menu_Dir->popup(ui->treeView->viewport()->mapToGlobal(pos));
        } else {
            try {
                {
                    QPeFile file(file_info);
                }
                menu_PE->PeFileInfo = &file_info;
                menu_PE->popup(ui->treeView->viewport()->mapToGlobal(pos));
            } catch(...) {
                menu_Other->popup(ui->treeView->viewport()->mapToGlobal(pos));
                menu_PE->PeFileInfo = Q_NULLPTR;
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete menu_PE;
    delete menu_Dir;
    delete menu_Other;
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

SsMode MainWindow::get_ssm() {
    return SsMode::ssmScan;
}

SsMode MainWindow::set_ssm(SsMode _ssm) {
    //TODO: what is it?
    switch(_ssm)
    {
    case ssmScan:
        break;
    case ssmEdit:
        break;
    default:
        SS = ScanState::ssFailure;
        break;
    }
    return SSmode;
}

MainWindow::ScanState MainWindow::set_ss(ScanState _ss) {
    ss = _ss;
    switch(ss)
    {
    case MainWindow::ScanState::ssNotInitialized:
        ui->actionQuit->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionHelp_content->setEnabled(true);

        break;
    case MainWindow::ScanState::ssReady:
        ui->actionQuit->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionHelp_content->setEnabled(true);

        break;
    case MainWindow::ScanState::ssScan:
        ui->actionQuit->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionHelp_content->setEnabled(true);

        break;
    case MainWindow::ScanState::ssEdit:
        ui->actionQuit->setEnabled(false);
        ui->actionAbout->setEnabled(false);
        ui->actionHelp_content->setEnabled(false);

        break;
    case MainWindow::ScanState::ssFailure:
    default:
        ui->actionQuit->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionHelp_content->setEnabled(true);

        setStatus(tr("SimScanner failure"));
        break;
    }
    return ss;
}

