//#include "monsterlistview.h"
//#include "ui_monsterlistview.h"

//MonsterListView::MonsterListView(Profile *pr, Purpose pu, QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::MonsterListView),
//    profile{ pr },
//    purpose{ pu }
//{
//    ui->setupUi(this);

//    layout = new QGridLayout();
//    this->setLayout(layout);

//    for (int i = 0; i < pr->getMonsterCount(); i++)
//    {
//        addButton();
//    }

//    connect(profile, &Profile::monsterAdded, this, &MonsterListView::onMonsterAdded);
//    connect(profile, &Profile::monsterDeleted, this, &MonsterListView::onMonsterDeleted);
//    connect(profile, &Profile::monsterUpdated, this, &MonsterListView::onMonsterUpdated);
//}

//MonsterListView::~MonsterListView()
//{
//    delete ui;
//}

//void MonsterListView::addButton()
//{
//    int row = buttonCount / maxColumns;
//    int column = buttonCount % maxColumns;

//    QToolButton *button = new QToolButton(this);
//    button->setText("");
//    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    button->setMinimumSize(QSize(150, 150));
//    policy.setHeightForWidth(true);
//    button->setSizePolicy(policy);
//    button->setAutoFillBackground(true);
//    QPalette palette = button->palette();
//    palette.setColor(QPalette::Button, QColor(0, 0, 0));
//    button->setPalette(palette);
//    button->setIconSize(QSize(145,145));
//    button->setAttribute(Qt::WA_DeleteOnClose);

//    layout->addWidget(button, row, column);

//    connect(button, &QToolButton::released, this, &MonsterListView::onButtonReleased);
//    buttonCount++;
//    updateButton(buttonCount - 1);
//}

//void MonsterListView::deleteButton()
//{
//    if (buttonCount == 0)
//        return;
//    buttonCount--;

//    int row = buttonCount / maxColumns;
//    int column = buttonCount % maxColumns;

//    QLayoutItem *item = layout->itemAtPosition(row, column);
//    QWidget *widget = item->widget();
//    widget->close();
//    layout->removeWidget(widget);
//}

//void MonsterListView::updateButton(int index)
//{
//    int row = index / maxColumns;
//    int column = index % maxColumns;

//    QLayoutItem *item = layout->itemAtPosition(row, column);
//    QWidget *widget = item->widget();
//    QToolButton *button = dynamic_cast<QToolButton *>(widget);

//    button->setIcon(profile->getMonster(index)->getImage());
//}

//void MonsterListView::onMonsterAdded()
//{
//    addButton();
//}

//void MonsterListView::onMonsterDeleted(int index)
//{
//    deleteButton();
//    for (int i = index; i < buttonCount; i++)
//        updateButton(i);
//}

//void MonsterListView::onMonsterUpdated(int index)
//{
//    updateButton(index);
//}

//void MonsterListView::onButtonReleased()
//{
//    QToolButton *button = dynamic_cast<QToolButton *>(sender());
//    int index =layout->indexOf(button);

//    MonsterDisplay *disp;
//    switch(purpose)
//    {
//    case MonsterListView::BOX:
//         disp = new MonsterDisplay(profile, profile->getMonster(index), MonsterDisplay::DELETE, this);
//         connect(disp, &MonsterDisplay::deleteReleased, profile, &Profile::onMonsterDeleteReleased);
//        break;
//    case MonsterListView::REQUEST:
//        disp = new MonsterDisplay(profile, profile->getMonster(index), MonsterDisplay::ADD, this);
//        connect(disp, &MonsterDisplay::addReleased, profile, &Profile::onMonsterAddReleased);
//        break;
//    }
//    disp->show();
//}

//int MonsterListView::getTeamIndex() const
//{
//    switch (purpose)
//    {
//    case MonsterListView::BOX:
//        return NULL;
//    case MonsterListView::REQUEST:
//        return teamIndex;
//    }
//}

//void MonsterListView::setTeamIndex(int value)
//{
//    switch (purpose)
//    {
//    case MonsterListView::BOX:
//        return;
//    case MonsterListView::REQUEST:
//        teamIndex = value;
//        break;
//    }
//}

//QString MonsterListView::getBattleName() const
//{
//    switch (purpose)
//    {
//    case MonsterListView::BOX:
//        return NULL;
//    case MonsterListView::REQUEST:
//        return battleName;
//    }
//}

//void MonsterListView::setBattleName(const QString &value)
//{
//    switch (purpose)
//    {
//    case MonsterListView::BOX:
//        return;
//    case MonsterListView::REQUEST:
//        battleName = value;
//    }
//}
