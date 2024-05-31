#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui_gamewindow.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(GameWindow *_gamewindow, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFileInfo fileInfo(__FILE__);
    QDir sourceDir = fileInfo.dir();
    QString styleSheetPath = sourceDir.filePath("style.qss");
    // QTabWidget* stageWidget = dynamic_cast<QTabWidget*>(ui->stackedWidget->widget(1));

    gamewindow = _gamewindow;
    stageAble[1][1] = true; // 第一关可用
    // 建议在这里初始化所有stages信息
    stages[1][1] = new Stage("As beginning\n", "You need to replace a string`s all a with b\n", "Input example:abac\nOutput example:bbbc\n");

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
    // 统一窗口样式，通过QSS文件设置

    this->setStyleSheet(styleSheet);
    // gamewindow->setStyleSheet(styleSheet); //中文

    this->setWindowTitle("A2B");
    stackedWidget = ui->centralwidget->findChild<QStackedWidget *>("stackedWidget");
    stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->layout()->setAlignment(Qt::AlignRight);
    this->setGeometry(0, 0, 800, 600);
    // ui->stackedWidget->addWidget(gamewindow); 会导致关闭程序时读写错误，应该是delete指针的问题，采用hide show的方法替代

    connect(gamewindow->ui->backButton, &QPushButton::clicked, this, [=]()
            {
            gamewindow->hide();
            this->show();
			ui->stackedWidget->setCurrentIndex(0); });

    connect(ui->startPushButton, &QPushButton::clicked, this, [=]()
            { ui->stackedWidget->setCurrentIndex(1); });

    connect(ui->backPushButton, &QPushButton::clicked, this, [=]()
            { ui->stackedWidget->setCurrentIndex(0); });
    connect(ui->optionPushButton, &QPushButton::clicked, this, [=]()
            { ui->stackedWidget->setCurrentIndex(2); });

    QTabWidget *tabWidget = ui->tabWidget;
    for (int i = 0; i < tabWidget->count(); ++i)
    {
        QWidget *tab = tabWidget->widget(i);
        QList<QPushButton *> buttons = tab->findChildren<QPushButton *>();
        int buttonIndex = 0;
        for (QPushButton *button : buttons)
        {
            buttonIndex++;

            connect(button, &QPushButton::clicked, this, [=]()
                    {
					gamewindow->stage = stages[i + 1][buttonIndex];//begin:i+1=1,buttonIndex=1,第一章第一关
					gamewindow->setStageInfo();
					this->gamewindow->show();
                    this->hide(); });
        }
    }
}

MainWindow::~MainWindow()
{
    ui->stackedWidget->removeWidget(gamewindow);
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    this->gamewindow->show();
}
