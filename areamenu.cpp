#include "areamenu.h"
#include "teammanager.h"

AreaMenu::AreaMenu(int index, QVector<QString> battleNames, TeamManager *parent) :
    QWidget(parent),
    layoutIndex{ index }
{
    layout = new QGridLayout();
    this->setLayout(layout);

    int columns;
    int column = 0;
    int row = 0;
    int count = 1;
    if (battleNames.size() > maxRows)
    {
       columns = qRound(double(battleNames.size())/double(maxRows));
    }
    else
    {
        columns = maxRows;
    }
    for (QString battleName : battleNames)
    {
        if (column >= columns)
        {
            column = 0;
            row++;
        }
        QPushButton *button = new QPushButton(this);
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        button->setText(battleName);
        connect(button, &QPushButton::released, [parent, index, count]() {
            parent->setPage(index + count);
        });
        count++;
        layout->addWidget(button, row, column++);
        //parent->addToLayout(new TeamMenu(battleName, parent));

//        TeamsLister *teamsLister = new TeamsLister(monsters_m, monsters_m->getTeamsPointer(battleName), this);
//        //teamsListers.push_back(teamsLister);
//        //connect(button, &QPushButton::released, this, );
//        connect(button, SIGNAL(released()), teamsLister, SLOT(openScreen()));
    }
}

AreaMenu::~AreaMenu()
{
}
