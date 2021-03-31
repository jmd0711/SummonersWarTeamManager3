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

    auto proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(tListModel);
    proxyModel->setFilterRole(Qt::ToolTipRole);
    proxyModel->setFilterRegExp(QRegExp(battleName, Qt::CaseInsensitive, QRegExp::FixedString));

    ui->listView->setModel(proxyModel);
    connect(ui->listView, &QListView::clicked, this, &TeamMenu::teamSelected);

    tDelegate = new TeamMenuItemDelegate(this);
    ui->listView->setItemDelegate(tDelegate);
}

TeamMenu::~TeamMenu()
{
    delete ui;
}

void TeamMenu::teamSelected(const QModelIndex &index)
{
    TeamDisplay teamDisplay(battleName);
    teamDisplay.editContents(tListModel->data(index, Qt::UserRole));

    switch (teamDisplay.exec())
    {
    case TeamDisplay::DELETE:
        tListModel->removeRow(index.row());
        break;
    case TeamDisplay::EDIT:
        QVariant mon = QVariant::fromValue(teamDisplay.getTeamChange());
        tListModel->setData(index, mon, Qt::EditRole);
        break;
    }
}

void TeamMenu::on_addButton_released()
{
    Team *team = new Team(battleName);
    //team->setTeamName(battleName);
    tListModel->addRow(team);
}
