#include "gamewindow_designed.h"
#include "ui_gamewindow_designed.h"

gamewindow_designed::gamewindow_designed(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gamewindow_designed)
{
    ui->setupUi(this);
	this->setWindowTitle("A2B");
    system = new System();
    stage = new Stage();
}

gamewindow_designed::~gamewindow_designed()
{
    delete ui;
}




void gamewindow_designed::on_Run_clicked()
{
   // stage->answer = ;
    //
    //
    System::logWidget = ui->Log;
    system->run(stage,ui->IDE->document(),false);
}

