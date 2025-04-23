#pragma once
#define NOMINMAX
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

	void SendRequest();

private:
	SOCKET m_oSocket;

	std::string m_sIPv4;

	void WSASetup();

	void RetrieveIPv4Address();

	void SetupSocket(int _iPortNumber);

	void AttemptServerConnection(int _iServerPortNumber);

	void ConnectionRetryTimer(short _siSeconds);
};