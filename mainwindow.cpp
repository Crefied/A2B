#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui_gamewindow.h"
#include"./ui_gamewindow_designed.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(GameWindow* _gamewindow, QPointer<gamewindow_designed> _designedWindow, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFileInfo fileInfo(__FILE__);
    QDir sourceDir = fileInfo.dir();
    QString styleSheetPath = sourceDir.filePath("style.qss");
    // QTabWidget* stageWidget = dynamic_cast<QTabWidget*>(ui->stackedWidget->widget(1));

    gamewindow = _gamewindow;
    designedWindow = _designedWindow;
    stageAble[1][1] = true; // 第一关可用
    // 建议在这里初始化所有stages信息
    stages[1][1] = new Stage("As beginning\n", "You need to replace a string`s all a with b\n", "Input example:abac\nOutput example:bbbc\n", "a=b");
	stages[1][2] = new Stage("More Difficult\n", "Remove all a\n", "Input example:abac\nOutput example:bc\n", "a= ");

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
    stackedWidget = ui->centralwidget->findChild<QStackedWidget*>("stackedWidget");
    stackedWidget->setCurrentIndex(0);
    //stackedWidget 0:startMenus,1:stageMenus,2:optionMenus,3:modeWidget,4:editorWindow

    ui->stackedWidget->layout()->setAlignment(Qt::AlignRight);
    this->setGeometry(0, 0, 1600,900);
    ui->stackedWidget->addWidget(designedWindow); //会导致关闭程序时读写错误，应该是delete指针的问题，采用hide show的方法替代

    connect(gamewindow->ui->backButton, &QPushButton::clicked, this, [&]()
        {
			this->setGeometry(gamewindow->geometry());
			this->resize(gamewindow->size());
            gamewindow->hide();
            this->show();
            ui->stackedWidget->setCurrentIndex(0);
        });
    connect(designedWindow->ui->backButton, &QPushButton::clicked, this, [&]()
        {
            ui->stackedWidget->setCurrentIndex(0);
        });


    connect(ui->startPushButton, &QPushButton::clicked, this, [&]()
        {
            QLayout* lay = ui->verticalLayout_4;
            //删除lay的所有
            while (QLayoutItem* item = lay->takeAt(0))
            {
                if (QWidget* widget = item->widget())
                {
                    widget->deleteLater();
                }
                delete item;
            }
            ui->stackedWidget->setCurrentIndex(3);
        });

    connect(ui->backPushButton, &QPushButton::clicked, this, [&]()
        {
            ui->stackedWidget->setCurrentIndex(0);
        });
    connect(ui->optionPushButton, &QPushButton::clicked, this, [&]()
        {
            ui->stackedWidget->setCurrentIndex(2);
        });
	connect(ui->storyMode, &QPushButton::clicked, this, [&]()
		{
			ui->stackedWidget->setCurrentIndex(1);
		});
	connect(ui->selfMode, &QPushButton::clicked, this, &MainWindow::selfModeSlot);
		

    QTabWidget* tabWidget = ui->tabWidget;
    for (int i = 0; i < tabWidget->count(); ++i)
    {
        QWidget* tab = tabWidget->widget(i);
        QList<QPushButton*> buttons = tab->findChildren<QPushButton*>();
        int buttonIndex = 0;
        for (QPushButton* button : buttons)
        {
            buttonIndex++;

            connect(button, &QPushButton::clicked, this, [&, i, buttonIndex]()
                {
                    gamewindow->stage = stages[i + 1][buttonIndex];//begin:i+1=1,buttonIndex=1,第一章第一关
					gamewindow->ui->Puzzle->clear();
                    gamewindow->ui->view->clear();
					gamewindow->ui->view->setReadOnly(true);
                    gamewindow->setStageInfo();
					this->gamewindow->setGeometry(this->geometry());
					this->gamewindow->resize(this->size());
                    this->gamewindow->show();
                    this->hide();

                });
        }
    }
    connect(ui->editorPushButton, &QPushButton::clicked, this, [&]()
        {
            gamewindow->stage = stages[1][1];//begin:i+1=1,buttonIndex=1,第一章第一关
            gamewindow->ui->Puzzle->clear();
			gamewindow->ui->view->clear();
            gamewindow->ui->view->setReadOnly(true);
            gamewindow->ui->view->setPlainText(QString("Change stage information on the left top box\nGive your stage standard answer on the left down box\nThen click upload to save your stage"));
            gamewindow->setStageInfo();
            this->gamewindow->setGeometry(this->geometry());
            this->gamewindow->resize(this->size());
            this->gamewindow->show();
            this->hide();
        });

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

void MainWindow::selfModeSlot()
{
    QLayout* lay = ui->verticalLayout_4;
	//删除lay的所有
	while (QLayoutItem* item = lay->takeAt(0))
	{
		if (QWidget* widget = item->widget())
		{
			widget->deleteLater();
		}
		delete item;
	}
	gamewindow->ui->view->clear();
    gamewindow->ui->Puzzle->clear();
    gamewindow->ui->view->setReadOnly(true);

	QFileInfo fileInfo(__FILE__);
	QDir sourceDir = fileInfo.dir();
	QString stagePath = sourceDir.filePath("Stage/");
	QFileInfoList stageList = QDir(stagePath).entryInfoList(QDir::Files);
	for (const QFileInfo& stageFile : stageList)
    {
		QString stageName = stageFile.fileName();
		QString _filePath = stageFile.absoluteFilePath();

		QFile file(_filePath);
		if (file.open(QFile::ReadOnly))
		{
			QTextStream in(&file);
			QString name = in.readLine();
			QString scriptDescription = in.readLine();
			QString exampleCase = in.readLine();
			exampleCase += "\n";
            exampleCase += in.readLine();
			QString answer = in.readAll();
            QPushButton* button = new QPushButton(name);
            button->setStyleSheet(styleSheet);
            button->setFlat(true);
            ui->verticalLayout_4->addWidget(button);
			connect(button, &QPushButton::clicked, this, [&, name, scriptDescription, exampleCase, answer]()
				{
					gamewindow->stage = new Stage(name, scriptDescription, exampleCase, answer);
					//button->setText(name);
					gamewindow->setStageInfo();
                    this->gamewindow->setGeometry(this->geometry());
                    this->gamewindow->resize(this->size());
                    this->gamewindow->show();
                    this->hide();
				});
		}
        else
			qDebug() << "Failed to open stage file" << file.errorString() << QDir::currentPath();
	}
}