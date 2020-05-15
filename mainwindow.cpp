#define _CRT_SECURE_NO_WARNINGS
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "computerinfo.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <TCHAR.H>
#include <tlhelp32.h>
#include <string.h>
#include "VersionHelpers.h"
#include "QTimer"

using namespace std;
#define UNLEN 256

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)//,mt(new table)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle("System information");
    tmr = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tmr->setInterval(1000); // Задаем интервал таймера
    connect(tmr, SIGNAL(timeout()), this, SLOT(update())); // Подключаем сигнал таймера к нашему слоту
    tmr->start(); // Запускаем таймер
    computerInfo *comp_info;
    char buffer[100];
    strcpy(buffer,comp_info->get_computer_name());
    ui->computer_name->setText(buffer);
    userInfo *user_info;
    strcpy(buffer,user_info->get_user_name());
    ui->label_7->setText(buffer);
    get_information();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete tmr;
}

void driveInfo::get_drive_type(Ui::MainWindow *ui){
    int sz = GetLogicalDriveStrings(NULL, 0);
    TCHAR* szLogicalDrives = new TCHAR[sz];
    GetLogicalDriveStrings(sz, szLogicalDrives);
    int counter = 0;
    while (*szLogicalDrives)
    {
        TCHAR szDisk[80];
        char buf[30];
        char buff[200];
        lstrcpy(szDisk, szLogicalDrives);
        GetDriveType(szDisk);
        UINT uDriveType = GetDriveType(szDisk);
//        if (uDriveType == DRIVE_FIXED)
//        {
            int i = 0;
            while(szDisk[i]!='\0'){
                buff[i] = szDisk[i];
                i++;
            }
            buff[i]='\0';

            __int64 uliTotalBytes;
            __int64 uliFreeBytes;
            GetDiskFreeSpaceEx(szDisk, (PULARGE_INTEGER)&uliFreeBytes, (PULARGE_INTEGER)&uliTotalBytes, NULL);
            int res = uliTotalBytes/ (1024 * 1024 * 1024);
            int freeBytes = uliFreeBytes/ (1024 * 1024 * 1024);
            _itoa(res,buf,10);
            //_itoa(freeBytes,buf,10);
            switch(counter){
            case 0:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                strcat(buff,"\nСвободный объем диска: ");
                _itoa(freeBytes,buf,10);
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser->setText(buff);
                break;
            case 1:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                strcat(buff,"\nСвободный объем диска: ");
                _itoa(freeBytes,buf,10);
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_2->setText(buff);
                break;
            case 2:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                strcat(buff,"\nСвободный объем диска: ");
                _itoa(freeBytes,buf,10);
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_3->setText(buff);
                break;
            case 3:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                strcat(buff,"\nСвободный объем диска: ");
                _itoa(freeBytes,buf,10);
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_4->setText(buff);
                break;
            case 4:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                strcat(buff,"\nСвободный объем диска: ");
                _itoa(freeBytes,buf,10);
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_5->setText(buff);
                break;
            case 5:
                strcat(buff,"\nОбъем диска:");
                strcat(buff,buf);
                strcat(buff," ГБ");
                strcat(buff,"\nСвободный объем диска: ");
                _itoa(freeBytes,buf,10);
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_6->setText(buff);
                break;
            }
        while (*szLogicalDrives) szLogicalDrives++;
        szLogicalDrives++;
        counter++;
   }
}

void MainWindow::get_information()
{
    //compInfo->get_computer_name(ui);
    //user_info->get_user_name(ui);
    procInfo->get_processor_type(ui);
    os_info->get_os_version_name(ui);
    os_info->get_windows_directory(ui);
    os_info->get_system_directory(ui);
    drive_info->get_drive_type(ui);
    mem_info->get_mem_info(ui);
    procInfo->get_processor_load(ui);
    disp_info->get_display_info(ui);
}



