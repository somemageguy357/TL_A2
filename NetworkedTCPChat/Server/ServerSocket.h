#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

#include "Commands.h"

class CServerSocket
{
public:
	CServerSocket() = delete;
	CServerSocket(int _iPortNumber);
	~CServerSocket();

	void Receive();

private:
	SOCKET m_oServerSocket;
	SOCKET m_oClientSocket;

	std::string m_sSavedMessage = "";

	int m_iClientCount = 0;

	void WSASetup();

	void SetupSocket(int _iPortNumber);
	
	void Listen();

	void Accept();

	void Send(std::string _sMessage);
};