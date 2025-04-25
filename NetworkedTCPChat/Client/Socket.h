/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Socket.h
Description : 
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

class CSocket
{
public:
	CSocket() = delete;

	/// <summary>
	/// Starts the setup process for the socket.
	/// </summary>
	/// <param name="_iPortNumber:">The port number of the socket.</param>
	/// <param name="_iServerPortNumber:">The port number of the server's socket.</param>
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