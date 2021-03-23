#include "teammanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TeamManager w;
    w.show();
    return a.exec();
}
