#include "system.h"

Code::Code()
{
    command = NULL;
    commandLen = 0;
}
void Code::updateOutput(const QString & m,bool ScreenClear,bool update)
{
    if(update)
        emit updateShow(m,ScreenClear);
}
void Code::processDocIntoCode(QTextDocument * _doc)
{
    int blocks = _doc->blockCount();
    command = new Command [blocks];
    int commandLine = 0;
    for(int i = 0;i < blocks;++i)
    {
        QTextBlock t = _doc->findBlockByNumber(i); // 每一行的文本
        QString s = t.text(); // 转化文本块为文字
        if(s.trimmed() == "") // 空行，跳过
        {
            continue;
        }
        command[commandLine].setStringCode(s);
        connect(&command[i],&Command::updateShow,this,&Code::updateOutput);
        if(s.indexOf("=") != -1) // 检查有没有=
        {
            QStringList sList =  s.split("=");
            if(sList.size() == 2) // 检查是否只有一个=
            {
                bool isFirstStartKeyword = false;
                bool isFirstEndKeyword = false;
                processKeyword(sList[0],"(once)",command[commandLine],i + 1,true,isFirstStartKeyword);
                processKeyword(sList[0],"(start)",command[commandLine],i + 1,true,isFirstStartKeyword);
                processKeyword(sList[0],"(end)",command[commandLine],i + 1,true,isFirstStartKeyword);
                processKeyword(sList[1],"(start)",command[commandLine],i + 1,false,isFirstEndKeyword);
                processKeyword(sList[1],"(end)",command[commandLine],i + 1,false,isFirstEndKeyword);
                processKeyword(sList[1],"(return)",command[commandLine],i + 1,false,isFirstEndKeyword);
            }
            else
            {
                // 太多=了
                QString c = System::processError(CE_ES,i + 1);
                updateOutput(c);;
                return;
            }
            command[commandLine].setFindString(sList[0].trimmed());
            command[commandLine].setPutString(sList[1].trimmed());
            commandLine++;
        }
        else
        {
            // 没有 =
            QString c = System::processError(CE_EN,i + 1);
            updateOutput(c);
            return;
        }
    }
    commandLen = commandLine;
}
int Code::processKeyword(QString & source,const QString & keyword,Command & command,int line,bool isStart,bool isFirstKeyword)
{
    int keywordIndex = source.indexOf(keyword);
    if(keywordIndex != -1)
    {
        if(isFirstKeyword)
        {
            System::processError(CE_KS,line);
        }
        if(isStart)
        {
            command.setStartKeyword(keyword);
            source.remove(keywordIndex,keyword.length());
        }
        else if(!isStart)
        {
            command.setEndKeyword(keyword);
            source.remove(keywordIndex,keyword.length());
        }
    }
    return keywordIndex;
}
QString Code::executeCode(QString testcase,bool isAnswerCode,bool _update)
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
        for(int i = 0;i <= commandLen;++i)
        {
            if(i == commandLen) // 走到头了
            {
                isEnd = true;
                break;
            }
            int result = (command + i)->work(isAnswerCode,&testcase,_update); // 执行代码
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
            else if(result == 2)
            {
                if(!isAnswerCode) // 输出当前修改情况
                    updateOutput(testcase,false,_update);
                isEnd = true;
                break;
            }
        }
    }
    return testcase;
}
/*
------------------------------------------------------------------------------------
*/
/*
void System::speedChange(bool adjust)
{
    if(adjust)
    {
        speed = std::min(MAXSPEED,speed + 1);
    }
    else
    {
        speed = std::max(MINSPEED,speed - 1);
    }
}*/
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
    resume();
    isStop = true;
}
void System::judge(Stage *_stage, Code * _input ,Code * _answer,bool update)
{
    bool sentExecution = true;
    for(int i = 0;i <= CASENUM;++i)
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
        if(speed == MAXSPEED)
        {
            sentExecution = false;
        }
        else
        {
            sentExecution = true;
        }
        QString testcase = generateCase(_stage);
        updateOutput("",true); // 清除
        updateOutput("Test Case: " + QString::number(i));
        updateOutput("Input: " + testcase + "\n");
        QString inputString = _input->executeCode(testcase,false,sentExecution); // 执行输入代码
        QString answerString = _answer->executeCode(testcase,true,sentExecution); // 计算正确值
        if(inputString != answerString)
        {
            QString c = processError(WA,0,&inputString,&answerString); // 有case 错误
            updateOutput(c); // 更新文本
            return;
        }
        else
        {
            updateOutput("Your answer: " + inputString);
            updateOutput("Right answer: " + answerString + "\n");
            caseAC();
        }
        QThread::msleep(700 - speed * 300);
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
    test.processDocIntoCode(_input);
    if(error)
    {
        return;
    }
    answer.processDocIntoCode(_stage->answer);
    if(error)
    {
        return;
    }
    judge(_stage,&test,&answer,update);
    if(isStop)
    {
        emit endRun(0);
    }
}
void System::caseAC()
{
    updateOutput("Accepted \n");
}
void System::allCaseAC()
{
    updateOutput("Stage complete");
    stageClear();
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

void System::updateOutput(const QString & m,bool ScreenClear,bool update)
{
    if(update)
        emit System::updateShow(m,ScreenClear);
}
/*
------------------------------------------------------------------------------------
*/
Command::Command()
{
    isUsed = false;
    findString = QString();
    putString = QString();
    startKeyword = QString();
    endKeyword = QString();
}
void Command::updateOutput(const QString & m,bool ScreenClear,bool update)
{
    if(update)
        emit updateShow(m,ScreenClear);
}
int Command::work(bool isAnswerCode,QString * _case,bool _update)
{

    if(!isUsed) // 如果是可以被使用的
    {
        if(endKeyword == "(return)")
        {
            _case->clear();
            _case->append(putString);
            return 2;
        }
        int pos = -1;
        int searchPlace = 0;
        if(startKeyword == "(start)")
        {
            searchPlace = 0;
        }
        else if(startKeyword == "(end)")
        {
            searchPlace = _case->length() - 1;
        }
        else
        {
            searchPlace = -1;
        }
        if((_case->indexOf(findString) == searchPlace && searchPlace != -1) ||
            (_case->indexOf(findString) != -1 && searchPlace == -1) )
        {
            if(!isAnswerCode)
                updateOutput("    " + stringCode,false,_update);
            pos = _case->indexOf(findString);
            _case->remove(pos,findString.length());
        }
        if(pos == -1)
        {
            // 未找到，进入下一个指令
            return 1;
        }
        else
        {
            if(endKeyword == "(start)")
            {
                _case->prepend(putString);
            }
            else if(endKeyword == "(end)")
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
    if(startKeyword == "(once)")
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
    plot = "";
}
void setPlot(Stage * stages[10][10],int chapters,const int levels[10])
{
    QFileInfo fileInfo(__FILE__);
    QDir sourceDir = fileInfo.dir();
    QFile file(sourceDir.filePath("plot.txt"));
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file" << file.errorString();
        return;
    }
    QTextStream in(&file); in.setAutoDetectUnicode(true);
    for(int i = 1;i <= chapters;++i)
    {
        for(int j = 1;j <= levels[i];++j)
        {
            QString plot = "";
            QString curLine = "";
            while(curLine != "end\r\n")
            {
                plot += curLine;
                curLine = file.readLine();
            }
            stages[i][j]->plot = plot;
        }

    }
}
void setInstruction(Stage * stages[10][10],int chapters,const int levels[10],const int instructionStages[10])
{
    QFileInfo fileInfo(__FILE__);
    QDir sourceDir = fileInfo.dir();
    QFile file(sourceDir.filePath("instructions.txt"));
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file" << file.errorString();
        return;
    }
    QTextStream in(&file); in.setAutoDetectUnicode(true);
    QString instructions[5] = {};
    for(int i = 1;i <= chapters;++i)
    {
        QString instruction = "";
        QString curLine = "";
        while(curLine != "end\r\n")
        {
            instruction += curLine;
            curLine = file.readLine();
        }
        instructions[i] =  instructions[i - 1] + instruction;
    }
    int p = 1;
    int t = 1;
    for(int i = 1;i <= chapters;++i)
        for(int j = 1;j <= levels[i];++j)
        {
            if (p >= instructionStages[t + 1])
            {
                t++;
            }
            stages[i][j]->instruction = instructions[t];
            p++;
        }
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

Stage::Stage(QString name_, bool onlyStory_)
{
    name = name_;
    onlyStory = onlyStory_;
}
