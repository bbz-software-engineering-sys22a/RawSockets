// SES6-02a-RAWSocket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main()
{
	int iResult;

	//Erstellen eines WSADATA Objekts, wird ben�tigt f�r das Initialisieren des Sockets durch WSAStartup()
	WSADATA wsaData;
	//Erstellen eines SOCKET Objekts, wird ben�tigt f�r das Erstellen eines Sockets durch socket()
	SOCKET rawSocket;
	//Daten die wir versenden wollen
	string data = "Nachricht";

	//struct in denen wir die Informationen des Ziel Servers speichern
	struct sockaddr_in destinationAddress;
	destinationAddress.sin_family = AF_INET;
	destinationAddress.sin_addr.s_addr = inet_addr("2.2.2.2");


	//Code Block 1
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup fehlgeschlagen: " << iResult << endl;
		system("pause");
		return 1;
	}

	//Code Block 2
	if ((rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == SOCKET_ERROR) {
		cout << "Socket konnte nicht erstellt werden: " << WSAGetLastError() << endl;
		system("pause");
		return 1;
	}

	//Code Block 3
	while (true) {
		sendto(rawSocket, data.c_str(), strlen(data.c_str()), 0, (SOCKADDR*)&destinationAddress, sizeof(destinationAddress));
		cout << "Packet versendet" << endl;
	}
	WSACleanup();

	system("pause");
	return 0;
}

