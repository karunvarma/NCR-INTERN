#include<Windows.h>
#include<iostream>
using namespace std;

int main()
{

	SECURITY_ATTRIBUTES Attr;
	Attr.nLength = sizeof(Attr);
	Attr.lpSecurityDescriptor = NULL;
	Attr.bInheritHandle = TRUE;

	HANDLE hFile;
	hFile =
		CreateFile(L"C:\\Users\\KD185138\\source\\repos\\NCR-INTERN\\windosAPI\\readFile\\test.txt", //name of the file which need to be accessed
			GENERIC_READ,//access mode to open file whether in read or write or anyone
			0,//shared mode if 0 indicates that the file cannot be accessed by other process

			/*If this parameter is NULL, the handle returned by CreateFile cannot be inherited by any child processes*/
			&Attr,//security attribute indicates that it cannot be inherited if the value is NULL

			OPEN_EXISTING,//the indicator to tell wether a new file is to be created or an existing file need to be opened
			FILE_ATTRIBUTE_NORMAL,//flag
			NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "file hander cannot be created " << GetLastError() << endl;
	}

	else
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(STARTUPINFO));
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

		BOOL status = 0;
		status = CreateProcess(
			L"C:\\Users\\KD185138\\source\\repos\\NCR-INTERN\\windosAPI\\helloworld\\Debug\\helloworld.exe",
			NULL, 

			
			/*A pointer to a SECURITY_ATTRIBUTES structure that determines whether the returned handle
			to the new process object can be inherited by child processes.
			If lpProcessAttributes is NULL, the handle cannot be inherited.*/
			&Attr, 
			NULL,  // thread security attributes

			/*If this parameter is TRUE, each inheritable handle in the calling process
			is inherited by the new process.
			If the parameter is FALSE, the handles are not inherited.*/
			TRUE,
			0,  // priority
			NULL,
			NULL,
			&si,
			&pi);
		if (status == 0)
		{
			cout << "creation of process is failed " << GetLastError() << endl;
		}
		else
		{
			cout << "creation of process succedded" << endl;
			cout << "process id " << pi.dwProcessId << endl;
		}
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
	}


}