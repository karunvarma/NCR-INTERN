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

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	BOOL created;


	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	cout << "running 1st child process" << endl;



	//2.	Write a program which uses the CreateProcess API to create two child processes(say calc.exe and notepad.exe)
	//	.Print HANDLE value and process ID of each child process.


	created = CreateProcess(
		L"C:\\Windows\\notepad.exe",
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
		cout << " process notepad failed and error no " << GetLastError() << endl;
	}
	cout << "child proces -- notepad process id " << pi.dwProcessId << endl;

	WaitForSingleObject(pi.hThread, INFINITE);
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);





	created = FALSE;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	cout << "running 2nd child process" << endl;

	created = CreateProcess(
		L"C:\\Windows\\System32\\calc.exe",
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
		cout << " process calculator failed and error no " << GetLastError() << endl;
	}
	cout << "child proces -- calculator process id " << pi.dwProcessId << endl;

	WaitForSingleObject(pi.hThread, INFINITE);
	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);




}