#include "teammenu.h"
#include "ui_teammenu.h"

TeamMenu::TeamMenu(MonsterListModel *mLM, TeamListModel *tLM, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamMenu),
    battleName{ name },
    tListModel{ tLM },
    mListModel{ mLM }
{
    ui->setupUi(this);
    ui->label->setText(battleName);

    maxMonsters = 6;
    for (int i = 0; i < maxMonsters; i++)
    {
        QToolButton *monButton = new QToolButton(this);
        monButton->setObjectName("monToolButton" + QString::number(i));
        monButton->setText("+");
        monButton->setMinimumSize(220, 220);
        monButton->setIconSize(QSize(220, 220));
        monButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        monButtons.push_back(monButton);
        ui->monstersHorizontalLayout->addWidget(monButton);
        connect(monButton, &QAbstractButton::released, this, &TeamMenu::handleMonsterButton);
    }

    tProxyModel = new QSortFilterProxyModel(this);
    tProxyModel->setSourceModel(tListModel);
    tProxyModel->setFilterRole(Qt::ToolTipRole);
    tProxyModel->setFilterRegExp(QRegExp(battleName, Qt::CaseInsensitive, QRegExp::FixedString));

    //TODO use QDataWidgetMapper instead
    //ui->listView->setModel(proxyModel);
    //connect(ui->listView, &QListView::clicked, this, &TeamMenu::teamSelected);

    //tDelegate = new TeamMenuItemDelegate(this);
    //ui->listView->setItemDelegate(tDelegate);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(tProxyModel);
    if (tProxyModel->rowCount() < 1)
    {
        Team *team = new Team(battleName);
        tListModel->addRow(team);
    }
    mapper->toFirst();

    connect(ui->previousButton, &QPushButton::released, mapper, &QDataWidgetMapper::toPrevious);
    connect(ui->nextButton, &QPushButton::released, mapper, &QDataWidgetMapper::toNext);
    connect(mapper, &QDataWidgetMapper::currentIndexChanged, this, &TeamMenu::updatePage);

    mapper->toFirst();
}

TeamMenu::~TeamMenu()
{
    delete ui;
}

//void TeamMenu::teamSelected(const QModelIndex &index)
//{
//    TeamDisplay teamDisplay(battleName);
//    teamDisplay.editContents(tListModel->data(index, Qt::UserRole));

//    switch (teamDisplay.exec())
//    {
//    case TeamDisplay::DELETE:
//        tListModel->removeRow(index.row());
//        break;
//    case TeamDisplay::EDIT:
//        QVariant team = QVariant::fromValue(teamDisplay.getTeamChange());
//        tListModel->setData(index, team, Qt::EditRole);
//        break;
//    }
//}

void TeamMenu::on_addButton_released()
{
    Team *team = new Team(battleName);
    //team->setTeamName(battleName);
    tListModel->addRow(team);
    mapper->toLast();
}

void TeamMenu::updatePage(int row)
{
    QModelIndex proxyIndex = tProxyModel->index(mapper->currentIndex(), 0);
    QModelIndex index = tProxyModel->mapToSource(proxyIndex);
    //QModelIndex index = tListModel->index(row);
    const Team *team = tListModel->data(index, Qt::UserRole).value<Team*>();

    ui->lineEdit->setText(team->getTeamName());
    ui->textEdit->setText(team->getTeamDescription());

    for (int i = 0; i < monButtons.size(); i++)
    {
        const Monster *mon = team->getMonster(i);
        if (mon)
            monButtons[i]->setIcon(QIcon(QPixmap::fromImage(mon->getImage())));
        else
            monButtons[i]->setIcon(QIcon());
    }

    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < tProxyModel->rowCount() - 1);
}

void TeamMenu::on_editButton_released()
{
    QModelIndex proxyIndex = tProxyModel->index(mapper->currentIndex(), 0);
    QModelIndex index = tProxyModel->mapToSource(proxyIndex);

    Team dataChange(battleName);
    dataChange.setTeamName(ui->lineEdit->text());
    dataChange.setTeamDescription(ui->textEdit->toPlainText());

    QVariant team = QVariant::fromValue(dataChange);
    tListModel->setData(index, team, Qt::EditRole);
}

void TeamMenu::on_deleteButton_released()
{
    int row = mapper->currentIndex();
    QModelIndex proxyIndex = tProxyModel->index(row, 0);
    QModelIndex index = tProxyModel->mapToSource(proxyIndex);

    if (row > 0)
    {
        //  mapper currently at pos 1+
        tListModel->removeRow(index.row());
        mapper->setCurrentIndex(row - 1);
    }
    else if (tProxyModel->rowCount() > 1)
    {
        //  mapper currently at pos 0 with contents past 1+
        tListModel->removeRow(index.row());
        mapper->setCurrentIndex(0);
    }
    else
    {
        //  mapper currently at pos 0, last to get deleted
        tListModel->removeRow(index.row());
        Team *team = new Team(battleName);
        tListModel->addRow(team);
        mapper->setCurrentIndex(0);
    }
}

void TeamMenu::addSelectedMonster(Monster *monster)
{
    QModelIndex proxyIndex = tProxyModel->index(mapper->currentIndex(), 0);
    QModelIndex index = tProxyModel->mapToSource(proxyIndex);

    Team *team = tListModel->data(index, Qt::UserRole).value<Team*>();

    team->addMonster(monster);
    for (int i = 0; i < monButtons.size(); i++)
    {
        const Monster *mon = team->getMonster(i);
        if (mon)
            monButtons[i]->setIcon(QIcon(QPixmap::fromImage(mon->getImage())));
        else
            monButtons[i]->setIcon(QIcon());
    }
}

void TeamMenu::handleMonsterButton()
{
    QToolButton *monButton = qobject_cast<QToolButton*>(sender());
    int currentIndexInTeam = monButtons.indexOf(monButton);

    QModelIndex proxyIndex = tProxyModel->index(mapper->currentIndex(), 0);
    QModelIndex index = tProxyModel->mapToSource(proxyIndex);

    Team *team = tListModel->data(index, Qt::UserRole).value<Team*>();

    Monster *mon = team->getMonster(currentIndexInTeam);
    if (mon)
    {
        MonsterDisplay monDisplay(MonsterDisplay::REMOVE);
        monDisplay.editContents(mon);
        switch(monDisplay.exec())
        {
        case MonsterDisplay::REMOVE:
            team->removeMonster(mon);
            for (int i = 0; i < monButtons.size(); i++)
            {
                const Monster *mon = team->getMonster(i);
                if (mon)
                    monButtons[i]->setIcon(QIcon(QPixmap::fromImage(mon->getImage())));
                else
                    monButtons[i]->setIcon(QIcon());
            }
            break;
        case MonsterDisplay::EDIT:
            //  TODO
            //QVariant mon = QVariant::fromValue(monDisplay.getDataChange());
            //mListModel->setData(index, mon, Qt::EditRole);
            break;
        default:
            break;
        }
    }
    else
    {
        QDialog *requestWindow = new QDialog(this);
        requestWindow->resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
        QVBoxLayout *requestLayout = new QVBoxLayout(requestWindow);
        BoxMenu *requestMenu = new BoxMenu(mListModel, requestWindow);
        requestMenu->setTask(MonsterDisplay::ADD);

        requestWindow->setLayout(requestLayout);
        requestWindow->layout()->addWidget(requestMenu);
        connect(requestMenu, &BoxMenu::addSelected, this, &TeamMenu::addSelectedMonster);
        requestWindow->exec();
        //team->addMonster(newMon);
    }
}
