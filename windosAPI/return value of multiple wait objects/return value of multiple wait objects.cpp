//1	Write a program to create a thread and print the reason for WaitForSingleObject return.Print results with.
//a.timeout interval INFINITE
//b.timeout interval 1000
//c.timeout interval 1000 with Sleep(2000) inside thread


#include <iostream>
#include <Windows.h>
using namespace std;



DWORD WINAPI timeout1(LPVOID ptr)
{
	return 0;
}

DWORD WINAPI timeout2(LPVOID ptr)
{
	return 0;
}
DWORD WINAPI timeout3(LPVOID ptr)
{
	Sleep(2000);
	return 0;
}

void check(DWORD stat)
{
	if (stat == WAIT_OBJECT_0)
	{
		cout << "success" << endl;
	}
	else if (stat == WAIT_TIMEOUT)
	{
		cout << "time out" << endl;
	}
}

int main()
{

	HANDLE hthread;
	DWORD ThreadID;

	LPVOID VarPtr = NULL;

	hthread = CreateThread(
		NULL, // whether the returned handle can be inherited by the child process
		0,//  it uses default stack size
		timeout1,	// call  back function(starting address)
		VarPtr, // pointer to a  variable that is passed to thread
		0, // creation flag
		&ThreadID
	);


	if (hthread == NULL)
	{
		cout << "thread creation is failed and error-->" << GetLastError() << endl;
	}

	DWORD ret;
	ret=WaitForSingleObject(hthread, INFINITE);
	check(ret);
	cout << "thread 1 id is " << ThreadID << endl;
	CloseHandle(hthread);



	hthread = CreateThread(
		NULL, // whether the returned handle can be inherited by the child process
		0,//  it uses default stack size
		timeout2,	// call  back function(starting address)
		VarPtr, // pointer to a  variable that is passed to thread
		0, // creation flag
		&ThreadID
	);


	if (hthread == NULL)
	{
		cout << "thread creation is failed and error-->" << GetLastError() << endl;
	}


	ret = WaitForSingleObject(hthread, 1000);
	check(ret);
	cout << "thread 2 id is " << ThreadID << endl;
	CloseHandle(hthread);



	hthread = CreateThread(
		NULL, // whether the returned handle can be inherited by the child process
		0,//  it uses default stack size
		timeout3,	// call  back function(starting address)
		VarPtr, // pointer to a  variable that is passed to thread
		0, // creation flag
		&ThreadID
	);


	if (hthread == NULL)
	{
		cout << "thread creation is failed and error-->" << GetLastError() << endl;
	}

	
	ret = WaitForSingleObject(hthread, 1000);
	check(ret);
	cout << "thread  3 id is " << ThreadID << endl;
	CloseHandle(hthread); 



}

