#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <TCHAR.H>
#include <tlhelp32.h>
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class computerInfo;
    friend class processorInfo;
    friend class osInfo;
    friend class driveInfo;
    friend class memoryInfo;
    friend class userInfo;
    friend class displayInfo;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void full_table();
    void get_information();
//    void get_process_list();
    void PrintProcessList(HANDLE CONST hStdOut);
    void PrintModuleList(HANDLE hStdOut, DWORD dwProcessId );
    void get_process_list();

/*private slots:
    void on_tableWidget_cellActivated(int row, int column);*/

private:
    Ui::MainWindow *ui;
    QTimer *tmr;

public:
    computerInfo *compInfo;
    userInfo *user_info;
    processorInfo *procInfo;
    osInfo *os_info;
    driveInfo *drive_info;
    memoryInfo *mem_info;
    displayInfo *disp_info;
private slots:
    void update();
    //void updateTime();
};



#endif // MAINWINDOW_H
