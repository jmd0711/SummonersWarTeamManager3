//#include "teamlistview.h"
//#include "ui_teamlistview.h"

//TeamListView::TeamListView(Profile *pr, QString name, QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::TeamListView),
//    profile{ pr },
//    battleName{ name }
//{
//    ui->setupUi(this);

//    layout = new QVBoxLayout();
//    layout->setAlignment(Qt::AlignTop);
//    this->setLayout(layout);

//    for (int i = 0; i < pr->getTeamsCount(battleName); i++)
//    {
//        addTeam();
//    }

//    connect(profile, &Profile::teamAdded, this, &TeamListView::onTeamAdded);
//    connect(profile, &Profile::teamDeleted, this, &TeamListView::onTeamDeleted);
//}

//TeamListView::~TeamListView()
//{
//    delete ui;
//}

//void TeamListView::addTeam()
//{
//    int initialCount;
//    if (profile->teamExists(battleName, teamCount))
//        initialCount = profile->getMonsterCount(battleName, teamCount);
//    else
//        initialCount = 0;
//    TeamWidget *teamWidget = new TeamWidget(profile, battleName, teamCount, initialCount, this);
//    connect(teamWidget, &TeamWidget::deleteReleased, profile, &Profile::onTeamDeleteReleased);

//    layout->addWidget(teamWidget);
//    //teamWidget->setMonsterCount(profile->getMonsterCount(battleName, teamCount));
//    teamCount++;
//}

//void TeamListView::deleteTeam()
//{
//    if (teamCount == 0)
//        return;
//    teamCount--;

//    QLayoutItem *item = layout->itemAt(teamCount);
//    QWidget *widget = item->widget();
//    layout->removeWidget(widget);
//    widget->close();
//}

//void TeamListView::onTeamAdded(QString name)
//{
//    if (name == battleName)
//    {
//        addTeam();
//    }
//}

//void TeamListView::onTeamDeleted(int indexFiltered, QString name)
//{
//    if (name == battleName)
//    {
//        deleteTeam();
//        for (int i = indexFiltered; i < teamCount; i++)
//        {
//            QLayoutItem *item = layout->itemAt(i);
//            QWidget *widget = item->widget();
//            TeamWidget *teamWidget = dynamic_cast<TeamWidget *>(widget);
//            teamWidget->setTeamIndex(teamWidget->getTeamIndex() - 1);
//        }
//    }
//}
