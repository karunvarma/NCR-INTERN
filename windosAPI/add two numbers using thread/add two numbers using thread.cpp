#include<Windows.h> 
#include<iostream> 
using namespace std;


//5. write a program which performs addition of 2 numbers where data is taken from thread and addition is performed in the other thread.


DWORD WINAPI getNumbers(LPVOID z)
{
     
    cout << "enter 1st number" << endl;
    cin >> ((int*)z)[0];
    cout << "enter 2nd number" << endl;
    cin >> ((int*)z)[1];
    return 0;
}

DWORD WINAPI Add(LPVOID z)
{
    cout << "result" << endl;
    cout << ((int*)z)[0] + ((int*)z)[1] << endl;
    return 0;
}

int main()
{
    
    HANDLE hThread = NULL;
    int a[2];//Array 
    //STEP-1 – CreateThread Function for Thread 



    hThread = CreateThread(
        NULL,       //Security Attribute 
        0,          //Default Stack Size 
        getNumbers, //ThreadStart Address 
        (void*)&a,  //Parameter 
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



    hThread = CreateThread(
            NULL,       //Security Attribute 
            0,          //Default Stack Size 
            Add, //ThreadStart Address 
            (void*)&a,  //Parameter 
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




    return 0;
}
