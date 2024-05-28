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

private slots:
    void on_run_clicked();

private:

    System * system;
    Stage * stage;
};



#endif // GAMEWINDOW_H
