#include "teamlistmodel.h"

TeamListModel::TeamListModel(Profile *pr, QObject *parent)
    : QAbstractListModel(parent),
      profile(pr)
{
}

int TeamListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return profile->teamsSize();
}

QVariant TeamListModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    Team *result = profile->getTeam(row);
    switch (role) {
    case Qt::DisplayRole:
        return result->getTeamName();
    case Qt::ToolTipRole:
        return result->getBattle();
    case Qt::UserRole:
        QVariant team = QVariant::fromValue(result);
        return team;
    }
    return QVariant();
}

bool TeamListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        Team *currentTeam = profile->getTeam(index.row());
        const Team teamChange = value.value<Team>();
        currentTeam->setTeamName(teamChange.getTeamName());
        currentTeam->setTeamDescription(teamChange.getTeamDescription());

        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }
    return false;
}

Qt::ItemFlags TeamListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractListModel::flags(index) | Qt::ItemIsEnabled;
}

bool TeamListModel::addRow(Team *team)
{
    beginInsertRows(QModelIndex(), profile->teamsSize(), profile->teamsSize());
    profile->addTeam(team);
    endInsertRows();
    return true;
}

bool TeamListModel::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    profile->removeTeamAt(row);
    endRemoveRows();
    return true;
}
