#ifndef SYSTEM_H
#define SYSTEM_H

#endif // SYSTEM_H
#include <QString>
#include <QTextDocument>
#include <QTextBlock>
#include <QRandomGenerator64>
#include <QTextBrowser>
class Command;
class System;
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
    bool isReturn;
};
struct Code // 代码块
{
private:
    Command * command; // 转化为可执行的代码
    int commandLen; // 代码行数量
public:
    Code();
    void process(QTextDocument * _doc);// 转化输入为代码
    QString execute(QString testcase,bool isAnswer = false);// 执行代码
};

struct Stage{
    QTextDocument * description; // 代码描述
    QTextDocument * answer; // 原始代码
    int caseMinLen = 1; // 最小例子长度
    int caseMaxLen = 7; // 最大例子长度
    Stage(){};
};

class System // 字符处理类
{
private:
    static bool error;
public:
    static QTextBrowser * logWidget;
    System(){};
    QString generateCase(Stage *_stage); // 生成测试样例
    void judge(Stage * _stage,Code * _input ,Code * _answer); // 判断结果对不对
    void run(Stage * _stage,QTextDocument * _input,bool _debug); // 进行整体的代码核验流程
    static void processError(Error _error,int line,QString * inputString = NULL,QString * answerString = NULL); // 处理error
    void caseAC();
    void allCaseAC();
};


class Command // 单句指令类
{
private:
    CommandType c; // 指令种类
    bool isUsed; // 指令是否被使用过（和once关联）
    QString findString; // 左侧字符串
    QString putString; // 右侧字符串
    QString stringCode; // 原始的string形式的code
public:
    Command();
    void setCommandType(CommandType _c);
    void setStringCode(QString _s);
    void setFindString(QString _s);
    void setPutString(QString _s);
    int work(bool isAnswer,QString * _case); // 进行一行运算
};

