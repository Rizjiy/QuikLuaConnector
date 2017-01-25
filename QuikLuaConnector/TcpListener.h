#pragma once

#include <string>

using namespace std;

class TcpListener
{
public:
	TcpListener(int port);
	~TcpListener();
	int StartServer();
	const char* Listen();
	void StopServer();
};

