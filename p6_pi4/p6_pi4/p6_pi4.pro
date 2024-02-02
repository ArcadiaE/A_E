QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++98

#CONFIG -= app_bundle

####################### define #######################
DEFINES += _DEBUG
DEFINES += _CONSOLE
DEFINES += _NOENUMQBOOL
DEFINES += QT_VERSION
####################### define #######################

#QT -= gui

####################### config #######################
#CONFIG += c++11 console
#CONFIG -= app_bundle
####################### config #######################

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../common/cmdlib.c \
    GameUI.cpp \
    game.cpp \
    sudoku.cpp

HEADERS += \
    ../common/cmdlib.h \
    GameUI.h \
    sudoku.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
