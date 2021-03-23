#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

class TeamManager;

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(TeamManager *parent = nullptr);
    ~MainMenu();

private slots:

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
