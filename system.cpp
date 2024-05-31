#include "system.h"

Code::Code()
{
    command = NULL;
    commandLen = 0;
}
void Code::updateOutput(const QString & m,bool clear,bool update)
{
    if(update)
        emit updateShow(m,clear);
}
void Code::process(QTextDocument * _doc)
{
    int blocks = _doc->blockCount();
    commandLen = blocks - 1;
    command = new Command [blocks];
    updateOutput("This time :" + QString::number(blocks));
    //System::logWidget->append("This time :" + QString::number(blocks));
    for(int i = 0;i < blocks;++i)
    {
        QTextBlock t = _doc->findBlockByNumber(i); // 每一行的文本
        QString s = t.text(); // 转化文本块为文字
        command[i].setStringCode(s);
        CommandType c = {};
        if(s.indexOf("=") != -1) // 检查有没有=
        {
            QStringList sList =  s.split("=");
            if(sList.size() == 2) // 检查是否只有一个=
            {
                // 检查是否是指令
                bool firstKeyword = false;
                if(sList[0].indexOf("(once)") != -1)
                {
                    if(!firstKeyword)
                    {
                        firstKeyword = true;
                        c.isOnce = true;
                        int st = sList[0].indexOf("(once)");
                        sList[0].remove(st,6); // 去除关键字
                    }
                    else
                    {
                        // 处理多指令异常
                        QString c = System::processError(CE_KS,i + 1);
                        updateOutput(c);
                        return;
                    }
                }
                else if(sList[0].indexOf("(start)") != -1)
                {
                    if(!firstKeyword)
                    {
                        firstKeyword = true;
                        c.isStartFind = true;
                        int st = sList[0].indexOf("(start)");
                        sList[0].remove(st,7); // 去除关键字
                    }
                    else
                    {
                        // 处理多指令异常
                        QString c = System::processError(CE_KS,i + 1);
                        updateOutput(c);
                        return;
                    }
                }
                else if(sList[1].indexOf("(start)") != -1)
                {
                    if(!firstKeyword)
                    {
                        firstKeyword = true;
                        c.isStartPut = true;
                        int st = sList[0].indexOf("(start)");
                        sList[0].remove(st,7); // 去除关键字
                    }
                    else
                    {
                        // 处理多指令异常
                        QString c = System::processError(CE_KS,i + 1);
                        updateOutput(c);
                        return;
                    }
                }
                else if(sList[0].indexOf("(end)") != -1)
                {
                    if(!firstKeyword)
                    {
                        firstKeyword = true;
                        c.isEndFind = true;
                        int st = sList[0].indexOf("(end)");
                        sList[0].remove(st,5); // 去除关键字
                    }
                    else
                    {
                        // 处理多指令异常
                        QString c = System::processError(CE_KS,i + 1);
                        updateOutput(c);
                        return;
                    }
                }
                else if(sList[1].indexOf("(end)") != -1)
                {
                    if(!firstKeyword)
                    {
                        firstKeyword = true;
                        c.isEndPut = true;
                        int st = sList[0].indexOf("(end)");
                        sList[0].remove(st,5); // 去除关键字
                    }
                    else
                    {
                        // 处理多指令异常
                        QString c = System::processError(CE_KS,i + 1);
                        updateOutput(c);
                        return;
                    }
                }
                else if(sList[1].indexOf("(return)") != -1)
                {
                    if(!firstKeyword)
                    {
                        firstKeyword = true;
                        c.isReturn = true;
                        int st = sList[0].indexOf("(return)");
                        sList[0].remove(st,8); // 去除关键字
                    }
                    else
                    {
                        // 处理多指令异常
                        QString c = System::processError(CE_KS,i + 1);
                        updateOutput(c);
                        return;
                    }
                }
                command[i].setCommandType(c);
                command[i].setFindString( sList[0].trimmed()); // 移除首尾空白
                command[i].setPutString(sList[1].trimmed());
                connect(&command[i],&Command::updateShow,this,&Code::updateOutput); // 传递信号
            }
            else
            {
                // 太多=了
                QString c = System::processError(CE_ES,i + 1);
                updateOutput(c);;
                return;
            }
        }
        else
        {
            if(s.trimmed() == "") // 空行
            {
                return;
            }
            else
            {
                // 没有 =
                QString c = System::processError(CE_EN,i + 1);
                updateOutput(c);
                return;
            }

        }

    }
}
QString Code::execute(QString testcase,bool isAnswerCode,bool _update)
{
    bool isEnd = false;
    int looptime = 0;
    if(!isAnswerCode) // 测试代码输出初始例子
        updateOutput(testcase,false,_update);
    while(!isEnd)
    {
        looptime++;
        if(looptime >= MAXTIME) // 陷入了循环
        {
            QString c = System::processError(TLE,0);
            updateOutput(c);
            break;
        }
        for(int i = 0;i <= commandLen + 1;++i)
        {
            if(i == commandLen + 1) // 走到头了
            {
                isEnd = true;
                break;
            }
            int result = (command + i)->work(isAnswerCode,&testcase); // 执行代码
            if(result == 1) // 没找到
            {
                continue;
            }
            else if(result == 0) // 成功找到
            {
                if(!isAnswerCode) // 输出当前修改情况
                    updateOutput(testcase,false,_update);
                break;
            }
        }
    }
    return testcase;
}
/*
------------------------------------------------------------------------------------
*/
void System::speedChange(bool adjust)
{
    if(adjust)
    {
        speed = std::max(2,speed + 1);
    }
    else
    {
        speed = std::min(0,speed - 1);
    }
}
void System::setup()
{
    error = false;
    update = true;
    speed = 0;
    isPause = false;
    isStop = false;
}
void System::pause()
{
    QMutexLocker locker(&mutex);
    isPause = true;
}
void System::resume()
{
    QMutexLocker locker(&mutex);
    isPause = false;
    condition.wakeAll();
}
void System::stop()
{
    isStop = true;
}
void System::judge(Stage *_stage, Code * _input ,Code * _answer,bool update)
{
    for(int i = 0;i < 3287;++i)
    {
        if(isPause)
        {
            mutex.lock();
            condition.wait(&mutex);
            mutex.unlock();
        }
        if(isStop)
        {
            break;
        }
        updateOutput("",true); // 清除
        updateOutput("Test Case: " + QString::number(i));
        //logWidget->clear();
        //logWidget->append("Test Case: " + QString::number(i));
        QString testcase = generateCase(_stage);
        updateOutput("Input: " + testcase + "\n");
        //logWidget->append("Input: " + testcase + "\n"); // 显示初始case
        QString inputString = _input->execute(testcase,false); // 执行输入代码
        QString answerString = _answer->execute(testcase,true); // 计算正确值
        if(inputString != answerString)
        {
            QString c = processError(WA,0,&inputString,&answerString); // 有case 错误
            updateOutput(c);
            return;
        }
        else
        {
            updateOutput("Your answer: " +answerString);
            caseAC();
        }
        if(speed == 0)
        {
            QThread::msleep(1000);
        }
        if(speed == 1)
        {
            QThread::msleep(600);
        }
        if(speed == 2)
        {
            QThread::msleep(200);
        }
    }
    if(isStop)
    {
        return;
    }
    allCaseAC();
    return;
}
QString System::generateCase(Stage *_stage)
{
    int len = QRandomGenerator::global()->bounded(_stage->caseMinLen,_stage->caseMaxLen);
    QString s = QString();
    for(int i = 0;i < len;++i)
    {
        switch(QRandomGenerator::global()->bounded(3))
        {
        case 0:
            s.append('a');
            break;
        case 1:
            s.append('b');
            break;
        case 2:
            s.append('c');
            break;
        }
    }
    return s;
}

