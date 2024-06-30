#include "mainwindow.h"
#include "gamewindow.h"
#include"gamewindow_designed.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QPointer>
#include<QScreen>
////
////
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System system;
    GameWindow gamewindow = GameWindow();
	QPointer<gamewindow_designed> design = new gamewindow_designed();
    MainWindow w(&gamewindow,design);
    //gamewindow.show();

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "test_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }


    w.resize(1600, 900);
	gamewindow.resize(1600, 900);

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - w.width()) / 2;
    int y = (screenGeometry.height() - w.height()) / 2;
    
    w.move(x,y-20);
	gamewindow.move(x, y - 20);


    w.show();
    return a.exec();
}
