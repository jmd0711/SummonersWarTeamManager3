#include "boxmenu.h"
#include "ui_boxmenu.h"

BoxMenu::BoxMenu(MonsterListModel *mLM, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxMenu),
    mListModel{ mLM }
{
    ui->setupUi(this);

    auto proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(mListModel);

    ui->listView->setModel(proxyModel);
    connect(ui->listView, &QListView::clicked, this, &BoxMenu::monsterSelected);
}

BoxMenu::~BoxMenu()
{
    delete ui;
}

void BoxMenu::monsterSelected(const QModelIndex &index)
{
    MonsterDisplay monDisplay(MonsterDisplay::Task::DELETE);
    monDisplay.editContents(mListModel->data(index, Qt::UserRole));

    switch (monDisplay.exec())
    {
    case MonsterDisplay::DELETE:
        mListModel->removeRow(index.row());
        break;
    case MonsterDisplay::EDIT:
        QVariant mon = QVariant::fromValue(monDisplay.getDataChange());
        mListModel->setData(index, mon, Qt::EditRole);
        break;
    }
}

void BoxMenu::on_addButton_released()
{

}
