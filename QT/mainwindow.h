#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    friend void syntaxError(int k, long int l,string s);

private slots:
    void Checkdef();//def
    void Checkregister();//return
    void Checkregister1();//if
    void Checkregister2();//else
    void Checkregister3();//while
    void Checkregister4();//for
    void Checkequal();//=
    void Checkmark();//"
    void Checkmark1();//;


private:

};
#endif // MAINWINDOW_H
