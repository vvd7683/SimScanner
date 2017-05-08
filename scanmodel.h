#ifndef SCANMODEL_H
#define SCANMODEL_H

/*
 * Class of treeview model mapping filesystem
 */
#include <QDirModel>
#include <QFileInfo>
#include <QSet>
#include <QPersistentModelIndex>

#include "macro.h"

class ScanModel : public QDirModel //Look here http://www.programmershare.com/2041913/
{
    Q_OBJECT
public:
    ScanModel();
    QSet<QPersistentModelIndex> checkedIndexes;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QFileInfo get_file_info(const QModelIndex &c_idx);
    QVector<QModelIndex>getChecked();

Q_SIGNALS:
    void signalAppendFile(const QModelIndex &index);
    void signalRemoveFile(const QModelIndex &index);
protected:
    QString get_full_path(QModelIndex idx);
private:
    void recursiveCheck(const QModelIndex &index, const QVariant &value);
};


#endif // SCANMODEL_H
