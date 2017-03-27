#ifndef SCANMODEL_H
#define SCANMODEL_H

#include <QDirModel>
#include <QSet>
#include <QPersistentModelIndex>

class ScanModel : public QDirModel //Look here http://www.programmershare.com/2041913/
{
public:
    ScanModel();
    QSet<QPersistentModelIndex> checkedIndexes;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
private:
    void recursiveCheck(const QModelIndex &index, const QVariant &value);
};


#endif // SCANMODEL_H
