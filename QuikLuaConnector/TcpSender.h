#pragma once
class TcpSender
{
public:
	TcpSender(int port);
	~TcpSender();
	int Connect();
	int Disconnect();
	int Send(const char* message);
private:
	int _port;

};

