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

	void Send();

	void Receive();

private:
	SOCKET m_oSocket;
	SOCKET m_oServerSocket;

	sockaddr_in m_oServerAddress;

	std::string m_sIPv4;

	void WSASetup();

	void RetrieveIPv4Address();

	void SetupSocket(int _iPortNumber);

	void AttemptServerConnection(int _iServerPortNumber);

	void ConnectionRetryTimer(short _siSeconds);
};