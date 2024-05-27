#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(GameWindow * _gamewindow,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gamewindow = _gamewindow;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    this->gamewindow->show();
}

