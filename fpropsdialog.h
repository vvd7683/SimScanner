#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

/*
 * File properties dialog class
 */
#include <QDialog>
#include <QFileInfo>
#include <QtCharts/QChartView>
#include <QLayout>
#include <QFile>
#include <QDateTime>
#include <QMenu>
#include <QToolBar>

#include "qpefile.h"
#include "entropychartview.h"
#include "qchartlayout.h"
#include "qchartdialog.h"
#include "structuretree.h"
#include "entropychartitem.h"
#include "spropsdialog.h"
#include "ss_types.h"
#include "nnprofilesdialog.h"

namespace Ui {
class FilePropertiesDialog;
}

class FilePropertiesDialog : public QChartDialog
{
    Q_OBJECT

public:
    explicit FilePropertiesDialog(QFileInfo &Info,
                                  SsMode mode = SsMode::ssmScan,
                                  QWidget *parent = 0);
    ~FilePropertiesDialog();

    QMenu *section_menu;
    QToolBar *file_tool_bar;

    StructureTree *structureTree;

    inline void init_sections();
    inline void init_directories();
private slots:
    void on_rbDerivative_toggled(bool checked);

    void on_rbEntropy_toggled(bool checked);

    void on_rbMaximums_toggled(bool checked);

    void on_rbMinimums_toggled(bool checked);

    void on_rbExtremums_toggled(bool checked);

    void on_structureTree_itemSelectionChanged();

    void on_actionView_Section_properties_triggered();

    void on_actionView_Section_associated_neuroprofiles_triggered();

public slots:
    void tvContextMenuRequested(const QPoint &pos);

private:
    Ui::FilePropertiesDialog *ui;
    QPeFile pe_file;
};

#endif // CHARTDIALOG_H
