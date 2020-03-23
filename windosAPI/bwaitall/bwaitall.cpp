//2	Write a program to create two threads and print the reason for WaitForMultipleObjects return.
//Print results with.
//a.bWaitAll = TRUE and timeout interval INFINITE
//b.bWaitAll = FALSE and timeout interval INFINITE, thread1 Sleep(4000) and thread2 Sleep(3000)
//c.bWaitAll = FALSE and timeout interval INFINITE, thread1 Sleep(2000) and thread2 Sleep(3000)
//d.bWaitAll = FALSE and timeout interval 2000, thread1 Sleep(4000) and thread2 Sleep(3000)


#include <iostream>
#include <Windows.h>
using namespace std;

// wait for multipleobjects 

// count
// handles array
// wait all
// time



DWORD WINAPI callback1(LPVOID ptr)
{
	int stime = *((DWORD*)ptr);
	Sleep(stime);
	cout << "thread 1 sleep for" << stime << endl;
	return 0;
}

DWORD WINAPI callback2(LPVOID ptr)
{
	int stime = *((DWORD*)ptr);
	Sleep(stime);
	cout << "thread 2 sleep for" << stime << endl;
	return 0;
}








void status(DWORD stat)
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




void createThread(BOOL waitall, DWORD time, int t1sleep, int t2sleep)
{
	HANDLE th[2];
	DWORD tid1, tid2;


	// create thread 1

	th[0] = CreateThread(
		NULL, // whether the returned handle can be inherited by the child process
		0,//  it uses default stack size
		callback1,	// call  back function(starting address)
		&t1sleep, // pointer to a  variable that is passed to thread
		0, // creation flag
		&tid1
	);


	// create thread 2

	th[1] = CreateThread(
		NULL, // whether the returned handle can be inherited by the child process
		0,//  it uses default stack size
		callback2,	// call  back function(starting address)
		&t2sleep, // pointer to a  variable that is passed to thread
		0, // creation flag
		&tid2
	);

	DWORD ret = WaitForMultipleObjects(2, th, waitall, time);
	status(ret);

	CloseHandle(th[0]);
	CloseHandle(th[1]);

	return;
}

int main()
{
	int arr[4][4] = {
		{true,INFINITE,0,0},
		{true,INFINITE,4000,3000},
		{false,INFINITE,2000,3000},
		{false,2000,4000,3000}
	};


	for (int i = 0; i < 4; i++)
	{
		createThread(arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
	}


	return 0;
}