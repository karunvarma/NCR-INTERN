#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib,"ws2_32.lib")

using namespace std;


int main()
{

	// initialize winsock

	WSADATA WsData;
	WORD ver = MAKEWORD(2, 2);

	int WsOk = WSAStartup(ver, &WsData);

	if (WsOk != 0)
	{
		cout << "error in  initializing winsock " << endl;
		return 0;
	}

	cout << "init winsock completed" << endl;

	// create a socket

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET)
	{
		cout << "cant create the socket! " << endl;
		return 0;
	}

	cout << "socket created for listening" << endl;
	// N/w big end 
	// PC little end

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;


	// bind the socket to ip address and port to a socket
	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// tell the winsock it is for listening
	listen(listening, SOMAXCONN);


	// wait for connection

	sockaddr_in client;
	int ClientSize = sizeof(client);

	SOCKET ClientSocket = accept(listening, (sockaddr*)&client, &ClientSize);

	char host[NI_MAXHOST];	// client remote name
	char service[NI_MAXHOST];  // service (port) the client is connected to

	ZeroMemory(host ,NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	}

	// close listening socket
	closesocket(listening);

	cout << "waiting for data " << endl;

	// while loop: accept and send message back to client
	char buff[4096];

	while (true)
	{
		ZeroMemory(buff, 4096);
		string userInput;


		//wait for client to send data
		int BytesReceived = recv(ClientSocket, buff, 4096, 0);
		if (BytesReceived == SOCKET_ERROR)
		{
			cout << "error in recv() quitting " << endl;
			break;
		}

		if (BytesReceived == 0)
		{
			cout << "client disconneted " << endl;
			break;
		}

		cout << "Client>" << buff << endl;

		/*cout << "msg " << endl;
		cout << buff << endl;*/
		cout << ">";
		getline(cin, userInput);


		// echo msg back to client
		send(ClientSocket, userInput.c_str, userInput.size() + 1, 0);

	}


	//close the sock

	closesocket(ClientSocket);

	// shutdown the winsock
	WSACleanup();


		return 0;

}

