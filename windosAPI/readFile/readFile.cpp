// createFile() api.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include<Windows.h>
using namespace std;

#define BUFFERSIZE 100




int main()
{
    HANDLE hFile;
    hFile = 
        CreateFile(L"C:\\Users\\KD185138\\source\\repos\\NCR-INTERN\\windosAPI\\readFile\\test.txt", //name of the file which need to be accessed
        GENERIC_READ,//type of access required on the file wether read or write or anyone
        0,//shared mode if 0 indicates that the file cannot be accessed by other process
        NULL,//security attribute indicates that it cannot be inherited if the value is NULL
        OPEN_EXISTING,//the indicator to tell wether a new file is to be created or an existing file need to be opened
        FILE_ATTRIBUTE_NORMAL,//flag
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        cout << "file hander cannot be created " << GetLastError() << endl;
    }
    else
    {
        WCHAR OutBuffer[BUFFERSIZE];
        DWORD noofbytesread = 0;
        ZeroMemory(OutBuffer, BUFFERSIZE);
        BOOL status = 0;
        status = ReadFile(hFile,
            OutBuffer,
            BUFFERSIZE,
            &noofbytesread,
            NULL);

        if (status == 1)
        {
            wcout << OutBuffer << endl;
        }
        else
        {
            cout << "error while reading the file" << endl;
        }

    }
    CloseHandle(hFile);
    return 0;
}

