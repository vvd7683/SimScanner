#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <QMenu>
#include <QMessageBox>

#include <opennn.h>
#include <tinyxml2.h>

#include "scanmodel.h"
#include "pe_parser/peParser.h"
#include "fpropsdialog.h"
#include "dbprofile.h"
#include "qpefilemenu.h"

#define PRED(x)     ((x) - 1)
#define SUCC(x)     ((x) + 1)

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
    QVector<SimScanNN *> ssnnProfiles;

    QPeFileMenu *menu_PE;
    QMenu *menu_Dir, *menu_Other;
public slots:
    void tvContextMenuRequested(const QPoint &pos);
    void peInfoExecute(bool checked);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
