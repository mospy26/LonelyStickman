#-------------------------------------------------
#
# Project created by QtCreator 2019-03-05T21:25:41
#
#-------------------------------------------------

#QT       += core gui
QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LonelyStickman
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
    level.cpp \
    dialog.cpp \
    newconfiguration.cpp \
    saveform.cpp \
    mario.cpp \
    mariocreator.cpp \
    mariostickman.cpp \
    stickmancreator.cpp \
    levelcreator.cpp \
    mariolevel.cpp

HEADERS += \
    level.h \
    dialog.h \
    stickman.h \
    newconfiguration.h \
    saveform.h \
    gamebuilder.h \
    mario.h \
    mariocreator.h \
    mariostickman.h \
    stickmancreator.h \
    levelcreator.h \
    mariolevel.h

FORMS += \
        dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.txt \
    .gitignore \
    music/part1.mp3 \
    wrong.json

RESOURCES += \
    resources.qrc
