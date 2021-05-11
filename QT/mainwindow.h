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
    void Check();//def
    void Checkregister();
    void Checkequal();//=
    void Checkmark();//"


private:

};
#endif // MAINWINDOW_H
