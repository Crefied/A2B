#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"./ui_gamewindow.h"
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
    //QTabWidget* stageWidget = dynamic_cast<QTabWidget*>(ui->stackedWidget->widget(1));

    gamewindow = _gamewindow;

    QFile file(styleSheetPath);
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
	gamewindow->setStyleSheet(styleSheet);

    

	this->setWindowTitle("A2B");
	stackedWidget = ui->centralwidget->findChild<QStackedWidget*>("stackedWidget");
	stackedWidget->setCurrentIndex(0);
	ui->stackedWidget->layout()->setAlignment(Qt::AlignRight);
	this->setGeometry(0, 0, 800, 600);
    //ui->stackedWidget->addWidget(gamewindow);

	connect(gamewindow->ui->backButton, &QPushButton::clicked, this, [=]()
		{
            gamewindow->hide();
            this->show();
			ui->stackedWidget->setCurrentIndex(0);
		});

    connect(ui->startPushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);        
        });
	
	connect(ui->backPushButton, &QPushButton::clicked, this, [=]()
		{
			ui->stackedWidget->setCurrentIndex(0);
		});
	connect(ui->optionPushButton, &QPushButton::clicked, this, [=]()
		{
			ui->stackedWidget->setCurrentIndex(2);
		});

    QTabWidget* tabWidget = ui->tabWidget; 
    for (int i = 0; i < tabWidget->count(); ++i)
    {
        QWidget* tab = tabWidget->widget(i);
        QList<QPushButton*> buttons = tab->findChildren<QPushButton*>();
        for (QPushButton* button : buttons)
        {
            connect(button, &QPushButton::clicked, this, [=]()
                {
                    this->hide();
					this->gamewindow->show();
                });
        }
    }


    
    
}



MainWindow::~MainWindow()
{
	ui->stackedWidget->removeWidget(gamewindow);
    //delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    this->gamewindow->show();
}


