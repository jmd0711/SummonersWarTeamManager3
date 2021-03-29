#include "monsterlistmodel.h"

MonsterListModel::MonsterListModel(Profile *pr, QObject *parent)
    : QAbstractListModel(parent),
      profile(pr)
{
}

//QVariant MonsterListModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

//bool MonsterListModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}

int MonsterListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!

    return profile->monstersSize();
}

QVariant MonsterListModel::data(const QModelIndex &index, int role) const
{
//    if (!index.isValid())
//        return QVariant();

//    // FIXME: Implement me!
//    return QVariant();
    const int row = index.row();
    Monster *result = profile->getMonster(row);
    switch (role) {
    case Qt::DisplayRole:
        return result->getName();
    case Qt::DecorationRole:
        return result->getImage();
    case Qt::UserRole:
        QVariant mon = QVariant::fromValue(*result);
        return mon;
    }
    return QVariant();
}

bool MonsterListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        Monster *currentMonster = profile->getMonster(index.row());
        const Monster dataChange = value.value<Monster>();
        currentMonster->setAccuracy(dataChange.getAccuracy());
        currentMonster->setAttack(dataChange.getAttack());
        currentMonster->setCritDamage(dataChange.getCritDamage());
        currentMonster->setCritRate(dataChange.getCritRate());
        currentMonster->setDefense(dataChange.getDefense());
        currentMonster->setDescription(dataChange.getDescription());
        currentMonster->setHp(dataChange.getHp());
        currentMonster->setLevel(dataChange.getLevel());
        currentMonster->setName(dataChange.getName());  //  change to textedit
        currentMonster->setPriority(dataChange.getPriority());
        currentMonster->setResistance(dataChange.getResistance());
        currentMonster->setSpeed(dataChange.getSpeed());
        currentMonster->setStars(dataChange.getStars());
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }

    return false;
//    if (data(index, role) != value) {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }
//    return false;
}

Qt::ItemFlags MonsterListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool MonsterListModel::addRow(Monster *mon)
{
    //beginInsertRows(parent, row, row + count - 1);
    beginInsertRows(QModelIndex(), profile->monstersSize(), profile->monstersSize());
    profile->addMonster(mon);
    endInsertRows();
    return true;
}

bool MonsterListModel::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    profile->removeMonsterAt(row);
    endRemoveRows();
    return true;
}

void MonsterListModel::itemDoubleClicked(const QModelIndex &index)
{
    removeRow(index.row());
}