void displayInfo::get_display_info(Ui::MainWindow *ui){
    int  nWidth, nHeight;
    nWidth = GetSystemMetrics(SM_CXSCREEN);
    nHeight = GetSystemMetrics(SM_CYSCREEN);
    //printf("%dx% d px \ n", nWidth, nHeight);
    char buf[250];
    char sec_buf[20];
    HDC ScreenDC;
    ScreenDC = GetDC(NULL);
    int x, y, frequency;
    x = GetDeviceCaps(ScreenDC, HORZRES);
    y = GetDeviceCaps(ScreenDC, VERTRES);
    _itoa(x,buf,10);
    _itoa(y,sec_buf,10);
    strcat(buf,"x");
    strcat(buf,sec_buf);
    ui->label_20->setText(buf);

    //get frequency
    frequency = GetDeviceCaps(ScreenDC, VREFRESH);
    _itoa(frequency,sec_buf,10);
    ui->freq->setText(sec_buf);
    //    setlocale(LC_ALL, "");
    DISPLAY_DEVICE sDispDev = { 0 };
    sDispDev.cb = sizeof(DISPLAY_DEVICE);

    if (EnumDisplayDevices(NULL, 0, &sDispDev, 0))
    {
        int i = 0;
        while(sDispDev.DeviceString[i]!='\0'){
            buf[i] = sDispDev.DeviceString[i];
            i++;
        }
        buf[i]='\0';
        ui->display->setText(buf);
    }

    std::wstring devName = sDispDev.DeviceName;

    int i = 0;
    while(sDispDev.DeviceName[i]!='\0'){
        buf[i] = sDispDev.DeviceName[i];
        i++;
    }
    buf[i]='\0';
    ui->label_21->setText(buf);

    if (EnumDisplayDevices(devName.c_str(), 0, &sDispDev, 0))
    {
        int i = 0;
        while(sDispDev.DeviceName[i]!='\0'){
            buf[i] = sDispDev.DeviceName[i];
            i++;
        }
        buf[i]='\0';
        ui->label_22->setText(buf);

    }
}

//void driveInfo::get_pass_volumes(Ui::MainWindow *ui){

//        DWORD  CharCount            = 0;
//        WCHAR  DeviceName[MAX_PATH] = L"";
//        DWORD  Error                = ERROR_SUCCESS;
//        HANDLE FindHandle           = INVALID_HANDLE_VALUE;
//        BOOL   Found                = FALSE;
//        size_t Index                = 0;
//        BOOL   Success              = FALSE;
//        WCHAR  VolumeName[MAX_PATH] = L"";

//        //
//        //  Enumerate all volumes in the system.
//        FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));

//        if (FindHandle == INVALID_HANDLE_VALUE)
//        {
//            Error = GetLastError();
//            wprintf(L"FindFirstVolumeW failed with error code %d\n", Error);
//            return;
//        }

//        for (;;)
//        {

//            Index = wcslen(VolumeName) - 1;

//            if (VolumeName[0]     != L'\\' ||
//                VolumeName[1]     != L'\\' ||
//                VolumeName[2]     != L'?'  ||
//                VolumeName[3]     != L'\\' ||
//                VolumeName[Index] != L'\\')
//            {
//                Error = ERROR_BAD_PATHNAME;
//                wprintf(L"FindFirstVolumeW/FindNextVolumeW returned a bad path: %s\n", VolumeName);
//                break;
//            }

//            VolumeName[Index] = L'\0';

//            CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));

//            VolumeName[Index] = L'\\';

//            if ( CharCount == 0 )
//            {
//                Error = GetLastError();
//                wprintf(L"QueryDosDeviceW failed with error code %d\n", Error);
//                break;
//            }

//            wprintf(L"\nFound a device:\n %s", DeviceName);

//            //ui->textBrowser->setText(L DeviceName);
//            wprintf(L"\nVolume name: %s", VolumeName);
//            wprintf(L"\nPaths:");
////            DisplayVolumePaths(VolumeName);
//            DWORD  CharCount = MAX_PATH + 1;
//            PWCHAR Names     = NULL;
//            PWCHAR NameIdx   = NULL;
//            BOOL   Success   = FALSE;

