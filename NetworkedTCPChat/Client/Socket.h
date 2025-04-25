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

	void Send();

	void Receive();

private:
	SOCKET m_oSocket;

	void WSASetup();

	void RetrieveIPv4Address();

	void SetupSocket(int _iPortNumber);

	void AttemptServerConnection(int _iServerPortNumber);

	void ConnectionRetryTimer(short _siSeconds);
};