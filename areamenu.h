#ifndef AREAMENU_H
#define AREAMENU_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class TeamManager;

class AreaMenu : public QWidget
{
    Q_OBJECT

public:
    explicit AreaMenu(int index, QVector<QString> battleNames, TeamManager *parent = nullptr);
    ~AreaMenu();

private:

    int layoutIndex;
    int maxRows = 2;
    QGridLayout *layout;
};

#endif // AREAMENU_H