//            for (;;)
//            {
//                //
//                //  Allocate a buffer to hold the paths.
//                Names = (PWCHAR) new BYTE [CharCount * sizeof(WCHAR)];

//                if ( !Names )
//                {

//                    return;
//                }

//                Success = GetVolumePathNamesForVolumeNameW(
//                    VolumeName, Names, CharCount, &CharCount
//                    );

//                if ( Success )
//                {
//                    break;
//                }

//                if ( GetLastError() != ERROR_MORE_DATA )
//                {
//                    break;
//                }

//                delete [] Names;
//                Names = NULL;
//            }

//            if ( Success )
//            {
//                //
//                //  Display the various paths.
//                for ( NameIdx = Names;
//                      NameIdx[0] != L'\0';
//                      NameIdx += wcslen(NameIdx) + 1 )
//                {
//                    wprintf(L"  %s", NameIdx);
//                }
//                wprintf(L"\n");
//            }

//            if ( Names != NULL )
//            {
//                delete [] Names;
//                Names = NULL;
//            }

//            Success = FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));

//            if ( !Success )
//            {
//                Error = GetLastError();

//                if (Error != ERROR_NO_MORE_FILES)
//                {
//                    wprintf(L"FindNextVolumeW failed with error code %d\n", Error);
//                    break;
//                }

//                Error = ERROR_SUCCESS;
//                break;
//            }
//        }

//        FindVolumeClose(FindHandle);
//        FindHandle = INVALID_HANDLE_VALUE;

//        return;
//}

void memoryInfo::get_mem_info(Ui::MainWindow *ui){//+
    MEMORYSTATUSEX statex;
    char buf[250];
    statex.dwLength = sizeof (statex);

    GlobalMemoryStatusEx (&statex);
    int percent = statex.dwMemoryLoad;
    _itoa(percent,buf,10);
     strcat(buf,"%");

    ui->mem_perc->setText(buf);
    long int mem_value = statex.ullTotalPhys/1024/1024;
    _itoa(mem_value,buf,10);
    strcat(buf,"MB");
    ui->all_mem->setText(buf);

    long int free_mem_value = statex.ullAvailPhys/1024/1024;
    _itoa(free_mem_value,buf,10);
    strcat(buf,"MB");
    ui->label_10->setText(buf);


    //размер виртуальной памяти
    long int virtual_mem_value = statex.ullTotalVirtual/1024/1024;
    _itoa(virtual_mem_value,buf,10);
    strcat(buf,"MB");
    ui->label_13->setText(buf);


    long int virtual_free_mem_value = statex.ullAvailVirtual/1024/1024;
    _itoa(virtual_free_mem_value,buf,10);
    strcat(buf,"MB");
    ui->label_15->setText(buf);

    long int page_file = statex.ullTotalPageFile/1024/1024;
    _itoa(page_file,buf,10);
    strcat(buf,"MB");
    ui->label_28->setText(buf);
}

void osInfo::get_windows_directory(Ui::MainWindow *ui){
    TCHAR path[MAX_PATH];
    GetWindowsDirectory(path,MAX_PATH);
    char buff[255];
    int i;
    for( i = 0;path[i]!='\0';i++){
        buff[i] = path[i];
    }
    buff[i] = '\0';
    ui->label_30->setText( buff);
    //cout<<path;
}

void osInfo::get_system_directory(Ui::MainWindow *ui)
{
    TCHAR path[MAX_PATH];
    GetSystemDirectory(path,MAX_PATH);
    char buff[255];
    int i;
    for( i = 0;path[i]!='\0';i++){
        buff[i] = path[i];
    }
    buff[i] = '\0';
    ui->label_32->setText( buff);
}

