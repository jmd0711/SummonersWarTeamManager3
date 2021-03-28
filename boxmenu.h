#ifndef BOXMENU_H
#define BOXMENU_H

#include <QListView>
#include <QSortFilterProxyModel>
#include <QWidget>

//#include "monsterlistview.h"
#include "monsterListmodel.h"
#include "profile.h"

namespace Ui {
class BoxMenu;
}

class BoxMenu : public QWidget
{
    Q_OBJECT

public:
    explicit BoxMenu(MonsterListModel *mLM, QWidget *parent = nullptr);
    ~BoxMenu();

private:
    Ui::BoxMenu *ui;

    MonsterListModel *mListModel;
    //QListView listView;

//    MonsterListView *monsterListWidget;
};

#endif // BOXMENU_H
