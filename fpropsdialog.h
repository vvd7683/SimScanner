#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QFileInfo>
#include <QtCharts/QChart>

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
private:
    Ui::FilePropertiesDialog *ui;
};

#endif // CHARTDIALOG_H
