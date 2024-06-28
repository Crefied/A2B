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
    stages[1][1] = new Stage("A=B\n", "将字符串中所有字母a换成字母b\n", "Input example:aabcbbc\nOutput example:bbbcbbc\n", "a=b");
	stages[1][2] = new Stage("排序\n", "给定一个由a,b,c组成的字符串，将其按照字母顺序重新排序。\n", "Input example:cbacabb\nOutput example:aabbbcc\n"," ba = ab \n ca = ac \n cb = bc");
    stages[1][3] = new Stage("去重\n", "将字符串中所有连续的相同字母换成单个字母。\n", "Input example:aaaccba\nOutput example:acba\n", "aa=a\nbb=b\ncc=c");
    stages[2][2] = new Stage("余数\n", "输入由abc构成的字符串，输出字符串长度模3的余数。\n", "Input example:cabcaba\nOutput example:1\n", "a=c\nb=c\nccc= \ncc=(return)2\nc=(return)1\n=(return)0");
    stages[2][1] = new Stage("Hello World\n", "输出HelloWorld。\n", "Input example:aaaccba\nOutput example:Hello World\n", "=(return)Hello World");
    stages[2][2] = new Stage("去重\n", "将字符串中所有连续的相同字母换成单个字母。\n", "Input example:aaaccba\nOutput example:acba\n", "aa=a\nbb=b\ncc=c");
    stages[2][4] = new Stage("独一无二\n", "输入由abc构成的字符串。若仅有一个字符与其所有相邻字符均不同，输出true，否则输出false。控制代码在10行以内。\n", "Input example:aabcc\nOutput example:true\n", "b=xaxx\nc=xxax\nxxx=\nxx=x\naaa=aa\naa=\naxa=(return)false\na=(return)true\n=(return)false");

    stages[2][5] = new Stage("最少\n", "输入由abc构成的字符串。输出其中出现次数最少的字符。保证答案唯一。控制代码在10行以内。\n", "Input example:cbabbcc\nOutput example:a\n", "ba=ab\nca=ac\ncb=bc\nbc=d\nbd=db\nad=\nd=(return)a\nb=(return)c\nc=(return)b");

    stages[3][1] = new Stage("Start&End\n", "给定一个由abc组成的字符串。将开头和结尾的所有a去除。\n", "Input example:aabcba\nOutput example:bcb\n", "(start)a=\n(end)a=");

    stages[3][2] = new Stage("A2B\n", "将开头和结尾的所有a换成b。代码不能超过四行。\n", "nothing\n", "(start)a=(end)x\nx=(start)b\n(end)a=(start)y\ny=(end)b");

    stages[3][3] = new Stage("回文串\n", "输入由abc构成的字符串。若此字符串为回文串，则输出true，否则输出false。\n", "nothing\n", "xaxa=\nxbxb=\nxcxc=\n(end)a=(start)xax\n(end)b=(start)xbx\n(end)c=(start)xcx\nxx=(return)false\n=(return)true");

    stages[3][4] = new Stage("交换\n", "输入由abc构成的字符串，交换开头的每个a和结尾的每个b。保证开头总有至少一个a。控制在4行以内。\n", "nothing\n", "(start)a=(end)x\nbx=xy\nx=a\ny=(start)b");

    stages[3][5] = new Stage("复制\n", "输入由abc构成的字符串，满足长度大于等于3。复制开头的三个字母，并将其拷贝在结尾。\n", "Input example:abcbcbb\nOutput example:abcbcbbabc\n", "(once)=xxx\nya=(start)a\nyb=(start)b\nyc=(start)c\nxa=(end)yaa\nxb=(end)ybb\nxc=(end)ycc\n(once)=yyy");

    stages[3][6] = new Stage("最多\n", "输入由abc构成的字符串。保留输入次数最多的一个字母，删除其他字母。保证出现最多的字母只有一个。\n", "Input example:abccbca\nOutput example:ccc\n", "ba=ab\nca=ac\ncb=bc\nbc=(start)x\nxa=(start)y\nac=(start)y\nab=(start)y\nx=y\nyc=cc\nya=aa\ny=b");

    stages[4][1] = new Stage("移除\n", "输入由abc构成的字符串，移除前三个a。若a不足三个，全部移除。\n", "Input example:aabcaca\nOutput example:bcca\n", "(once)a=\n(once)a=\n(once)a=");

    stages[4][2] = new Stage("移除2\n", "输入由abc构成的字符串，移除后三个a。若a不足三个，全部移除。\n", "Input example:aabcaca\nOutput example:abcc\n", "(once)=(end)xxx\ncx=xc\nbx=xb\nax=\nx=");

    stages[4][3] = new Stage("删除\n", "输入一个由abc构成的字符串。输出空字符串。\n", "nothing\n", "=(return)");

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
            gamewindow->isStory = true;
            for (int i = 1; i <= 4; i++)
            {
                QLayout* lay;
                if (i == 1)
                {
                    lay = ui->verticalLayout;
                }
                else if (i == 2) lay = ui->verticalLayout_5;
                else if (i == 3) lay = ui->verticalLayout_6;
                else if (i == 4) lay = ui->verticalLayout_7;
                
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
                    //gamewindow->ui->view->setReadOnly(true);
                    for (int j = 1; j <= 8; j++)
                    {
                        if (stages[i][j] == nullptr)
                            continue;
                        QString name = stages[i][j]->name;
                        QString scriptDescription = stages[i][j]->scriptDescription;
                        QString exampleCase = stages[i][j]->caseDescription;
                        QString answer = stages[i][j]->answer->toPlainText();
                        QPushButton* button = new QPushButton(stages[i][j]->name);
                        button->setStyleSheet(styleSheet);
                        button->setFlat(true);
                        lay->addWidget(button);
                        connect(button, &QPushButton::clicked, this, [&, name, scriptDescription, exampleCase, answer]()
                            {
                                gamewindow->stage = new Stage(name, scriptDescription, exampleCase, answer);
                                //button->setText(name);
                                gamewindow->setStageInfo();
                                this->gamewindow->setGeometry(this->geometry());
                                this->gamewindow->resize(this->size());
                                this->gamewindow->show();
                                this->hide();
                                qDebug() << gamewindow->stage->answer;
                            });
                    }
                

            }
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