void System::run(Stage * _stage,QTextDocument * _input,bool _debug) // incomplete debug mode
{
    System::error = false;
    Code test = Code();
    Code answer = Code();
    connect(&test,&Code::updateShow,this,&System::updateOutput);
    connect(&answer,&Code::updateShow,this,&System::updateOutput);
    test.process(_input);
    if(error)
    {
        return;
    }
    answer.process(_stage->answer);
    if(error)
    {
        return;
    }
    judge(_stage,&test,&answer,update);
    emit CalEnd(0);
}
void System::caseAC()
{
    updateOutput("Accepted");
    //logWidget->append("Accepted");
}
void System::allCaseAC()
{
    // incomplete
}
bool System::error = false;

QString System::processError(Error _error,int line,QString * inputString,QString * answerString) // incomplete
{
    error = true;
    QString report = QString();
    switch(_error)
    {
    case WA:
        report += "Wrong answer \n Your answer: " + *inputString + "\nRight answer: "  + *answerString;
        break;
    case TLE:
        report += "Time Limit Exceed.\n Single loop at some code";
        break;
    case CE_KS:
        report += "Compile error.\n Too many key words / used key word not in valid key words.\n at line " + QString::number(line);
        break;
    case CE_ES:
        report += "Compile error.\n too many = at line " + QString::number(line);
        break;
    case CE_EN:
        report += "Compile error.\n no ‘=’ at line " + QString::number(line);
        break;
    }
    return report;
}

