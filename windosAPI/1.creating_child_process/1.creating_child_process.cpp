// child process in linux can be created using fork


// in create process api we have to give the excutable 
// that executable acts as a child process



// create process
//1) application name
//2)(cmd line);
//3) process attribute
//4) thread attributs
//5) inherit handle(process inheriting the parent process or not)
//6) flag
//7) environment(if null the  child will take parent env)
//8) dir (if child is in diff dir and parent is in diff dir)
//9) startupinfo
//10) process info


//create process
//zero mem
//wait for single obj
//close handle


#include<Windows.h>
#include<iostream>
using namespace std;

int main()
{
	HANDLE hprocess;
	HANDLE hThread;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD ProcessId = 0;
	DWORD ThreadID = 0;
	BOOL created;


	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	cout << "running child process" << endl;


	created = CreateProcess(
		L"C:\\Users\\KD185138\\source\\repos\\NCR-INTERN\\windosAPI\\helloworld\\Debug\\helloworld.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	);

	if (created == FALSE)
	{
		cout << " process creation failed and error no" << GetLastError() << endl;
	}



	WaitForSingleObject(pi.hThread, INFINITE);
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}