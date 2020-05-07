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
    get_information();
    //mt->
}

/*void MainWindow :: full_table(){
    ui->tabWidget->clear();
    ui->tab_2->
}*/

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


//            std::wcout << szDisk << std::endl;

//            std::wcout << L"Системные флаги диска:\t";
//            DWORD dwSystemFlags;
//            GetVolumeInformation(szDisk, NULL, 0, NULL, 0, &dwSystemFlags, NULL, 0);
//            std::wcout << dwSystemFlags << L"\n";

            __int64 uliTotalBytes;
            GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&uliTotalBytes, NULL);
            int res = uliTotalBytes/ (1024 * 1024 * 1024);
            _itoa(res,buf,10);

            switch(counter){
            case 0:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser->setText(buff);
                break;
            case 1:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_2->setText(buff);
                break;
            case 2:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_3->setText(buff);
                break;
            case 3:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_4->setText(buff);
                break;
            case 4:
                strcat(buff,"\nОбъем диска: ");
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_5->setText(buff);
                break;
            case 5:
                strcat(buff,"\nОбъем диска:");
                strcat(buff,buf);
                strcat(buff," ГБ");
                ui->textBrowser_6->setText(buff);
                break;
            }
//            std::wcout << L"Объем диска:\t" << uliTotalBytes / (1024 * 1024 * 1024) << L" МБ\n";
//            std::wcout << std::endl;
        //}
        while (*szLogicalDrives) szLogicalDrives++;
        szLogicalDrives++;
        counter++;
   }



//    char buff[100];
//    wchar_t buffer[100];
//    if (GetDriveType(L"F:")==DRIVE_CDROM)
//            cout << "CD" << endl;//GetDriveType(buffer);
//    int i=0;
//    while(buffer[i]!='\0'){
//        buff[i] = buffer[i];
////            sprintf(buff[i],"%c",peProcessEntry.szExeFile[i]);
//        i++;
//    }
//    buff[i] = '\0';

//    ui->label_8->setText(buff);
}

void MainWindow::get_information()
{
    compInfo->get_computer_name(ui);
    user_info->get_user_name(ui);
    procInfo->get_processor_type(ui);
    //os_info->get_os_version_name(ui);
    os_info->get_windows_directory(ui);
    drive_info->get_drive_type(ui);
    //drive_info->get_pass_volumes(ui);
    //drive_info->get_free_space(ui);
    mem_info->get_mem_info(ui);
   disp_info->get_display_info(ui);
}

void driveInfo:: get_free_space(Ui::MainWindow *ui){
        DWORD FreeBytesAvailable;
        DWORD TotalNumberOfBytes;
        DWORD TotalNumberOfFreeBytes;

        BOOL GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx(
        L"c:\\",					  // directory name
        (PULARGE_INTEGER)&FreeBytesAvailable,     // bytes available to caller
        (PULARGE_INTEGER)&TotalNumberOfBytes,     // bytes on disk
        (PULARGE_INTEGER)&TotalNumberOfFreeBytes  // free bytes on disk
        );

        if(GetDiskFreeSpaceFlag != 0)
        {
            cout << "	Total Number Of Free Bytes = " << TotalNumberOfFreeBytes << "( " <<  double(long (TotalNumberOfFreeBytes))/1024/1000
                 << " Mb )" << endl;
            cout << "	Total Number Of Bytes = " << TotalNumberOfBytes  << "( " << double(long (TotalNumberOfBytes))/1024/1000
                 << " Mb )" << endl;
        }
        else	cout << "	Not Present (GetDiskFreeSpace)" << endl;

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

    setlocale(LC_ALL, "");
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

        //printf("Adapter %s", sDispDev.DeviceString);
    }
    else
    {
        cout << "Не удалось найти информацию об адаптере!" << endl;
        system("\npause");
        exit(EXIT_FAILURE);
    }
//    if (EnumDisplayDevices(NULL, 0, &sDispDev, 0))
//    {
//        int i = 0;
//        while(sDispDev.DeviceString[i]!='\0'){
//            buf[i] = sDispDev.DeviceString[i];
//            i++;
//        }
//        buf[i]='\0';
//        ui->label_21->setText(buf);
//        //printf("Adapter %s", sDispDev.DeviceString);
//    }

    std::wstring devName = sDispDev.DeviceName;

    if (EnumDisplayDevices(devName.c_str(), 0, &sDispDev, 0))
    {
        int i = 0;
        while(sDispDev.DeviceName[i]!='\0'){
            buf[i] = sDispDev.DeviceName[i];
            i++;
        }
        buf[i]='\0';
        ui->label_22->setText(buf);
        //printf("Name %s", sDispDev.DeviceName);
    }
    else
    {
        cout << "Не удалось найти информацию о дисплее!" << endl;
        system("\npause");
    }



