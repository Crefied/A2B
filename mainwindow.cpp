#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFile>
#include<QDebug>
#include<QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStackedLayout* qsl = new QStackedLayout();
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
        qDebug() << "Failed to open style.qss" << file.errorString()<<QDir::currentPath();
    }
    ui->pushButton->setStyleSheet("background-color: red;");
    ui->pushButton->setStyleSheet(styleSheet);
}

MainWindow::~MainWindow()
{
    delete ui;
}
