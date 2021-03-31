#ifndef TEAMDISPLAY_H
#define TEAMDISPLAY_H

#include <QDialog>

#include "profile.h"

namespace Ui {
class TeamDisplay;
}

class TeamDisplay : public QDialog
{
    Q_OBJECT

public:
    enum Task
    {
        DELETE = 1,
        EDIT = 2,
    };
    explicit TeamDisplay(QString battleName, QWidget *parent = nullptr);
    ~TeamDisplay();

    void editContents(QVariant teamData);

    Team getTeamChange() const;

private slots:
    void on_editButton_released();

    void on_deleteButton_released();

private:
    Ui::TeamDisplay *ui;

    Team teamChange;
};

#endif // TEAMDISPLAY_H
