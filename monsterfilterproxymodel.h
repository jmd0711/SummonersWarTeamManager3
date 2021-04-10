#ifndef MONSTERFILTERPROXYMODEL_H
#define MONSTERFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

#include "profile.h"

class MonsterFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    enum SortBy
    {
        NAME,
        PRIORITY,
        DEFAULT,
    };
    MonsterFilterProxyModel(QObject *parent = 0);


    void setSortBy(const MonsterFilterProxyModel::SortBy &value);

protected:
    //bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

private:
    MonsterFilterProxyModel::SortBy sortBy;
};

#endif // MONSTERFILTERPROXYMODEL_H
