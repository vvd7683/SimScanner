#ifndef ADDNEWDIALOG_H
#define ADDNEWDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "scanmodel.h"
#include "fpropsdialog.h"
#include "qpefile.h"
#include "qpefilemenu.h"
#include "selectedsampleitem.h"
#include "ss_defs.h"

namespace Ui {
class addNewDialog;
}

class addNewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addNewDialog(QWidget *parent = 0);
    ~addNewDialog();
    QString getSampleFamily();
    int getSampleIndex();
    QVector<QFileInfo>getSelectedSamples();
    QVector<QFileInfo>getNegativeSamples();

public slots:
    void tvPositiveContextMenuRequested(const QPoint &pos);
    void tvSelectedContextMenuRequested(const QPoint &pos);
    void trySampleSlot(bool checked);
    void slotAppendSample(const QModelIndex &c_idx);
    void slotRemoveSample(const QModelIndex &c_idx);

private slots:
    void on_actionRemove_sample_triggered();

    void on_actionView_PE_properties_triggered();

    void on_tvSelectedSamples_customContextMenuRequested(const QPoint &pos);

private:
    Ui::addNewDialog *ui;
    QPeFileMenu *menu_PE;
    QMenu selected_menu;
    ScanModel *negative_model;
    ScanModel *positive_model;
};

#endif // ADDNEWDIALOG_H
