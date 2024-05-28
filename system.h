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
struct Code // 代码块
{
private:
    Command * command; // 可执行的代码，一个command是一行代码
    int commandLen; // 代码行数量
public:
    Code();
    void process(QTextDocument * _doc);// 转化输入为代码
    QString execute(QString testcase,bool isAnswerCode = false);// 执行代码
};

struct Stage // 关卡类
{
    QTextDocument * description; // 代码描述
    QTextDocument * answer; // 原始代码
    int caseMinLen = 1; // 最小例子长度
    int caseMaxLen = 7; // 最大例子长度

	QString name; // 关卡名
	QString scriptDescription;// 关卡描述

    Stage(){};
};

class System // 字符处理类
{
private:
    static bool error; // 错误全局传递
public:
    static QTextBrowser * logWidget; // 外部输出文本框，即log文本框
    System(){};
    QString generateCase(Stage *_stage); // 生成测试样例
    void judge(Stage * _stage,Code * _input ,Code * _answer); // 判断结果对不对
    void run(Stage * _stage,QTextDocument * _input,bool _debug); // 进行整体的代码核验流程
    static void processError(Error _error,int line,QString * inputString = NULL,QString * answerString = NULL); // 处理error
    void caseAC(); // 一个样例AC
    void allCaseAC(); // 所有样例AC，没写
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
    void setCommandType(CommandType _c); // 4个set
    void setStringCode(QString _s);
    void setFindString(QString _s);
    void setPutString(QString _s);
    int work(bool isAnswerCode,QString * _case); // 进行一行运算
};

