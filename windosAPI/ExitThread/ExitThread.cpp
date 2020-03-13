#include <iostream>
#include<Windows.h>
using namespace std;


DWORD WINAPI ThreadFun(LPVOID ptr)
{
	DWORD code = *(DWORD*)ptr;
	ExitThread(code);
	for (int i = 0; i < 100; i++) cout << i << endl;
	return 0;
}


//7.	Write a program to create a secondary thread and wait in the process’s primary thread for the secondary thread to return using WaitForSingleObject.
//	Terminate secondary thread by using ExitThread API from within secondary thread.
//	Print the exit code of the secondary thread using GetExitCodeThread API in process’s primary thread.

int main()
{

	
	// thread is a indepenet entity that runs with in a process
	// 1. threads share  some resources except stack and register
	// 2. by defualt thread size in windows os is 1MB
	// 3. deleted a thread does not neccesarly remove the thread from the 
	//    operating system thread is deleted when the last handle of the thread is closedf
	HANDLE hthread;
	DWORD ThreadID;

	DWORD code;
	LPVOID VarPtr = &code;
	

	hthread = CreateThread(
		NULL, // whether the returned handle can be inherited by the child process
		0,//  it uses default stack size
		ThreadFun,	// call  back function(starting address)
		VarPtr, // pointer to a  variable that is passed to thread
		0, // creation flag
		&ThreadID
	);
	if (hthread == NULL)
	{
		cout << "thread creation is failed and error-->" << GetLastError() << endl;
	}

	

	// if function succeeds then it return non zero value
	if (GetExitCodeThread(hthread, &code) == 0){
		cout << "unable to get the exit code " << GetLastError() << endl;
	}
	else
	{
		WaitForSingleObject(hthread, INFINITE);
		cout << "throught pointer " <<*((DWORD*)VarPtr) << endl;
		cout << "exit code for the thread "<<code << endl;
		
	}
	cout << "thread id is " << ThreadID << endl;
	CloseHandle(hthread);
	return 0;
}
