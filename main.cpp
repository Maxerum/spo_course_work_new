#define _CRT_SECURE_NO_WARNINGS
#include "mainwindow.h"
#include "computerinfo.h"
#include <Windows.h>
#include <iostream>
#include <QApplication>
#include <QTimer>
using namespace std;

#define UNLEN 256

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //QTimer::singleShot(5 * 60 * 1000, &a, SLOT(quit()));
    //w.get_process_list();
    //w.get_information();
    w.show();
    return a.exec();
}