//    char buffer[250];
//    DISPLAY_DEVICE  display_device;
//    ZeroMemory(&display_device, sizeof(display_device));
//    display_device.cb = sizeof(display_device);
//    for(int i = 0; EnumDisplayDevices(NULL, i, &display_device, 0); ++i){
//        cout<<display_device.DeviceName;
//    }
////    void GetVideoInfo()
////    {
//        setlocale(LC_ALL, "");
//        DISPLAY_DEVICE sDispDev = { 0 };
//        sDispDev.cb = sizeof(DISPLAY_DEVICE);
//        if (EnumDisplayDevices(NULL, 0, &sDispDev, 0))
//        {
//            cout << "Адаптер: " << sDispDev.DeviceString << endl;
//        }
//        else
//        {
//            cout << "Не удалось найти информацию об адаптере!" << endl;
//            system("\npause");
//            exit(EXIT_FAILURE);
//        }
//        if (EnumDisplayDevices(NULL, 0, &sDispDev, 0))
//        {
//            cout << sDispDev.DeviceString << endl;
//        }

//        std::wstring devName = sDispDev.DeviceName;

//        if (EnumDisplayDevices(devName.c_str(), 0, &sDispDev, 0))
//        {
//            cout << sDispDev.DeviceName << endl;
//        }
//        else
//        {
//            cout << "Не удалось найти информацию о дисплее!" << endl;
//            system("\npause");
//        }
////    }

}

void driveInfo::get_pass_volumes(Ui::MainWindow *ui){

        DWORD  CharCount            = 0;
        WCHAR  DeviceName[MAX_PATH] = L"";
        DWORD  Error                = ERROR_SUCCESS;
        HANDLE FindHandle           = INVALID_HANDLE_VALUE;
        BOOL   Found                = FALSE;
        size_t Index                = 0;
        BOOL   Success              = FALSE;
        WCHAR  VolumeName[MAX_PATH] = L"";

        //
        //  Enumerate all volumes in the system.
        FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));

        if (FindHandle == INVALID_HANDLE_VALUE)
        {
            Error = GetLastError();
            wprintf(L"FindFirstVolumeW failed with error code %d\n", Error);
            return;
        }

        for (;;)
        {
            //
            //  Skip the \\?\ prefix and remove the trailing backslash.
            Index = wcslen(VolumeName) - 1;

            if (VolumeName[0]     != L'\\' ||
                VolumeName[1]     != L'\\' ||
                VolumeName[2]     != L'?'  ||
                VolumeName[3]     != L'\\' ||
                VolumeName[Index] != L'\\')
            {
                Error = ERROR_BAD_PATHNAME;
                wprintf(L"FindFirstVolumeW/FindNextVolumeW returned a bad path: %s\n", VolumeName);
                break;
            }

            //
            //  QueryDosDeviceW does not allow a trailing backslash,
            //  so temporarily remove it.
            VolumeName[Index] = L'\0';

            CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));

            VolumeName[Index] = L'\\';

            if ( CharCount == 0 )
            {
                Error = GetLastError();
                wprintf(L"QueryDosDeviceW failed with error code %d\n", Error);
                break;
            }

            wprintf(L"\nFound a device:\n %s", DeviceName);

            //ui->textBrowser->setText(L DeviceName);
            wprintf(L"\nVolume name: %s", VolumeName);
            wprintf(L"\nPaths:");
//            DisplayVolumePaths(VolumeName);
            DWORD  CharCount = MAX_PATH + 1;
            PWCHAR Names     = NULL;
            PWCHAR NameIdx   = NULL;
            BOOL   Success   = FALSE;

            for (;;)
            {
                //
                //  Allocate a buffer to hold the paths.
                Names = (PWCHAR) new BYTE [CharCount * sizeof(WCHAR)];

                if ( !Names )
                {
                    //
                    //  If memory can't be allocated, return.
                    return;
                }

                //
                //  Obtain all of the paths
                //  for this volume.
                Success = GetVolumePathNamesForVolumeNameW(
                    VolumeName, Names, CharCount, &CharCount
                    );

                if ( Success )
                {
                    break;
                }

                if ( GetLastError() != ERROR_MORE_DATA )
                {
                    break;
                }

                //
                //  Try again with the
                //  new suggested size.
                delete [] Names;
                Names = NULL;
            }

            if ( Success )
            {
                //
                //  Display the various paths.
                for ( NameIdx = Names;
                      NameIdx[0] != L'\0';
                      NameIdx += wcslen(NameIdx) + 1 )
                {
                    wprintf(L"  %s", NameIdx);
                }
                wprintf(L"\n");
            }

            if ( Names != NULL )
            {
                delete [] Names;
                Names = NULL;
            }

            //
            //  Move on to the next volume.
            Success = FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));

            if ( !Success )
            {
                Error = GetLastError();

                if (Error != ERROR_NO_MORE_FILES)
                {
                    wprintf(L"FindNextVolumeW failed with error code %d\n", Error);
                    break;
                }

                //
                //  Finished iterating
                //  through all the volumes.
                Error = ERROR_SUCCESS;
                break;
            }
        }

        FindVolumeClose(FindHandle);
        FindHandle = INVALID_HANDLE_VALUE;

        return;
}

