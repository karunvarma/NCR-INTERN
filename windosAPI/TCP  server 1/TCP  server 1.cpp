#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

#pragma comment(lib,"ws2_32.lib")
using namespace std;

//#define PORT 80



int main(const int argc,const char *argv[])
{

	string IpAddresss = "153.58.143.140"; // ip of server
	int Port= 54000;	// port of servr

	// init winsock lib

	WSADATA  WsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &WsaData) != 0)
	{
		cout << "error in initializing the socket" << endl;
		return 0;
	}

	// create a socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock ==INVALID_SOCKET)
	{
		cout << "cant create the socket! " << WSAGetLastError() << endl;
		return 0;
	}


	//define server info
	SOCKADDR_IN sin;
	ZeroMemory(&sin, sizeof(sin));

	// network byte is bigendian

	sin.sin_port = htons(Port);
	sin.sin_family = AF_INET;
	inet_pton(AF_INET, IpAddresss.c_str(), &sin.sin_addr);


	// connect to server
	int connres = connect(sock, (sockaddr*)&sin, sizeof(sin));

	if (connres == SOCKET_ERROR)
	{
		cout << "cannot connect to server " << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}


	// do-while loop to send and recieve data
	char buf[4096];
	string userInput;

	do {
		//promt the user for some text
		cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0) {
			//send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {

				//wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);

				if (bytesReceived > 0) {
					//echo response to the console
					cout << "server> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}

	} while (userInput.size() > 0);



	// close everything
	closesocket(sock);
	WSACleanup();



	
	return 0;
}