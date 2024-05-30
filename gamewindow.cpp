#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    system = new System();
    stage = new Stage();
}

GameWindow::~GameWindow()
{
    //delete ui;
    //delete system;
    //delete stage;
}

void GameWindow::on_run_clicked()
{
    stage->answer = ui->view->document();
    System::logWidget = ui->textBrowser;
    system->run(stage,ui->IDE->document(),false);

    ui->Progress->resize(611,31);
}


//void GameWindow::on_backButton_clicked()
=======
}

void GameWindow::setStageInfo()
{
	ui->stageInfo->append(stage->name);
	ui->stageInfo->append(stage->scriptDescription);
	ui->stageInfo->append(stage->caseDescription);
}

