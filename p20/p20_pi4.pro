QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++98

#CONFIG -= app_bundle

####################### define #######################

DEFINES += __osf__
DEFINES += _DEBUG
DEFINES += _CONSOLE
DEFINES += _NOENUMQBOOL
#DEFINES += _SOFTGPIO
DEFINES += _SERVER
#DEFINES += QT_VERSION

####################### define #######################

#QT -= gui

####################### config #######################

CONFIG += c++11
#CONFIG += c++11 console
#CONFIG -= app_bundle

#debug
QMAKE_CXXFLAGS += -Wall -pedantic -Wextra -Wall  -g -W -fexceptions
QMAKE_LFLAGS += -lpthread -lwiringPi -lGL -lX11 -no-pie

#release
#QMAKE_CXXFLAGS += -Wall -O2 -ansi -W -fexceptions -D__osf__ -DNDEBUG -D_CONSOLE -D_NOENUMQBOOL -D_SOFTGPIO
#QMAKE_LFLAGS += -s -lpthread -lwiringPi -no-pie

####################### config #######################

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

####################### include #######################

SOURCES += \
    cmdlib.c \
    qt/mx.cpp \
    qt/mxButton.cpp \
    qt/mxCheckBox.cpp \
    qt/mxChoice.cpp \
    qt/mxChooseColor.cpp \
    qt/mxFileDialog.cpp \
    qt/mxGlWindow.cpp \
    qt/mxGroupBox.cpp \
    qt/mxLabel.cpp \
    qt/mxLineEdit.cpp \
    qt/mxListBox.cpp \
    qt/mxMenu.cpp \
    qt/mxMenuBar.cpp \
    qt/mxMessageBox.cpp \
    qt/mxPopupMenu.cpp \
    qt/mxProgressBar.cpp \
    qt/mxRadioButton.cpp \
    qt/mxSettings.cpp \
    qt/mxSlider.cpp \
    qt/mxTab.cpp \
    qt/mxToggleButton.cpp \
    qt/mxToolTip.cpp \
    qt/mxTreeView.cpp \
    qt/mxWidget.cpp \
    qt/mxWindow.cpp \
    threads.c \
    action.c \
    buffer.c \
    client.c \
    painter.c \
    receiver.c \
    sender.c \
    server.c \
    softgpio.c \
    GlPainter.cpp \
    GlWindow.cpp \
    RCWindow.cpp \
    SDWindow.cpp

HEADERS += \
    cmdlib.h \
    qt/mxButton_i.h \
    qt/mxCheckBox_i.h \
    qt/mxChoice_i.h \
    qt/mxGlWindow_i.h \
    qt/mxLineEdit_i.h \
    qt/mxListBox_i.h \
    qt/mxMenuBar_i.h \
    qt/mxPopupMenu_i.h \
    qt/mxRadioButton_i.h \
    qt/mxSlider_i.h \
    qt/mxTab_i.h \
    qt/mxToggleButton_i.h \
    qt/mxTreeView_i.h \
    qt/mxWindow_i.h \
    threads.h \
    action.h \
    buffer.h \
    client.h \
    CmdLine.h \
    GlPainter.h \
    GlWindow.h \
    RCWindow.h \
    SDWindow.h \
    server.h \
    shared.h \
    softgpio.h

#FORMS += \
#    mainwindow.ui

####################### include #######################

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
