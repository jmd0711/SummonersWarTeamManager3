#include "monsterfilterproxymodel.h"

MonsterFilterProxyModel::MonsterFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    sortBy = MonsterFilterProxyModel::DEFAULT;
}

bool MonsterFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    Monster *leftData = sourceModel()->data(source_left, Qt::UserRole).value<Monster*>();
    Monster *rightData = sourceModel()->data(source_right, Qt::UserRole).value<Monster*>();

    bool defaultBool = leftData->getId() < rightData->getId();
    switch(sortBy)
    {
    case NAME:
        if(!(QString::localeAwareCompare(leftData->getName(), rightData->getName()) == 0))
            return QString::localeAwareCompare(leftData->getName(), rightData->getName()) < 0;
        break;
    case PRIORITY:
        if (!(leftData->getPriority() == rightData->getPriority()))
            return leftData->getPriority() < rightData->getPriority();
        break;
    default:
        return defaultBool;
    }
    return defaultBool;
}

void MonsterFilterProxyModel::setSortBy(const MonsterFilterProxyModel::SortBy &value)
{
    sortBy = value;
}
