#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "TcpListener.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <strsafe.h>
using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27014"

SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;
char bufSize[4];


TcpListener::TcpListener(int port)
{
}

TcpListener::~TcpListener()
{
}

int TcpListener::StartServer()
{
	WSADATA wsaData;
	int iResult;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

}

const char* TcpListener::Listen()
{
	int iResult;

		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return "";
		}

		// No longer need server socket
		//closesocket(ListenSocket);

		// Receive until the peer shuts down the connection

		//receive message size
		iResult = recv(ClientSocket, bufSize, 4, 0);
		if (iResult > 0) {

			int nSize = (unsigned int&)bufSize;
			cout << "Number: " << (unsigned int)nSize << endl;

			char *recvbuf = new char[nSize];

			//recive message
			iResult = recv(ClientSocket, recvbuf, nSize, 0);
			if (iResult > 0) {

				//std::string str(recvbuf, nSize);
				//printf("Recived: %s\n", str);
				cout << "Recived: " << recvbuf << endl;

				return recvbuf;
				//// Echo the buffer back to the sender
				//iSendResult = send(ClientSocket, recvbuf, iResult, 0);
				//if (iSendResult == SOCKET_ERROR) {
				//	printf("send failed with error: %d\n", WSAGetLastError());
				//	closesocket(ClientSocket);
				//	WSACleanup();
				//	return "";
				//}
				//printf("Bytes sent: %d\n", iSendResult);
			}
			else {
				printf("recv failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return "";
			}

			delete[] recvbuf;

		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return "";
		}

		// shutdown the connection since we're done
		iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return "";
		}

		return 0;
}

void TcpListener::StopServer()
{
	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

}