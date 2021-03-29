#ifndef MONSTERDISPLAY_H
#define MONSTERDISPLAY_H

#include <QDialog>

#include "profile.h"

namespace Ui {
class MonsterDisplay;
}

class MonsterDisplay : public QDialog
{
    Q_OBJECT

public:
    enum Task
    {
        DELETE = 1,
        ADD = 2,
        REMOVE = 3,
        EDIT = 4,
    };
    explicit MonsterDisplay(Task t, QWidget *parent = nullptr);
    ~MonsterDisplay();

    void editContents(QVariant monsterData);

    Monster getDataChange() const;

private slots:
    void on_editButton_released();

    void on_doButton_released();

private:
    Ui::MonsterDisplay *ui;

    Monster dataChange;
    Task task;
};

#endif // MONSTERDISPLAY_H
