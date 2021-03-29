QT       += \
    core \
    gui \
    network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    areamenu.cpp \
    boxmenu.cpp \
    main.cpp \
    mainmenu.cpp \
    monsterdisplay.cpp \
    monsterlistmodel.cpp \
    monsterlistview.cpp \
    profile.cpp \
    teamlistview.cpp \
    teammanager.cpp \
    teammenu.cpp

HEADERS += \
    areamenu.h \
    boxmenu.h \
    mainmenu.h \
    monsterdisplay.h \
    monsterlistmodel.h \
    monsterlistview.h \
    profile.h \
    teamlistview.h \
    teammanager.h \
    teammenu.h

FORMS += \
    boxmenu.ui \
    mainmenu.ui \
    monsterdisplay.ui \
    teamdisplay.ui \
    teammanager.ui \
    teammenu.ui \
    teamwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
