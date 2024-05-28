#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Stage.h"
#include <QMainWindow>
#include "gamewindow.h"
#include<QStackedLayout>
#include<qstackedwidget.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QWidget* centralWidget;
	QStackedWidget* stackedWidget;
    MainWindow(QWidget *parent = nullptr);
    MainWindow(GameWindow * _gamewindow,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    GameWindow * gamewindow;
};
#endif // MAINWINDOW_H
