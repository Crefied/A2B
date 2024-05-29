#ifndef GAMEWINDOW_DESIGNED_H
#define GAMEWINDOW_DESIGNED_H

#include <QWidget>
#include<QPointer>
#include "system.h"
namespace Ui {
class gamewindow_designed;
}

class gamewindow_designed : public QWidget
{
    Q_OBJECT

public:
    gamewindow_designed(QWidget *parent = nullptr);
    ~gamewindow_designed();
    Ui::gamewindow_designed *ui;
private:

    System * system;
    Stage * stage;

private slots:
    void on_Run_clicked();
};

#endif // GAMEWINDOW_DESIGNED_H
