#include "mainwindow.h"
#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System system;
    GameWindow gamewindow = GameWindow();
    MainWindow w(&gamewindow);
    gamewindow.show();

    return a.exec();
}
