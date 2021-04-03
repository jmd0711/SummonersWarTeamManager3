//#include <QtGui>

//#include "teammenuitemdelegate.h"

//TeamMenuItemDelegate::TeamMenuItemDelegate(QObject *parent)
//    : QItemDelegate(parent)
//{

//}

//void TeamMenuItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QString teamName = index.model()->data(index, Qt::DisplayRole).toString();
//    const Team team = index.model()->data(index, Qt::UserRole).value<Team>();

//    drawDisplay(painter, option, option.rect, teamName);
//    foreach (Monster *mon, team.getMonsters())
//    {
//        drawDecoration(painter, option, option.rect, QPixmap::fromImage(mon->getImage()));
//    }

//    QStyleOptionButton addButton;
//    QRect r = option.rect;
//    int x = r.left() + r.width() - 140;
//    int y = r.top();
//    int w = 140;
//    int h = 140;
//    int offset = 10;
//    addButton.rect = QRect(x + offset, y + offset, w - (2 * offset), h - (2 * offset));
//    addButton.text = "+";
//    addButton.state = QStyle::State_Enabled;
//    QApplication::style()->drawControl(QStyle::CE_PushButton, &addButton, painter);
//}

//bool TeamMenuItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
//{
//    if (event->type() == QEvent::MouseButtonRelease)
//    {
//        QMouseEvent * e = (QMouseEvent *)event;
//        int clickX = e->x();
//        int clickY = e->y();

//        QRect r = option.rect;
//        int x = r.left() + r.width() - 140;
//        int y = r.top();
//        int w = 140;
//        int h = 140;
//        int offset = 10;

//        if (clickX > x + offset && clickX < x + w - offset && clickY > y + offset && clickY < y + h - offset)
//        {
//            //  DO MONSTER SELECTION
//            return false;
//        }
//    }
//    return false;
//}
