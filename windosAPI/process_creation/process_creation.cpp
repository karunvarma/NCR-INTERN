// process_creation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<Windows.h>

int main()
{
    HANDLE  hProcess = NULL;
    HANDLE  hThread = NULL;
    STARTUPINFO si; // how to start the process
    PROCESS_INFORMATION pi; // process related info

  //  DWORD dwProcessId = 0;
  //  DWORD dwThreadId = 0;


    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    BOOL bcreateProcess = CreateProcess(
        L"C:\\Program Files\\Windows Media Player\\wmplayer.exe",// application name
        NULL, // command line
        NULL, // process security attriubutes
        NULL,  // thread security attributes

        FALSE, // inherit this handle
        0, // no creating flag  or to set the priority
        NULL, // environment
        NULL, // current dir
        &si, // startup information
        &pi  // process information 
    );

    if (bcreateProcess == FALSE)
    {
        std::cout << "process creation is failed" << GetLastError() << std::endl;
    }
    std::cout << "process created succesfully" << std::endl;
    std::cout << "proces id" << pi.dwProcessId << std::endl;
    std::cout << "thread id" << pi.dwThreadId << std::endl;

    std::cout << "get process id" << GetProcessId(pi.hProcess) << std::endl;
    std::cout << "get thread id" << GetThreadId(pi.hThread) << std::endl;

    WaitForSingleObject(pi.hThread, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

}

