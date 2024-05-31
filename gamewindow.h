#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPointer>
#include "system.h"
namespace Ui
{
    class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    Ui::GameWindow *ui;
    Stage *stage;
    bool isRunning;
    void setStageInfo(); // 已经更新stage信息才调用
    void updateOutputInfo(const QString & info,bool clear); // info 是输入信息，clear 是清屏
    void threadEnd();
private slots:
    void on_run_clicked();

    void on_pause_clicked();

    void on_start_clicked();

    void on_slow_clicked();

    void on_quick_clicked();

    void on_stop_clicked();

signals:
    void startThread(Stage * _stage,QTextDocument * _input,bool _debug);
    void speedChange(bool adjust);
    void stop();
    void pause();
    void resume();
    // void on_backButton_clicked();

private:
    System * system;
    QThread * thread;
};

#endif // GAMEWINDOW_H
