#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPushButton>
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
    bool isDesign = false;
    Stage* stages[10][10] = { };
    QPushButton * chapterButtons[5][8];
    //MainWindow(QWidget *parent = nullptr);
    MainWindow(QPointer<GameWindow> _gamewindow, QPointer<gamewindow_designed> _designedWindow = NULL, QWidget* parent = nullptr);
    ~MainWindow();
    void loadProgress();
    void updateUnlockStage();
    void unlockAllStages();
    void lockAllStages();
private slots:
    void on_pushButton_clicked();
    void selfModeSlot();
    void on_backButton_clicked();
signals:
    void closeEvent(QCloseEvent * event);
private:
    Ui::MainWindow* ui;
    QPointer<GameWindow> gamewindow;
    QPointer<gamewindow_designed> designedWindow;
};
#endif // MAINWINDOW_H
