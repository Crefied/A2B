/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QPushButton *run;
    QPushButton *upload;
    QPlainTextEdit *IDE;
    QPlainTextEdit *view;
    QTextBrowser *textBrowser;
    QPushButton *backButton;
    QPlainTextEdit *Puzzle;
    QWidget *ProgressFrame;
    QWidget *Progress;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName("GameWindow");
        GameWindow->resize(1200, 700);
        GameWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(31, 30, 51);\n"
""));
        run = new QPushButton(GameWindow);
        run->setObjectName("run");
        run->setGeometry(QRect(1060, 270, 81, 31));
        run->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Consolas\";\n"
"text-decoration: underline;\n"
"color:white;"));
        upload = new QPushButton(GameWindow);
        upload->setObjectName("upload");
        upload->setGeometry(QRect(360, 270, 91, 31));
        upload->setStyleSheet(QString::fromUtf8("\n"
"text-decoration: underline;\n"
"color:white;\n"
"font: 700 20pt \"Consolas\";"));
        IDE = new QPlainTextEdit(GameWindow);
        IDE->setObjectName("IDE");
        IDE->setGeometry(QRect(530, 300, 611, 351));
        IDE->setStyleSheet(QString::fromUtf8("border: 2px solid white;\n"
"font:  20pt \"Consolas\";\n"
"color:white;"));
        view = new QPlainTextEdit(GameWindow);
        view->setObjectName("view");
        view->setGeometry(QRect(50, 300, 401, 351));
        view->setStyleSheet(QString::fromUtf8("border:2px solid white;\n"
"font:  20pt \"Consolas\";\n"
"color:white;"));
        textBrowser = new QTextBrowser(GameWindow);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(530, 80, 611, 181));
        textBrowser->setStyleSheet(QString::fromUtf8("border: 2px solid white;\n"
"font: 20pt \"Consolas\";\n"
"color: rgb(0, 255, 0);"));
        backButton = new QPushButton(GameWindow);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(20, 660, 81, 31));
        backButton->setStyleSheet(QString::fromUtf8("color:white;\n"
"font: 700 20pt \"Consolas\";\n"
"text-decoration: underline;"));
        Puzzle = new QPlainTextEdit(GameWindow);
        Puzzle->setObjectName("Puzzle");
        Puzzle->setGeometry(QRect(50, 30, 401, 231));
        Puzzle->setStyleSheet(QString::fromUtf8("border: 2px solid white;\n"
"font: 14pt \"Consolas\";\n"
"color:white;"));
        ProgressFrame = new QWidget(GameWindow);
        ProgressFrame->setObjectName("ProgressFrame");
        ProgressFrame->setGeometry(QRect(530, 30, 611, 31));
        ProgressFrame->setStyleSheet(QString::fromUtf8("border:2px solid white;"));
        Progress = new QWidget(ProgressFrame);
        Progress->setObjectName("Progress");
        Progress->setGeometry(QRect(0, 0, 0, 41));
        Progress->setStyleSheet(QString::fromUtf8("background-color:green;\n"
""));

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QCoreApplication::translate("GameWindow", "Form", nullptr));
        run->setText(QCoreApplication::translate("GameWindow", "RUN", nullptr));
        upload->setText(QCoreApplication::translate("GameWindow", "UPLOAD", nullptr));
        backButton->setText(QCoreApplication::translate("GameWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
