#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <cstdio>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    printf("this is the console");
    MainWindow w;
    w.show();
    QLabel *label = new QLabel("Hello Qt!");
    label -> show();
    return a.exec();
}