void osInfo:: get_os_version_name(Ui::MainWindow *ui){//???

     RTL_OSVERSIONINFOEXW *pk_OsVer = new RTL_OSVERSIONINFOEXW;
     typedef LONG(WINAPI* tRtlGetVersion)(RTL_OSVERSIONINFOEXW*);

     memset(pk_OsVer, 0, sizeof(RTL_OSVERSIONINFOEXW));
     pk_OsVer->dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);

     HMODULE h_NtDll = GetModuleHandleW(L"ntdll.dll");
     tRtlGetVersion f_RtlGetVersion = (tRtlGetVersion)GetProcAddress(h_NtDll, "RtlGetVersion");

     if (!f_RtlGetVersion)
      return; // This will never happen (all processes load ntdll.dll)

     LONG Status = f_RtlGetVersion(pk_OsVer);
     char buf[50];
     char sm_buf[20];
    // strcpy(buf,"Windows");
     _itoa(pk_OsVer->dwMajorVersion,buf,10);
     _itoa(pk_OsVer->dwMinorVersion,sm_buf,10);
     strcat(buf,".");
     strcat(buf,sm_buf);
     if (Status == 0)
         ui->OS->setText(buf);
     // std::cout << "OS version: Windows " << pk_OsVer->dwMajorVersion << "." << pk_OsVer->dwMinorVersion << std::endl;
     else
      std::cout << 0;

     delete pk_OsVer;
}


char* computerInfo::get_computer_name(/*Ui::MainWindow *ui*/){

        char buffer[MAX_COMPUTERNAME_LENGTH + 1];
        size_t origsize = strlen(buffer) + 1;
        const size_t newsize = 100;
        size_t convertedChars = 0;
        wchar_t wcstring[newsize];
        mbstowcs_s(&convertedChars, wcstring, origsize, buffer, _TRUNCATE);
        char buff[255];
        int i=0;
        DWORD size;
        size = sizeof(buffer);
        GetComputerName(wcstring, &size);
//        GetUserNameA(wcstring,&size);
        while(wcstring[i]!='\0'){
            buff[i] = wcstring[i];
            //            sprintf(buff[i],"%c",peProcessEntry.szExeFile[i]);
            i++;
        }
        buff[i] = '\0';

        return buff;
        //return buff;
        //ui->computer_name->setText(buff);
}


char* userInfo::get_user_name(){
//    char UserName[UNLEN + 1];
//        unsigned long len_UserName = UNLEN + 1;
//        GetUserNameA (UserName,&len_UserName);
//        cout<< UserName;

    char buffer[MAX_COMPUTERNAME_LENGTH + 1];
    size_t origsize = strlen(buffer) + 1;
    const size_t newsize = 100;
    size_t convertedChars = 0;
    wchar_t wcstring[newsize];
    mbstowcs_s(&convertedChars, wcstring, origsize, buffer, _TRUNCATE);
    char buff[255];
    int i=0;
    DWORD size;
    size = sizeof(buffer);
    GetUserName(wcstring, &size);
    while(wcstring[i]!='\0'){
        buff[i] = wcstring[i];
        i++;
    }
    buff[i] = '\0';
    return buff;
    //ui->label_7->setText(buff);
}



void processorInfo::get_processor_type(Ui::MainWindow *ui){
    SYSTEM_INFO sys_Info;
    GetSystemInfo(&sys_Info);
    int amount = sys_Info.dwNumberOfProcessors;
    char buffer[250] ;
    itoa(amount,buffer,10);
    ui->amount_of_kernels->setText(buffer);
    //sys_Info.dwProcessorType
    int key = sys_Info.wProcessorLevel;
    switch(key){
    case 3:strcpy(buffer,"80386");
        break;
    case 4:strcpy(buffer,"80486");
        break;
    case 5:strcpy(buffer,"Pentium");
        break;
    case 6:strcpy(buffer,"Pentium Pro");
    break;
    default:
        strcpy(buffer,"Undefined");
        break;
    }
    ui->label_17->setText(buffer);


    int architecture = sys_Info.wProcessorArchitecture;
    switch(architecture){
    case 0:strcpy(buffer,"x86");break;
    case 9:strcpy(buffer,"x64 (AMD или Intel)");break;
    case 5:strcpy(buffer,"ARM");break;
    case 12:strcpy(buffer,"ARM64");break;
    case 6:strcpy(buffer,"Intel Itanium-based");break;
    }

    //itoa(architecture,buffer,10);
    ui->label_8->setText(buffer);
}

