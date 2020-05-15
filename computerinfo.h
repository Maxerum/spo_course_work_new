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

//class computerInfo
//{
//    char computer_name[100];
//public:
//    computerInfo();
//    char *get_current_name(){return this->computer_name;}
//    char* get_computer_name(/*Ui::MainWindow *ui*/);//+
//    char *copy(char *buffer){strcpy_s(computer_name,buffer);}
//};

class processorInfo{
public:
    processorInfo();
    void get_processor_type(Ui::MainWindow *ui);//+
    void get_processor_load(Ui::MainWindow *ui);
};


//class userInfo{
//public:
//    userInfo();
//    char* get_user_name(/*Ui::MainWindow *ui*/);//+
//};

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
};


class memoryInfo:public MainWindow{
//    char persent[10];
//    char all_memory[10];
//    char free_memory[10];
//    char virtual_size_memory[10];
//    char file_page[10];
public:
//    void set_all_memory(char *all_memory){strcpy(this->all_memory,all_memory);}
//    void set_file_page(char *file_page){strcpy(this->file_page,file_page);}
//    void set_virtual_size_memory(char *virtual_size_memory){strcpy(this->virtual_size_memory,virtual_size_memory);}
    //void
    memoryInfo();
    void get_mem_info(Ui::MainWindow *ui);//+
};

class displayInfo:public MainWindow{
public:
   displayInfo();
   void get_display_info(Ui::MainWindow *ui);//+
};


#endif // COMPUTERINFO_H
