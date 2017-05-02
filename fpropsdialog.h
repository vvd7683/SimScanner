#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QFileInfo>
#include <QtCharts/QChartView>
#include <QLayout>
#include <QFile>
#include <QDateTime>

#include "qpefile.h"
#include "entropychartview.h"
#include "qchartlayout.h"
#include "structuretree.h"
#include "entropychartitem.h"
#include "spropsdialog.h"

namespace Ui {
class FilePropertiesDialog;
}

class FilePropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilePropertiesDialog(QFileInfo &Info, QWidget *parent = 0);
    ~FilePropertiesDialog();

protected:
    EntropyChartView *chartEntropy;
    EntropyChartView *chartEntropyDerivative;
    ExtremumDensityChartView *chartMaximumDensity;
    ExtremumDensityChartView *chartMinimumDensity;
    ExtremumDensityChartView *chartExtremumDensity;

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
public slots:
    void tvContextMenuRequested(const QPoint &pos);

private:
    Ui::FilePropertiesDialog *ui;
    QPeFile pe_file;
};

#endif // CHARTDIALOG_H
