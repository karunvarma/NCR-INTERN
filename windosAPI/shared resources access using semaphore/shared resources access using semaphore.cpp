//Write a program where only 2 out of 4 threads at a time are allowed to access shared resources.
//Use semaphore object to count the no of allowed threads to access shared resources.
//Use the shared resource for 200 ms with Sleep(200).
//Use WaitForSingleObject to get the ownership of semaphore object


#include<Windows.h> 
#include<iostream> 
using namespace std;


HANDLE semaphore;


DWORD WINAPI CallBack(LPVOID z)
{

	DWORD res=WaitForSingleObject(semaphore, INFINITE);
	return 0;
}





int main()
{
	
	HANDLE Handles[4];


	semaphore = CreateSemaphore(
		NULL, // security attributes
		1, // initial state
		2, // maximum resources
		NULL
	);


	if (semaphore == NULL) {
		cout << "CreateSemaphore error: " << GetLastError() << endl;
		return 0;
	}

	//creating 4 threads
	for (int i = 0; i < 4; i++) {
		Handles[i] = CreateThread(
			NULL,
			0,
			CallBack,
			NULL,
			0,
			0
		);

		if (Handles[i] == NULL) {
			cout << "Create thread error: " << GetLastError() << endl;
			return 0;
		}
	}

	WaitForMultipleObjects(4, Handles, TRUE, INFINITE);

	for (int i = 0; i < 4; i++) {
		CloseHandle(Handles[i]);
	}

	CloseHandle(semaphore);

	return  0;
}