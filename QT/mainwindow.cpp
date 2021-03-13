#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"method.h"
#include<QTextDocument>
#include<QDebug>
#include<QTimer>
#include<string>
#include<QCursor>
#include<QColor>
#include<QPalette>

using namespace std;
extern QString res;
extern bool flag;
extern char*src;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    timer->setInterval(500);
    timer->start();
    ui->textBrowser->setTextColor(QColor(232,232,232));
    QPalette pa=ui->textBrowser->palette();
    pa.setColor(QPalette::Base,QColor(54,54,54));
    ui->textBrowser->setPalette(pa);
    //    ui->textBrowser->append("<font color=\"#00FF00\">绿色字体hax,haxx</font> ");
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkdef()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkregister()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkequal()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkmark()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkmark1()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkregister1()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkregister2()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkregister3()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkregister4()));
    ui->toolBar->addAction(ui->actionrun);
    this->ui->actionrun->setStatusTip("Machine is running the code ...");
    connect(ui->actionrun,&QAction::triggered,this,[&]{
        QString content = ui->textBrowser->document()->toPlainText();
        string s = content.toStdString();
        int temp = Excute(s);
        ui->textBrowser_2->clear();
        ui->textBrowser_2->append(res);
        ui->textBrowser_2->append("process exit...with code "+QString::number(temp));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*==============================*槽函数==============================*/
void MainWindow::Checkdef(){
    QString search_text = "def";//被查找数据
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(255,127,0));
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull())
        {
            if(!found)
            {
                found = true;
            }
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //结束
    if (found == false) {}
    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
    cursor = ui->textBrowser->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
    return;
}

void MainWindow::Checkregister(){
    QString search_text = "return";//被查找数据
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(255,127,0));
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull())
        {
            if(!found)
            {
                found = true;
            }
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //结束
    if (found == false) {}
    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
    cursor = ui->textBrowser->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
    return;
}

void MainWindow::Checkequal(){
    QString search_text = "=";//被查找数据
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(255,236,139));
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull())
        {
            if(!found)
            {
                found = true;
            }
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //结束
    if (found == false) {}
    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
    cursor = ui->textBrowser->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
    return;
}

void MainWindow::Checkmark(){
    QString search_text = "\"";//被查找数据
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(255,127,0));
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull())
        {
            if(!found)
            {
                found = true;
            }
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //结束
    if (found == false) {}
    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
    cursor = ui->textBrowser->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
    return;
}

void MainWindow::Checkmark1(){
    QString search_text = ";";//被查找数据
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(255,236,139));
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull())
        {
            if(!found)
            {
                found = true;
            }
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //结束
    if (found == false) {}
    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
    cursor = ui->textBrowser->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
    return;
}

void MainWindow::Checkregister1(){
    QString search_text = "if";//被查找数据
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(0,206,209));
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull())
        {
            if(!found)
            {
                found = true;
            }
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //结束
    if (found == false) {}
    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
    cursor = ui->textBrowser->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
    return;
}

void MainWindow::Checkregister2(){
    QString search_text = "else";//被查找数据
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(0,206,209));
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull())
        {
            if(!found)
            {
                found = true;
            }
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //结束
    if (found == false) {}
    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
    cursor = ui->textBrowser->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
    return;
}

void MainWindow::Checkregister3(){
    QString search_text = "while";//被查找数据
    if (search_text.trimmed().isEmpty())//trimmed移除前后空白字符并判断是不是为空
    {
        QTextCharFormat fmt;//文本字符格式
        fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
        QTextCursor cursor = ui->textBrowser->textCursor();//获取文本光标
        cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
        ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
        return;
    }
    else
    {
        QTextDocument *document = ui->textBrowser->document();//全部数据
        bool found = false;
        QTextCursor highlight_cursor(document);
        QTextCursor cursor(document);
        //开始
        cursor.beginEditBlock();
        QTextCharFormat color_format(highlight_cursor.charFormat());
        QTextCharFormat color_format1(highlight_cursor.charFormat());
        color_format.setForeground(QColor(0,206,209));
        while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
            //查找指定的文本，匹配整个单词
            highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
            if (!highlight_cursor.isNull())
            {
                if(!found)
                {
                    found = true;
                }
                highlight_cursor.mergeCharFormat(color_format);
            }
        }
        cursor.endEditBlock();
        //结束
        if (found == false) {}
        QTextCharFormat fmt;//文本字符格式
        fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
        cursor = ui->textBrowser->textCursor();//获取文本光标
        cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
        ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
        return;
    }
}

void MainWindow::Checkregister4(){
    QString search_text = "for";//被查找数据
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(0,206,209));
    while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
        //查找指定的文本，匹配整个单词
        highlight_cursor = document->find(search_text, highlight_cursor, QTextDocument::FindWholeWords);
        if (!highlight_cursor.isNull())
        {
            if(!found)
            {
                found = true;
            }
            highlight_cursor.mergeCharFormat(color_format);
        }
    }
    cursor.endEditBlock();
    //结束
    if (found == false) {}
    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(QColor(232,232,232));// 前景色(即字体色)设为color色
    cursor = ui->textBrowser->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textBrowser->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
    return;
}
/**/
