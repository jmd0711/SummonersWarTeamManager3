#ifndef TEAMMENU_H
#define TEAMMENU_H

#include <QDataWidgetMapper>
#include <QDesktopWidget>
#include <QDialog>
#include <QIcon>
#include <QLineEdit>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "boxmenu.h"
#include "monsterdisplay.h"
#include "monsterlistmodel.h"
#include "profile.h"
#include "teamdisplay.h"
#include "teamlistmodel.h"
#include "teammenuitemdelegate.h"

namespace Ui {
class TeamMenu;
}

class TeamMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TeamMenu(MonsterListModel *mLM, TeamListModel *tLM, QString name, QWidget *parent = nullptr);
    ~TeamMenu();

private slots:
    //void teamSelected(const QModelIndex &index);

    void on_addButton_released();

    void updatePage(int row);

    void on_editButton_released();

    void on_deleteButton_released();

    void addSelectedMonster(Monster *monster);

    void onRowsInserted(const QModelIndex &parent, int first, int last);

    void onRowsRemoved(const QModelIndex &parent, int first, int last);

private:
    Ui::TeamMenu *ui;
    int maxMonsters;

    QString battleName;

    TeamListModel *tListModel;
    QSortFilterProxyModel *tProxyModel;

    MonsterListModel *mListModel;
    //TeamMenuItemDelegate *tDelegate;

    QDataWidgetMapper *mapper;
    QVector<QToolButton*> monButtons;

    void handleMonsterButton();
};

#endif // TEAMMENU_H
