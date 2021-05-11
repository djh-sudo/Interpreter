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
#include<QRegExp>
using namespace std;
extern QString res;
extern int flag;
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

    connect(timer,SIGNAL(timeout()),this,SLOT(Check()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkregister()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkequal()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Checkmark()));

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


void MainWindow::Check(){
    QRegExp search_text = QRegExp("return|for|def");
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
    QRegExp search_text = QRegExp("=|;|(\\d+)");
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
    QRegExp search_text = QRegExp("(\\\"(.*)\\\")");
    QTextDocument *document = ui->textBrowser->document();//全部数据
    bool found = false;
    QTextCursor highlight_cursor(document);
    QTextCursor cursor(document);
    //开始
    cursor.beginEditBlock();
    QTextCharFormat color_format(highlight_cursor.charFormat());
    QTextCharFormat color_format1(highlight_cursor.charFormat());
    color_format.setForeground(QColor(155,207,10));
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
    QRegExp search_text = QRegExp("if|else|while");
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

