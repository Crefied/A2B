/********************************************************************************
** Form generated from reading UI file 'gamewindow_designed.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_DESIGNED_H
#define UI_GAMEWINDOW_DESIGNED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewindow_designed
{
public:
    QWidget *ProgressFrame;
    QWidget *Progress;
    QPlainTextEdit *IDE;
    QPushButton *Run;
    QTextBrowser *Puzzle;
    QTextBrowser *Log;
    QPushButton *pushButton;

    void setupUi(QWidget *gamewindow_designed)
    {
        if (gamewindow_designed->objectName().isEmpty())
            gamewindow_designed->setObjectName("gamewindow_designed");
        gamewindow_designed->resize(1200, 700);
        gamewindow_designed->setStyleSheet(QString::fromUtf8("background-color: rgb(31,30,51);"));
        ProgressFrame = new QWidget(gamewindow_designed);
        ProgressFrame->setObjectName("ProgressFrame");
        ProgressFrame->setGeometry(QRect(490, 50, 651, 41));
        ProgressFrame->setStyleSheet(QString::fromUtf8("border: 2px solid white;\n"
"font: 700 20pt \"Consolas\";\n"
"color:white;"));
        Progress = new QWidget(ProgressFrame);
        Progress->setObjectName("Progress");
        Progress->setGeometry(QRect(0, 0, 0, 41));
        Progress->setStyleSheet(QString::fromUtf8("background-color: rgb(0,255,0)"));
        IDE = new QPlainTextEdit(gamewindow_designed);
        IDE->setObjectName("IDE");
        IDE->setGeometry(QRect(490, 150, 631, 521));
        IDE->setStyleSheet(QString::fromUtf8("border: 2px solid white;\n"
"font: 20pt \"Consolas\";\n"
"color:white;"));
        Run = new QPushButton(gamewindow_designed);
        Run->setObjectName("Run");
        Run->setGeometry(QRect(1010, 110, 101, 31));
        Run->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Consolas\";\n"
"color:white;\n"
"text-decoration: underline;"));
        Puzzle = new QTextBrowser(gamewindow_designed);
        Puzzle->setObjectName("Puzzle");
        Puzzle->setGeometry(QRect(30, 40, 381, 231));
        Puzzle->setStyleSheet(QString::fromUtf8("border: 2px solid white;\n"
"font: 20pt \"Consolas\";\n"
"color:white;"));
        Log = new QTextBrowser(gamewindow_designed);
        Log->setObjectName("Log");
        Log->setGeometry(QRect(30, 290, 381, 341));
        Log->setStyleSheet(QString::fromUtf8("border: 2px solid white;\n"
"font: 700 20pt \"Consolas\";\n"
"color:rgb(0,255,0);"));
        pushButton = new QPushButton(gamewindow_designed);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 640, 91, 31));
        pushButton->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Consolas\";\n"
"text-decoration: underline;\n"
"color:white;"));

        retranslateUi(gamewindow_designed);

        QMetaObject::connectSlotsByName(gamewindow_designed);
    } // setupUi

    void retranslateUi(QWidget *gamewindow_designed)
    {
        gamewindow_designed->setWindowTitle(QCoreApplication::translate("gamewindow_designed", "Form", nullptr));
        Run->setText(QCoreApplication::translate("gamewindow_designed", "RUN", nullptr));
        pushButton->setText(QCoreApplication::translate("gamewindow_designed", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewindow_designed: public Ui_gamewindow_designed {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_DESIGNED_H