void System::updateOutput(const QString & m,bool clear,bool update)
{
    if(update)
        emit System::updateShow(m,clear);
}
/*
------------------------------------------------------------------------------------
*/
Command::Command()
{
    c = {};
    isUsed = false;
    findString = QString();
    putString = QString();
}
void Command::setFindString(QString _s)
{
    findString = _s;
}
void Command::setPutString(QString _s)
{
    putString = _s;
}
void Command::setStringCode(QString _s)
{
    stringCode = _s;
}
void Command::setCommandType(CommandType _c)
{
    c.isOnce = _c.isOnce;
    c.isStartFind = _c.isStartFind;
    c.isEndFind = _c.isEndFind;
    c.isStartPut = _c.isStartPut;
    c.isEndPut = _c.isEndPut;
    c.isReturn = _c.isReturn;
    isUsed = false;
}
void Command::updateOutput(const QString & m,bool clear,bool update)
{
    if(update)
        emit updateShow(m,clear);
}
int Command::work(bool isAnswerCode,QString * _case,bool _update)
{
    if(!isUsed) // 如果是可以被使用的
    {
        int pos = -1;
        if(c.isStartFind)
        {
            if(_case->indexOf(findString) == 0)
            {
                if(!isAnswerCode)
                    updateOutput("    " + stringCode,false,_update);
                pos = _case->indexOf(findString);
                _case->remove(pos,findString.length());
            }
        }
        else if(c.isEndFind)
        {
            if(_case->lastIndexOf(findString) == _case->length() - 1)
            {
                if(!isAnswerCode)
                    updateOutput("    " + stringCode,false,_update);
                pos = _case->indexOf(findString);
                _case->remove(pos,findString.length());
            }
        }
        else
        {
            if(_case->indexOf(findString) != -1)
            {
                if(!isAnswerCode)
                    updateOutput("    " + stringCode,false,_update);
                pos = _case->indexOf(findString);
                _case->remove(pos,findString.length());
            }
        }
        if(pos == -1)
        {
            // 未找到，进入下一个指令
            return 1;
        }
        else
        {
            if(c.isStartPut)
            {
                _case->prepend(putString);
            }
            else if(c.isEndPut)
            {
                _case->append(putString);
            }
            else
            {
                _case->insert(pos,putString);
            }
        }
    }
    else
    {
        // 进行下一个指令
        return 1;
    }
    if(c.isOnce)
    {
        isUsed = true;
    }
    return 0;
}

Stage::Stage(QString _name, QString _scriptDescription, QString _caseDescription, QString _answer)
{
    name = _name;
    scriptDescription = _scriptDescription;
    caseDescription = _caseDescription;
    answer = new QTextDocument();
    answer->setPlainText(_answer);
    answerString = _answer;
}

void Stage::saveStage()
{
    QFileInfo fileInfo(__FILE__);
    QDir sourceDir = fileInfo.dir();
    QString n = name; n.remove(QChar('\n'));
    qDebug() << sourceDir.filePath(QString("Stage/") + n + ".txt");
    QFile file(sourceDir.filePath(QString("Stage/") + n + ".txt"));
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open file" << file.errorString();
        return;
    }
    QTextStream out(&file); out.setAutoDetectUnicode(true);
    if (answer != nullptr)
        out << name << scriptDescription << caseDescription << QString(answer->toPlainText());
    else
        out << name << scriptDescription << caseDescription << answerString;
    file.close();
    //loadStage(QString("Stage/") + n + ".txt");
    //qDebug() << name << scriptDescription << caseDescription << answerString;
}

void Stage::loadStage(QString path)
{
    QFileInfo fileInfo(__FILE__);
    QDir sourceDir = fileInfo.dir();
    QFile file(sourceDir.filePath(path));
    qDebug() << sourceDir.filePath(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file";
        return;
    }
    QTextStream in(&file); in.setAutoDetectUnicode(true);
    name = in.readLine(); scriptDescription = in.readLine(); caseDescription = in.readLine() + QString("\n"); caseDescription += in.readLine(); answerString = in.readAll();
    answer = new QTextDocument();
    answer->setPlainText(answerString);
    file.close();
}
