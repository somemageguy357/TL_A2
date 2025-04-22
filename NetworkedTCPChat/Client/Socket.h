#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

class CSocket
{
public:
	CSocket() = delete;
	CSocket(int _iPortNumber, int _iServerPortNumber);
	~CSocket();

	std::string GetIPv4Address();

private:
	SOCKET m_oSocket;

	std::string m_sIPv4;
};