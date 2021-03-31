#ifndef BOXMENU_H
#define BOXMENU_H

#include <QListView>
#include <QSortFilterProxyModel>
#include <QWidget>

//#include "monsterlistview.h"
#include "monsterdisplay.h"
#include "monsterlistmodel.h"
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

private slots:
    void monsterSelected(const QModelIndex &index);

private:
    Ui::BoxMenu *ui;

    MonsterListModel *mListModel;
};

#endif // BOXMENU_H
