#include "teammenu.h"
#include "ui_teammenu.h"

TeamMenu::TeamMenu(TeamListModel *tLM, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamMenu),
    battleName{ name },
    tListModel{ tLM }
{
    ui->setupUi(this);
    ui->label->setText(battleName);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(tListModel);
    proxyModel->setFilterRole(Qt::ToolTipRole);
    proxyModel->setFilterRegExp(QRegExp(battleName, Qt::CaseInsensitive, QRegExp::FixedString));

    //TODO use QDataWidgetMapper instead
    //ui->listView->setModel(proxyModel);
    //connect(ui->listView, &QListView::clicked, this, &TeamMenu::teamSelected);

    //tDelegate = new TeamMenuItemDelegate(this);
    //ui->listView->setItemDelegate(tDelegate);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(proxyModel);
    if (proxyModel->rowCount() < 1)
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
    QModelIndex proxyIndex = proxyModel->index(mapper->currentIndex(), 0);
    QModelIndex index = proxyModel->mapToSource(proxyIndex);
    //QModelIndex index = tListModel->index(row);
    const Team team = tListModel->data(index, Qt::UserRole).value<Team>();

    ui->lineEdit->setText(team.getTeamName());
    ui->textEdit->setText(team.getTeamDescription());

    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < proxyModel->rowCount() - 1);
}

void TeamMenu::on_editButton_released()
{
    QModelIndex proxyIndex = proxyModel->index(mapper->currentIndex(), 0);
    QModelIndex index = proxyModel->mapToSource(proxyIndex);

    Team dataChange(battleName);
    dataChange.setTeamName(ui->lineEdit->text());
    dataChange.setTeamDescription(ui->textEdit->toPlainText());

    QVariant team = QVariant::fromValue(dataChange);
    tListModel->setData(index, team, Qt::EditRole);
}

void TeamMenu::on_deleteButton_released()
{
    int row = mapper->currentIndex();
    QModelIndex proxyIndex = proxyModel->index(row, 0);
    QModelIndex index = proxyModel->mapToSource(proxyIndex);

    if (row > 0)
    {
        //  mapper currently at pos 1+
        tListModel->removeRow(index.row());
        mapper->setCurrentIndex(row - 1);
    }
    else if (proxyModel->rowCount() > 1)
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
