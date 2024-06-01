#ifndef SYSTEM_H
#define SYSTEM_H

#include <QString>
#include <QTextDocument>
#include <QTextBlock>
#include <QRandomGenerator64>
#include <QTextBrowser>
#include <QWidget>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include<QFile>
#include<QFileInfo>
#include<QDir>
class Command;
class System;
/*
 * 重点关注：
 * System类 中run：计算调用起点
 * Stage类 ： 关卡所需
*/

const int MAXTIME = 800;
enum Error {
    WA = 1,
    TLE,
    CE_KS,
    CE_ES,
    CE_EN
};

struct CommandType // 关键字种类，判断指令的操作
{
    bool isOnce; // 一次运算
    bool isStartFind; // 左侧的start
    bool isStartPut; // 右侧的start
    bool isEndFind; // 左侧的end
    bool isEndPut; // 右侧的end
    bool isReturn; // 右侧return
};

struct Code:public QObject // 代码块
{
    Q_OBJECT
private:
    Command * command; // 可执行的代码，一个command是一行代码
    int commandLen; // 代码行数量
    System * system;
public:
    Code();
    void process(QTextDocument * _doc);// 转化输入为代码
    QString execute(QString testcase,bool isAnswerCode = false,bool _update = true);// 执行代码
    void updateOutput(const QString & m,bool clear = false,bool update = true);
signals:
    void updateShow(const QString & m,bool clear = false,bool update = true);
};

struct Stage // 关卡类
{
    QTextDocument* description; // 代码描述
    QTextDocument* answer; // 原始代码
    int caseMinLen = 1; // 最小例子长度
    int caseMaxLen = 7; // 最大例子长度

    QString name; // 关卡名
    QString scriptDescription;// 关卡描述
    QString caseDescription; // 例子描述
    QString answerString;
    Stage() {};
    Stage(QString _name, QString _scriptDescription, QString _caseDescription, QString answer);
    void saveStage();
    void loadStage(QString path); // path:QString("Stage/") + n + ".txt" !!! n需要name去掉 QChar('\n')
};


class System: public QObject // 字符处理类
{
    Q_OBJECT

private:
    static bool error; // 错误全局传递
public:
    bool update;
    int speed;
    bool isPause;
    bool isStop;
    QMutex mutex;
    QWaitCondition condition;

    System(){setup();};
    QString generateCase(Stage *_stage); // 生成测试样例
    void judge(Stage * _stage,Code * _input ,Code * _answer,bool update); // 判断结果对不对
    void run(Stage * _stage,QTextDocument * _input,bool _debug); // 进行整体的代码核验流程
    static QString processError(Error _error,int line,QString * inputString = NULL,QString * answerString = NULL); // 处理error
    void caseAC(); // 一个样例AC
    void allCaseAC(); // 所有样例AC，没写
    void updateOutput(const QString & m,bool clear = false,bool update = true);
    void speedChange(bool adjust);
    void pause();
    void resume();
    void stop();
    void setup();
signals:
    void updateShow(const QString & m,bool clear = false,bool update = true);
    void CalEnd(int returnCode);
    void updateProgress(int clear,bool error);
};


class Command:public QObject // 单句指令类
{
    Q_OBJECT
private:
    CommandType c; // 指令种类
    bool isUsed; // 指令是否被使用过（和once关联）
    QString findString; // 左侧字符串
    QString putString; // 右侧字符串
    QString stringCode; // 原始的string形式的code
public:
    Command();
    void setCommandType(CommandType _c); // 4个set
    void setStringCode(QString _s);
    void setFindString(QString _s);
    void setPutString(QString _s);
    int work(bool isAnswerCode,QString * _case,bool update = true); // 进行一行运算
    void updateOutput(const QString & m,bool clear = false,bool update = true);
signals:
    void updateShow(const QString & m,bool clear = false,bool update = true);
};

#endif // SYSTEM_H


