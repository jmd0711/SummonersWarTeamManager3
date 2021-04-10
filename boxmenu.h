#ifndef BOXMENU_H
#define BOXMENU_H

#include <QListView>
#include <QSortFilterProxyModel>
#include <QWidget>

//#include "monsterlistview.h"
#include "monsterdisplay.h"
#include "monsterfilterproxymodel.h"
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

    MonsterDisplay::Task getTask() const;
    void setTask(const MonsterDisplay::Task &value);

signals:
    void addSelected(Monster *monster);

private slots:
    void monsterSelected(const QModelIndex &proxyIndex);

    //void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::BoxMenu *ui;
    MonsterDisplay::Task t;

    MonsterListModel *mListModel;
    MonsterFilterProxyModel *proxyModel;
    QListView *listView;
};

#endif // BOXMENU_H
