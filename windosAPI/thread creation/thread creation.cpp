#include <iostream>
#include<Windows.h>

using namespace std;

DWORD WINAPI ThreadFun(LPVOID ptr)
{
	for (int i = 0; i < 10; i++) cout << i << endl;
	return 0;
}

int main()
{
	
	cout << "hello world" << endl;
	// thread is a indepenet entity that runs with in a process
	// 1. threads share  some resources except stack and register
	// 2. by defualt thread size in windows os is 1MB
	// 3. deleted a thread does not neccesarly remove the thread from the 
	//    operating system thread is deleted when the last handle of the thread is closedf
	HANDLE hthread;
	DWORD ThreadID;

	LPVOID VarPtr = NULL;

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

	WaitForSingleObject(hthread, INFINITE);

	cout << "thread id is " << ThreadID << endl;
	CloseHandle(hthread);
	return 0;
}
