#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "gamewindow.h"
#include"gamewindow_designed.h"
#include<QStackedLayout>
#include<qstackedwidget.h>
#include<QPointer>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    QWidget* centralWidget;
    QStackedWidget* stackedWidget;
    QString styleSheet;

    Stage* stages[10][10] = { nullptr };
    bool stageAble[10][10] = { false };

    //MainWindow(QWidget *parent = nullptr);
    MainWindow(GameWindow* _gamewindow, QPointer<gamewindow_designed> _designedWindow, QWidget* parent = nullptr);
    ~MainWindow();
    

private slots:
    void on_pushButton_clicked();
    void selfModeSlot();
private:
    Ui::MainWindow* ui;
    QPointer<GameWindow> gamewindow;
    QPointer<gamewindow_designed> designedWindow;
};
#endif // MAINWINDOW_H