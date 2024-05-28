#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFile>
#include<QDebug>
#include<QDir>

MainWindow::MainWindow(GameWindow * _gamewindow,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileInfo fileInfo(__FILE__);
    QDir sourceDir = fileInfo.dir();
    QString styleSheetPath = sourceDir.filePath("style.qss");

    QFile file(styleSheetPath);
    QString styleSheet;
    if (file.open(QFile::ReadOnly))
    {
        styleSheet = QLatin1String(file.readAll());
        qDebug() << "Style sheet:" << styleSheet;
    }
    else
    {
        qDebug() << "Failed to open style.qss" << file.errorString() << QDir::currentPath();
    }
	//统一窗口样式，通过QSS文件设置


    this->setStyleSheet(styleSheet);
    

	this->setWindowTitle("A2B");
	stackedWidget = ui->centralwidget->findChild<QStackedWidget*>("stackedWidget");
	stackedWidget->setCurrentIndex(0);
	ui->stackedWidget->layout()->setAlignment(Qt::AlignRight);
	this->setGeometry(0, 0, 800, 600);
    connect(ui->startPushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
        
        });

}
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

