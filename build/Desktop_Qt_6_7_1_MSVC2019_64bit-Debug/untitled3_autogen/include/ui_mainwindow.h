/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_8;
    QStackedWidget *stackedWidget;
    QWidget *startMenu;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *menuLayout;
    QPushButton *startPushButton;
    QPushButton *optionPushButton;
    QPushButton *editorPushButton;
    QWidget *stageWidget;
    QTabWidget *tabWidget;
    QWidget *Chapter1;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *Stage1_1;
    QWidget *Chapter2;
    QWidget *Chapter3;
    QWidget *Chapter4;
    QWidget *gameWidget;
    QWidget *optionWidget;
    QPushButton *backPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 893);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(100, 100));
        MainWindow->setBaseSize(QSize(100, 100));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setAutoFillBackground(false);
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 20, 1241, 831));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(verticalLayoutWidget_3);
        stackedWidget->setObjectName("stackedWidget");
        startMenu = new QWidget();
        startMenu->setObjectName("startMenu");
        verticalLayoutWidget = new QWidget(startMenu);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(70, 10, 348, 701));
        menuLayout = new QVBoxLayout(verticalLayoutWidget);
        menuLayout->setSpacing(20);
        menuLayout->setObjectName("menuLayout");
        menuLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        menuLayout->setContentsMargins(20, 20, 20, 20);
        startPushButton = new QPushButton(verticalLayoutWidget);
        startPushButton->setObjectName("startPushButton");
        QFont font;
        font.setPointSize(18);
        startPushButton->setFont(font);
        startPushButton->setFlat(true);

        menuLayout->addWidget(startPushButton);

        optionPushButton = new QPushButton(verticalLayoutWidget);
        optionPushButton->setObjectName("optionPushButton");
        optionPushButton->setFont(font);
        optionPushButton->setFlat(true);

        menuLayout->addWidget(optionPushButton);

        editorPushButton = new QPushButton(verticalLayoutWidget);
        editorPushButton->setObjectName("editorPushButton");
        editorPushButton->setFont(font);
        editorPushButton->setAutoDefault(false);
        editorPushButton->setFlat(false);

        menuLayout->addWidget(editorPushButton);

        stackedWidget->addWidget(startMenu);
        stageWidget = new QWidget();
        stageWidget->setObjectName("stageWidget");
        tabWidget = new QTabWidget(stageWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(10, 0, 1600, 900));
        QFont font1;
        font1.setBold(true);
        font1.setUnderline(true);
        tabWidget->setFont(font1);
        Chapter1 = new QWidget();
        Chapter1->setObjectName("Chapter1");
        Chapter1->setEnabled(true);
        verticalLayoutWidget_2 = new QWidget(Chapter1);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(100, 100, 160, 281));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Stage1_1 = new QPushButton(verticalLayoutWidget_2);
        Stage1_1->setObjectName("Stage1_1");

        verticalLayout->addWidget(Stage1_1);

        tabWidget->addTab(Chapter1, QString());
        Chapter2 = new QWidget();
        Chapter2->setObjectName("Chapter2");
        tabWidget->addTab(Chapter2, QString());
        Chapter3 = new QWidget();
        Chapter3->setObjectName("Chapter3");
        tabWidget->addTab(Chapter3, QString());
        Chapter4 = new QWidget();
        Chapter4->setObjectName("Chapter4");
        tabWidget->addTab(Chapter4, QString());
        stackedWidget->addWidget(stageWidget);
        gameWidget = new QWidget();
        gameWidget->setObjectName("gameWidget");
        stackedWidget->addWidget(gameWidget);
        optionWidget = new QWidget();
        optionWidget->setObjectName("optionWidget");
        stackedWidget->addWidget(optionWidget);

        verticalLayout_8->addWidget(stackedWidget);

        backPushButton = new QPushButton(centralwidget);
        backPushButton->setObjectName("backPushButton");
        backPushButton->setGeometry(QRect(10, 790, 311, 91));
        backPushButton->setCursor(QCursor(Qt::ArrowCursor));
        backPushButton->setAutoDefault(false);
        backPushButton->setFlat(false);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        editorPushButton->setDefault(false);
        tabWidget->setCurrentIndex(0);
        backPushButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startPushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        optionPushButton->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        editorPushButton->setText(QCoreApplication::translate("MainWindow", "\345\205\263\345\215\241\347\274\226\350\276\221\345\231\250", nullptr));
        Stage1_1->setText(QCoreApplication::translate("MainWindow", "Stage1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Chapter1), QCoreApplication::translate("MainWindow", "Chapter1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Chapter2), QCoreApplication::translate("MainWindow", "Chapter2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Chapter3), QCoreApplication::translate("MainWindow", "Chapter3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Chapter4), QCoreApplication::translate("MainWindow", "Chapter4", nullptr));
        backPushButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\347\233\256\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
