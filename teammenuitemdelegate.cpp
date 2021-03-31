#include "teammenuitemdelegate.h"

TeamMenuItemDelegate::TeamMenuItemDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}

void TeamMenuItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString teamName = index.model()->data(index, Qt::DisplayRole).toString();
    const Team team = index.model()->data(index, Qt::UserRole).value<Team>();

    drawDisplay(painter, option, option.rect, teamName);
    foreach (Monster *mon, team.getMonsters())
    {
        drawDecoration(painter, option, option.rect, QPixmap::fromImage(mon->getImage()));
    }
}
