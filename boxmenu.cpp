#include "boxmenu.h"
#include "ui_boxmenu.h"

BoxMenu::BoxMenu(MonsterListModel *mLM, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxMenu),
    mListModel(mLM)
{
    ui->setupUi(this);

    auto proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(mListModel);

    //ui->setModel(proxyModel);
    ui->listView->setModel(proxyModel);
    connect(ui->listView, &QListView::clicked, mLM, &MonsterListModel::itemDoubleClicked);
//    monsterListWidget = new MonsterListView(profile, MonsterListView::BOX, this);
//    ui->scrollArea->setWidgetResizable(true);
//    ui->scrollArea->
}

BoxMenu::~BoxMenu()
{
    delete ui;
}
