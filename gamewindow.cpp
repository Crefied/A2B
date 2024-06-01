﻿#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    system = NULL;
    stage = new Stage();
    thread = NULL;
    isRunning = false;
    progressBar_init();
    connect(ui->upload, &QPushButton::clicked, this, [=]()
            { this->stage->saveStage(); });
}

GameWindow::~GameWindow()
{
    delete ui;
    // delete system;
    // delete stage;
}

void GameWindow::on_run_clicked()
{

    if(isRunning)
    {
        threadEnd();
    }
    system = new System();
    thread = new QThread(this);
    system->moveToThread(thread);
    connect(this, &GameWindow::startThread, system, &System::run);             // 计算关联
    connect(system, &System::updateShow, this, &GameWindow::updateOutputInfo); // 文本输出关联
    connect(system, &System::CalEnd, this, &GameWindow::threadEnd, Qt::DirectConnection);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater, Qt::DirectConnection);
    connect(thread, &QThread::finished, system, &QObject::deleteLater, Qt::DirectConnection);
    connect(system,&System::updateProgress,this,&GameWindow::progressBar_update);
    stage->answer = ui->view->document(); // 设置答案
    thread->start();                      // 线程开始
    // connect(this,&GameWindow::resume,system,&System::resume, Qt::QueuedConnection);
    // connect(this,&GameWindow::stop,system,&System::stop, Qt::QueuedConnection);
    // connect(this,&GameWindow::pause,system,&System::pause, Qt::QueuedConnection);
    // connect(this,&GameWindow::speedChange,system,&System::speedChange, Qt::QueuedConnection);
    emit startThread(stage, ui->IDE->document(), false); // 开始计算
    isRunning = true;
}

// void GameWindow::on_backButton_clicked()

void GameWindow::setStageInfo()
{
    ui->Puzzle->appendPlainText(stage->name);
    ui->Puzzle->appendPlainText(stage->scriptDescription);
    ui->Puzzle->appendPlainText(stage->caseDescription);
}

void GameWindow::updateOutputInfo(const QString &info, bool clear)
{
    if (clear)
    {
        ui->Output->clear();
    }
    ui->Output->append(info);
}
void GameWindow::threadEnd()
{
    thread->quit();
    thread->wait();
    progressBar_init();
    isRunning = false;
}

void GameWindow::on_pause_clicked()
{
    if (isRunning)
        system->isPause = true;
}

void GameWindow::on_start_clicked()
{
    if (isRunning)
    {
        QMutexLocker locker(&system->mutex);
        system->isPause = false;
        system->condition.wakeAll();
    }
}

void GameWindow::on_slow_clicked()
{
    if (isRunning)
        system->speed = std::min(0, system->speed - 1);
}

void GameWindow::on_quick_clicked()
{
    if (isRunning)
        system->speed = std::max(2, system->speed + 1);
}

void GameWindow::on_stop_clicked()
{
    if (isRunning)
    {
        system->isStop = true;
        ui->Output->clear();
    }
}
void GameWindow::progressBar_init()
{
    ui->progressBar->setFormat("");
    ui->progressBar->setAlignment(Qt::AlignCenter);
    ui->progressBar->setValue(0);
}
void GameWindow::progressBar_update(int amount,bool error)
{
    ui->progressBar->setFormat(QString::number(amount) + "/ 3267");
    ui->progressBar->setAlignment(Qt::AlignVCenter);
    ui->progressBar->setValue(amount);
}