void memoryInfo::get_mem_info(Ui::MainWindow *ui){//+
    MEMORYSTATUSEX statex;
    char buf[250];
    statex.dwLength = sizeof (statex);

    GlobalMemoryStatusEx (&statex);
    int percent = statex.dwMemoryLoad;
    _itoa(percent,buf,10);
     strcat(buf,"%");
//    while(statex.dwMemoryLoad[i]!='\0'){
//        buff[i] = peProcessEntry.szExeFile[i];
//        //            sprintf(buff[i],"%c",peProcessEntry.szExeFile[i]);
//        i++;
//    }
//    buff[i] = '\0';
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

//void MainWindow::

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

}

void osInfo:: get_os_version_name(Ui::MainWindow *ui){//???


    if(IsWindows10OrGreater()){
        ui->OS->setText("Windows 10");
    }
    if (IsWindows8Point1OrGreater())
    {
        ui->OS->setText("Windows 8.1");
    }
    if (IsWindows8OrGreater())
    {
        ui->OS->setText("Windows 8");
    }
    if (IsWindows7OrGreater())
    {
        ui->OS->setText("Windows 7");
    }
    if (IsWindowsVistaOrGreater())
    {
        ui->OS->setText("Windows Vista");
    }
    if (IsWindowsXPOrGreater())
    {
        ui->OS->setText("Windows XP");
    }
    ui->OS->setText("Windows Unknown");
}
//void MainWindow:: full_table()
//{

//    SYSTEM_INFO sys_Info;

//       GetSystemInfo(&sys_Info);

//      /* unsigned char bytes[sizeof(DWORD)];
//       DWORD val = -1;
//       std::memcpy(bytes, &val, sizeof bytes);
//        for (const auto it : bytes)
//             std::cout << static_cast<int>(it) << ' ';*/
//       if(sys_Info.dwProcessorType == 586){

//           ui->listWidget->addItem("Pentium");
//       }
//      /* cout << "Your process type : " << sys_Info.dwProcessorType << endl;

//       cout << "Amount of kernel : " << sys_Info.dwNumberOfProcessors << endl;*/
//       //DWORD str = sys_Info.dwProcessorType;



//}

void computerInfo::get_computer_name(Ui::MainWindow *ui){

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
        ui->computer_name->setText(buff);
}


void userInfo::get_user_name(Ui::MainWindow *ui){
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
    ui->label_7->setText(buff);
}

void processorInfo::get_processor_type(Ui::MainWindow *ui){
    SYSTEM_INFO sys_Info;
    GetSystemInfo(&sys_Info);
    int amount = sys_Info.dwNumberOfProcessors;
    char buffer[250] ;
    itoa(amount,buffer,10);
    ui->amount_of_kernels->setText(buffer);

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
    if(architecture == 0){
        strcpy(buffer,"x86");
    }
    //itoa(architecture,buffer,10);
    ui->label_8->setText(buffer);



//    const int DelayTime = 500;
//    DWORD TimerHi,TimerLo;
//    int PriorityClass,Priority;
////    var TimerHi : DWORD;
////         TimerLo : DWORD;
////         PriorityClass : Integer;
////         Priority : Integer;
//      PriorityClass = GetPriorityClass(GetCurrentProcess);
//      Priority = GetThreadPriority(GetCurrentThread);
//      SetPriorityClass(GetCurrentProcess, REALTIME_PRIORITY_CLASS);
//      SetThreadPriority(GetCurrentThread, THREAD_PRIORITY_TIME_CRITICAL);
//      Sleep(10);
//      _asm {
//        DW 310Fh // rdtsc
//        MOV TimerLo, EAX
//        MOV TimerHi, EDX
//      }
//      Sleep(DelayTime);
//      _asm {
//        //DW 310Fh // rdtsc
//        SUB EAX, TimerLo
//        SBB EDX, TimerHi
//        MOV TimerLo, EAX
//        MOV TimerHi, EDX
//      }
//      SetThreadPriority(GetCurrentThread, Priority);
//      SetPriorityClass(GetCurrentProcess, PriorityClass);
//      int lol = TimerLo / (1000.0 * DelayTime);
//     // printf("%d",TimerLo / (1000.0 * DelayTime));

}

void MainWindow::update()
{
    HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    PrintProcessList(hStdOut);
    mem_info->get_mem_info(ui);
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
//        int wchars_num =  MultiByteToWideChar( CP_UTF8 , 0 , x.c_str() , -1, NULL , 0 );
//        wchar_t* wstr = new wchar_t[wchars_num];
//        MultiByteToWideChar( CP_UTF8 , 0 , x.c_str() , -1, wstr , wchars_num );
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


