#ifndef NNPROFILESDIALOG_H
#define NNPROFILESDIALOG_H

#include <QDialog>

namespace Ui {
class NnProfilesDialog;
}

class NnProfilesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NnProfilesDialog(QWidget *parent = 0);
    ~NnProfilesDialog();

private:
    Ui::NnProfilesDialog *ui;
};

#endif // NNPROFILESDIALOG_H
