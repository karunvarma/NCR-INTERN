#include <iostream>
#include<Windows.h>

using namespace std;

DWORD WINAPI ThreadFun(LPVOID ptr)
{
	for (int i = 1; i <= 1000; i++) cout << i << endl;
	return 0;
}


//6.	Write a program to create a thread in suspended state.
//	Resume the thread after 5 seconds wait.
//	The thread should print integers from 1 to 1000 and return normally.
//	Use getchar() in process’s primary thread to wait for user input and allow time for thread to return.

int main()
{

	// thread is a indepenet entity that runs with in a process
	// 1. threads share  some resources except stack and register
	// 2. by defualt thread size in windows os is 1MB
	// 3. deleted a thread does not neccesarly remove the thread from the 
	//    operating system thread is deleted when the last handle of the thread is closedf
	char wait;
	wait = getchar();
	HANDLE hthread;
	DWORD ThreadID;

	LPVOID VarPtr = NULL;

	hthread = CreateThread(
		NULL, // whether the returned handle can be inherited by the child process
		0,//  it uses default stack size
		ThreadFun,	// call  back function(starting address)
		VarPtr, // pointer to a  variable that is passed to thread
		CREATE_SUSPENDED, // it does not run
		&ThreadID
	);


	if (hthread == NULL)
	{
		cout << "thread creation is failed and error-->" << GetLastError() << endl;
	}

	Sleep(5000);
	// running the  after 5 sec thread
	ResumeThread(hthread);
	WaitForSingleObject(hthread, INFINITE);

	//cout << "thread id is " << ThreadID << endl;
	CloseHandle(hthread);
	return 0;
}