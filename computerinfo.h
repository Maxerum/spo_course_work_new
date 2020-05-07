#ifndef COMPUTERINFO_H
#define COMPUTERINFO_H
#include "mainwindow.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <TCHAR.H>
#include <tlhelp32.h>

using namespace std;

class computerInfo
{

public:
    computerInfo();
    void get_computer_name(Ui::MainWindow *ui);//+

};

class processorInfo{
public:
    processorInfo();
    void get_processor_type(Ui::MainWindow *ui);//+
};


class userInfo{
public:
    userInfo();
    void get_user_name(Ui::MainWindow *ui);//+
};

class osInfo{
public:
    osInfo();
    void get_os_version_name(Ui::MainWindow *ui);//-
    void get_windows_directory(Ui::MainWindow *ui);
    void get_system_directory(Ui::MainWindow *ui);
};

class driveInfo{
public:
    driveInfo();
    void get_drive_type(Ui::MainWindow *ui);//+
    void get_pass_volumes(Ui::MainWindow *ui);//+
    void get_free_space(Ui::MainWindow *ui);//-
};


class memoryInfo:public MainWindow{
public:
    memoryInfo();
    void get_mem_info(Ui::MainWindow *ui);//+
};

class displayInfo:public MainWindow{
public:
    displayInfo();
   void get_display_info(Ui::MainWindow *ui);//+
};


#endif // COMPUTERINFO_H
