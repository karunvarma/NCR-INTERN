#include<Windows.h> 
#include<iostream> 
using namespace std;

//
//3  Write a program to increment the value of a shared integer by two threads.
//   Print the final value of shared integer in the process’s primary thread

DWORD WINAPI CallBack(LPVOID z)
{
    (*((int*)z))++;
    return 0;
}


int main()
{

    HANDLE hThread = NULL;
    
    int shared = 0;
    cout << "before " << shared << endl;

    hThread = CreateThread(
        NULL,       //Security Attribute 
        0,          //Default Stack Size 
        CallBack, //ThreadStart Address 
        (void*)&shared,  //Parameter 
        0,         //Flags 
        0);       //ThreadID 



    if (hThread == NULL)
    {
        cout << "Thread Creation Failed" << endl;
        cout << "Error No - " << GetLastError() << endl;
    }
    else
    {
        WaitForSingleObject(hThread, INFINITE);
    }
    CloseHandle(hThread);

    cout << "after 1st thread value = " << shared << endl;


    hThread = CreateThread(
        NULL,       //Security Attribute 
        0,          //Default Stack Size 
        CallBack, //ThreadStart Address 
        (void*)&shared,  //Parameter 
        0,         //Flags 
        0);       //ThreadID 



    if (hThread == NULL)
    {
        cout << "Thread Creation Failed" << endl;
        cout << "Error No - " << GetLastError() << endl;
    }
    else
    {
        WaitForSingleObject(hThread, INFINITE);
    }
    CloseHandle(hThread);

    
    cout << "after 2nd thread value = " << shared << endl;


    return 0;
}
