#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QDesktopWidget>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QInputDialog>
#include <QUuid>

#include "mainmenu.h"
#include "boxmenu.h"
#include "areamenu.h"
#include "teammenu.h"

#include "monsterlistmodel.h"
#include "teamlistmodel.h"
#include "profile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TeamManager; }
QT_END_NAMESPACE

class TeamManager : public QMainWindow
{
    Q_OBJECT

public:
    TeamManager(QWidget *parent = nullptr);
    ~TeamManager();

public slots:
    void setPage(int index);

private slots:

    void on_backButton_released();

    void on_mainButton_released();

    void on_boxButton_released();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionImport_triggered();

    void on_actionAbout_triggered();

    void onImport(QNetworkReply *reply);

    void onDataReceived(QNetworkReply *reply);

    void onImageReceived(QNetworkReply *reply);

private:
    Ui::TeamManager *ui;

    Profile *profile;
    QString filePath;
    QHash<QNetworkReply *, QJsonObject> dataStorage;
    QHash<QNetworkReply *, Monster *> monsterStorage;

    MonsterListModel *mListModel;
    TeamListModel *tListModel;

    int lastPageIndex;
    QVector<int> lastPageStack;
    QStackedLayout *layout;
    MainMenu *menuPage;
    BoxMenu *boxPage;
    AreaMenu *arenaPage;
    AreaMenu *guildPage;
    AreaMenu *siegePage;
    TeamMenu *tartarusPage;     // TeamMenu
    AreaMenu *cairosPage;
    AreaMenu *dimensionalPage;
    AreaMenu *riftPage;
    TeamMenu *towerPage;        // TeamMenu

    void requestImage(Monster *monster);
    void clearProfile();
    void requestData(QJsonObject &partialData);
};
#endif // TEAMMANAGER_H
