#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <QMenu>
#include <QMessageBox>
#include <QStringListModel>

#include "scanmodel.h"
#include "pe_parser/peParser.h"
#include "fpropsdialog.h"
#include "qpefilemenu.h"
#include "aboutdialog.h"
#include "addnewdialog.h"
#include "macro.h"
#include "ss_types.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    QPeFileMenu *menu_PE;
    QMenu *menu_Dir, *menu_Other;
public slots:
    void tvContextMenuRequested(const QPoint &pos);
    void peInfoExecute(bool checked);
    void setStatus(QString &status);
private slots:
    void on_pushButton_clicked();

    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    enum ScanState {
        ssNotInitialized = 0,
        ssReady,
        ssScan,
        ssEdit,
        ssFailure,

        ssCount
    } ss;

    ScanState get_ss() {return ss;}
    ScanState set_ss(ScanState _ss);
    __declspec( property( get=get_ss, put=set_ss) ) ScanState SS;
    SsMode get_ssm();
    SsMode set_ssm(SsMode _ssm);
    __declspec( property( get=get_ssm, put=set_ssm) ) SsMode SSmode;
};

#endif // MAINWINDOW_H