static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME & ft) { return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime); }
float GetCPULoad()
{
    FILETIME idleTime, kernelTime, userTime;
    return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
}

void processorInfo::get_processor_load(Ui::MainWindow *ui)
{
    SYSTEMTIME sysTime;
        //Retrieves data so that we have a way to Get it to output when using the pointers
    GetSystemTime(&sysTime);
    float res = GetCPULoad()*100;
//    int counter = 0;
//    while (counter < 5)
//    {
//            //Timestamp + Memory Info, and eventually CPU Load percentage
//            //myfile << sysTime.wHour << "." << sysTime.wMinute << "." << sysTime.wSecond << ", " << GetCPULoad() * 100 << "%, " << memStat.dwMemoryLoad << "%, " << memStat.ullTotalPhys / MB << ", " << memStat.ullAvailPhys / MB << ", " << memStat.ullTotalPageFile / MB << ", " << memStat.ullAvailPageFile / MB << ", " << memStat.ullTotalVirtual / MB << ", " << memStat.ullAvailVirtual / MB << ", " << memStat.ullAvailExtendedVirtual / MB << "\n";
//            //250 millisecond sleep delay
//            Sleep(200);
//            cout << GetCPULoad() * 100 << "%, " << endl;
//            Sleep(200);
//            counter = counter + 1;
//    }
    ui->progressBar->setValue(res);
}

void MainWindow::update()
{
    HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    PrintProcessList(hStdOut);
     //mem_info->get_mem_info(ui);
    mem_info->get_mem_info(ui);
    procInfo->get_processor_load(ui);
    //get_information();
}
//void MainWindow::get_process_list()
//{
//    HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    PrintProcessList(hStdOut);
//}

void MainWindow::PrintProcessList(HANDLE CONST hStdOut)
{
    PROCESSENTRY32 peProcessEntry;
    TCHAR szBuff[1024];
    char buff[255];
    DWORD dwTemp;
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return;
    }

    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);

    Process32First(hSnapshot, &peProcessEntry);
    do {
        int i=0;
        while(peProcessEntry.szExeFile[i]!='\0'){
            buff[i] = peProcessEntry.szExeFile[i];
//            sprintf(buff[i],"%c",peProcessEntry.szExeFile[i]);
            i++;
        }
        buff[i] = '\0';

        //snprintf(buff,sizeof(peProcessEntry.szExeFile),(LPSTR)peProcessEntry.szExeFile);
//        printf(L"===  %s ===\r\n",peProcessEntry.szExeFile) ;
       ui->listWidget->addItem(buff);

//       for(int i=0;buff[i]!='\0';i++){
//           buff
        //PrintModuleList(hStdOut, peProcessEntry.th32ProcessID);
    } while (Process32Next(hSnapshot, &peProcessEntry));

    CloseHandle(hSnapshot);
}

//void MainWindow::PrintModuleList(HANDLE hStdOut, DWORD dwProcessId)
//{
//    MODULEENTRY32 meModuleEntry;
//    TCHAR szBuff[1024];
//    DWORD dwTemp;
//    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(
//        TH32CS_SNAPMODULE, dwProcessId);
//    if (INVALID_HANDLE_VALUE == hSnapshot) {
//        return;
//    }

//    meModuleEntry.dwSize = sizeof(MODULEENTRY32);
//    Module32First(hSnapshot, &meModuleEntry);
//    do {
//        wsprintf(szBuff, L"  ba: %08X, bs: %08X, %s\r\n",
//            meModuleEntry.modBaseAddr, meModuleEntry.modBaseSize,
//            meModuleEntry.szModule);
//        WriteConsole(hStdOut, szBuff, lstrlen(szBuff), &dwTemp, NULL);

//    } while (Module32Next(hSnapshot, &meModuleEntry));

//    CloseHandle(hSnapshot);
//}


