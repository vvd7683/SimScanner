#ifndef SPROPSDIALOG_H
#define SPROPSDIALOG_H

/*
 * Class of section properties dialog.
 * Form GUI contains QTabWidget including
 * first table of section structure/dump
 * and second table of entropy charts.
 */
#include <QDialog>
#include <QMenu>
#include <QBoxLayout>
#include <QtCharts/QChart>

#include "qpefile.h"
#include "sectionitem.h"
#include "qchartlayout.h"
#include "qchartdialog.h"
#include "ss_types.h"

namespace Ui {
class SPropsDialog;
}

class SectionPropertiesDialog : public QChartDialog
{
    Q_OBJECT

public:
    explicit SectionPropertiesDialog(SSSection &ss_sec, SsMode mode = SsMode::ssmScan, QWidget *parent = 0);
    ~SectionPropertiesDialog();
private slots:
    void on_rbEntropy_toggled(bool checked);

    void on_rbDerivative_toggled(bool checked);

    void on_rbMaximums_toggled(bool checked);

    void on_rbMinimums_toggled(bool checked);

    void on_rbExtremums_toggled(bool checked);

private:
    Ui::SPropsDialog *ui;
    SSSection &sec;

    //Top nodes
    QMenu *secs_menu;
    QMenu *dirs_menu;

    QMenu *sec_menu;
    QMenu *dir_menu;
};

#endif // SPROPSDIALOG_H
