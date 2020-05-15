#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <TCHAR.H>
#include <tlhelp32.h>
#include <QMainWindow>
//#include "computerinfo.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class computerInfo
{
    char computer_name[100];
public:
    computerInfo();
    char *get_current_name(){return this->computer_name;}
    char* get_computer_name(/*Ui::MainWindow *ui*/);//+
    char *copy(char *buffer){strcpy_s(computer_name,buffer);}
};

class userInfo{
public:
    userInfo();
    char* get_user_name(/*Ui::MainWindow *ui*/);//+
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class processorInfo;
    friend class osInfo;
    friend class driveInfo;
    friend class memoryInfo;
    friend class displayInfo;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void get_information();
    void PrintProcessList(HANDLE CONST hStdOut);
    void PrintModuleList(HANDLE hStdOut, DWORD dwProcessId );
    void get_process_list();

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
};



#endif // MAINWINDOW_H
