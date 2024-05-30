#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include<QPointer>
#include "system.h"
namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    Ui::GameWindow* ui;

    Stage* stage;

    void setStageInfo();//ÒÑ¾­¸üÐÂstageÐÅÏ¢²Åµ÷ÓÃ
private slots:
    void on_run_clicked();
    
    //void on_backButton_clicked();

private:

    System * system;

};



#endif // GAMEWINDOW_H
