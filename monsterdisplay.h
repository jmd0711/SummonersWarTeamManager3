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
        DELETE,
        ADD,
        REMOVE,
    };
    explicit MonsterDisplay(Task t, QWidget *parent = nullptr);
    ~MonsterDisplay();

    void editContents(QVariant monPointer);

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

    Task task;
};

#endif // MONSTERDISPLAY_H
