#include "scanmodel.h"

ScanModel::ScanModel()
{
}

Qt::ItemFlags ScanModel::flags(const QModelIndex &index) const
{
    return QDirModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant ScanModel::data(const QModelIndex &index, int role) const
{
    if(index.column() == 0) {
        if(role == Qt::CheckStateRole)
        {
            return checkedIndexes.contains(index) ? Qt::Checked : Qt::Unchecked;
        }
    }
    return QDirModel::data(index, role);
}

bool ScanModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::CheckStateRole)
    {
        if(value == Qt::Checked)
        {
            checkedIndexes.insert(index);
            if(hasChildren(index) == true)
            {
                recursiveCheck(index, value);
            }
        }
        else
        {
            checkedIndexes.remove(index);
            if(hasChildren(index) == true)
            {
                recursiveCheck(index, value);
            }
        }
        emit dataChanged(index, index);
        return true;
    }

    return QDirModel::setData(index, value, role);
}

void ScanModel::recursiveCheck(const QModelIndex &index, const QVariant &value)
{
    if(hasChildren(index))
    {
        int i;
        int childrenCount = rowCount(index);
        QModelIndex child;
        for(i=0; i<childrenCount; i++)
        {
            child = QDirModel::index(i, 0, index);
            setData(child, value, Qt::CheckStateRole);
        }
    }
}
