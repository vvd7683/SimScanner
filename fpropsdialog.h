#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QFileInfo>
#include <QtCharts/QChartView>
#include <QLayout>

#include "pe_parser/peParser.h"

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
    QFileInfo &info;
    QtCharts::QChartView *chartEntropy;
    QtCharts::QChartView *chartEntropyDerivative;
private:
    Ui::FilePropertiesDialog *ui;
};

#endif // CHARTDIALOG_H
