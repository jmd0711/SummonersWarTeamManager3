#ifndef MONSTERDISPLAY_H
#define MONSTERDISPLAY_H

#include <QDialog>

#include "monster.h"
#include "profile.h"

class MonsterListView;
class TeamWidget;

namespace Ui {
class MonsterDisplay;
}

class MonsterDisplay : public QDialog
{
    Q_OBJECT

public:
    enum Task
    {
        DELETE,
        ADD,
        REMOVE,
    };
    explicit MonsterDisplay(Profile *pr, Monster *monster, Task t, MonsterListView *parent = nullptr);
    explicit MonsterDisplay(Profile *pr, Monster *monster, Task t, TeamWidget *parent = nullptr);
    ~MonsterDisplay();

private slots:
    void onDeleteReleased();

    void onAddReleased();

    void onRemoveReleased();

    void on_editButton_released();

signals:
    void deleteReleased(int index);

    void addReleased(QString battleName, int indexFiltered, int monsterIndex);

    void removeReleased(QString battleName, int indexFiltered, int monsterIndex);

private:
    Ui::MonsterDisplay *ui;

    Profile *profile;
    Monster *monster;

    Task task;

    //  Only used for ADD or REMOVE
    QString battleName;
    int teamIndex;
};

#endif // MONSTERDISPLAY_H
