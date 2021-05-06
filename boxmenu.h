#ifndef BOXMENU_H
#define BOXMENU_H

#include <QDesktopWidget>
#include <QInputDialog>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QUrl>
#include <QUrlQuery>
#include <QUuid>
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
    void enableAddButton(bool isEnabled);

signals:
    void addSelected(Monster *monster);

private slots:
    void addSelectedMonster(Monster *monster);

    void monsterSelected(const QModelIndex &proxyIndex);

    void onMonstersReceived(QNetworkReply *reply);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_addButton_released();

private:
    Ui::BoxMenu *ui;
    MonsterDisplay::Task t;

    MonsterListModel *mListModel;
    MonsterFilterProxyModel *proxyModel;
    QListView *listView;

    Profile *addProfile;
    MonsterListModel *addListModel;
};

#endif // BOXMENU_H
