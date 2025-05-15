/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Socket.cpp
Description : Contains function definitions for Socket.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "ClientSocket.h"
#include <thread>
#include <chrono>

#include "ClientUtilities.h"

CSocket::CSocket(int _iPortNumber, int _iServerPortNumber)
{
	WSASetup();
	RetrieveIPv4Address();
	SetupSocket(_iPortNumber);
	AttemptServerConnection(_iServerPortNumber);
}

CSocket::~CSocket()
{
	closesocket(m_oSocket);
}

SOCKET* CSocket::GetSocket()
{
	return &m_oSocket;
}

void CSocket::SetHasQuit(bool _bHasQuit)
{
	m_bHasQuit = _bHasQuit;
}

bool CSocket::GetHasQuit()
{
	return m_bHasQuit;
}

void CSocket::WSASetup()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);

	int iResult = WSAStartup(wVersionRequested, &wsaData);

	if (iResult != 0)
	{
		CUtilities::Print("WSAStartUp failed. Result: " + std::to_string(iResult) + ".", 0, 1, CUtilities::EColour::Red);
		WSACleanup();
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		CUtilities::Print("WSAStartUp failed. Version not available.", 0, 1, CUtilities::EColour::Red);
		WSACleanup();
	}
}

void CSocket::RetrieveIPv4Address()
{
	PCSTR sHostName = "";
	addrinfo* poAddressInfo = nullptr;

	if (getaddrinfo(sHostName, NULL, 0, &poAddressInfo) != 0)
	{
		CUtilities::Print("Name Error: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
		WSACleanup();
	}

	for (addrinfo* poAI = poAddressInfo; poAI != NULL; poAI = poAI->ai_next)
	{
		if (poAI->ai_family != AF_INET)
		{
			continue;
		}

		char cBuffer[256];
		sockaddr_in* poAddIn = (sockaddr_in*)poAI->ai_addr;
		inet_ntop(AF_INET, &poAddIn->sin_addr, cBuffer, 256);
		CUtilities::Print("IP Address: " + (std::string)cBuffer, 0, 1);
		//std::cout << "IP Address: " << cBuffer << std::endl;
	}
}

void CSocket::SetupSocket(int _iPortNumber)
{
	m_oSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_oSocket == INVALID_SOCKET)
	{
		CUtilities::Print("Invalid Socket: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
		WSACleanup();
	}

	sockaddr_in oSocketAddress;
	oSocketAddress.sin_family = AF_INET;
	oSocketAddress.sin_port = htons(_iPortNumber);
	oSocketAddress.sin_addr.S_un.S_addr = INADDR_ANY;

	int iStatus = bind(m_oSocket, (sockaddr*)&oSocketAddress, sizeof(oSocketAddress));

	if (iStatus == SOCKET_ERROR)
	{
		CUtilities::Print("Client Bind Error: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
		WSACleanup();
	}
}

void CSocket::AttemptServerConnection(int _iServerPortNumber)
{
	CUtilities::Print("Connecting to server...", 0, 1);

	if (m_oSocket == INVALID_SOCKET)
	{
		CUtilities::Print("Invalid Server Socket: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
		WSACleanup();
	}

	sockaddr_in oServerAddress;
	oServerAddress.sin_family = AF_INET;
	oServerAddress.sin_port = htons(_iServerPortNumber);

	InetPton(AF_INET, L"127.0.0.1", &oServerAddress.sin_addr.S_un.S_addr);

	int iStatus = connect(m_oSocket, (sockaddr*)&oServerAddress, sizeof(oServerAddress));

	if (iStatus == SOCKET_ERROR)
	{
		if (WSAGetLastError() == 10061)
		{
			CUtilities::Print("Connection Error: " + std::to_string(WSAGetLastError()) + ": Connection Refused. Attempting another connection...", 0, 1, CUtilities::EColour::Red);
			AttemptServerConnection(_iServerPortNumber); //Re-attempt connection.
		}

		else
		{
			CUtilities::Print("Connection Error: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
			WSACleanup();
		}
	}
}