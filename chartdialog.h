#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>

namespace Ui {
class ChartDialog;
}

class ChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChartDialog(QWidget *parent = 0);
    ~ChartDialog();

private:
    Ui::ChartDialog *ui;
};

#endif // CHARTDIALOG_H
