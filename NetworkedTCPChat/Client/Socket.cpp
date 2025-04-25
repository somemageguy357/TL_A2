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

#include "Socket.h"
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

void CSocket::Send()
{
	unsigned int uiLineLength = -1;

	const short ksiMaxInputLength = 256;

	char cBuffer[ksiMaxInputLength];

	while (true)
	{
		std::cout << "\nEnter a message to send: ";

		std::cin.getline(cBuffer, uiLineLength);

		std::string sMessage = cBuffer; //maybe replace with char sizeof?

		if (sMessage.size() > ksiMaxInputLength)
		{
			CUtilities::Print("Sending Error: Character Limit Exceeded.", 0, 1, CUtilities::EColour::Red);
			continue;
		}

		int iSend = send(m_oSocket, cBuffer, strlen(cBuffer), 0);

		if (iSend == SOCKET_ERROR)
		{
			CUtilities::Print("Sending Error: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
			WSACleanup();
			break;
		}

		break;
	}

	Receive();
}

void CSocket::Receive()
{
	const int kiBufferSize = 257; //Has to be one more than the limit (256).
	char cBuffer[kiBufferSize];

	while (true)
	{
		int iRcv = recv(m_oSocket, cBuffer, kiBufferSize - 1, 0);

		if (iRcv == SOCKET_ERROR)
		{
			CUtilities::Print("Receiving Error: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
			continue;
		}

		cBuffer[iRcv] = '\0';
		break;
	}

	std::string sBuffer = cBuffer;

	if (sBuffer.substr(0, 7) == "Server:")
	{
		CUtilities::Print(sBuffer, 1, 1, CUtilities::EColour::Yellow);
	}

	else
	{
		CUtilities::Print(sBuffer, 1, 1, CUtilities::EColour::Cyan);
	}

	if (sBuffer != "Server: Leaving the server.")
	{
		Send();
	}
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
	//sockaddr_in oServerAddress;
	//oServerAddress.sin_family = AF_INET;
	//oServerAddress.sin_port = htons(_iServerPortNumber);

	//bool bConnected = false;
	//bool bRetry = false;
	//short siConnectionAttempts = 1;
	//short siRetryTimer = 2;

	//std::cout << "Attempting to connect to server...\n";
	//std::thread oThread;

	//InetPton(AF_INET, L"127.0.0.1", &oServerAddress.sin_addr.S_un.S_addr);

	//while (bConnected == false)
	//{
	//	if (bRetry == true)
	//	{
	//		bRetry = false;
	//		oThread = std::thread([this, siRetryTimer] { ConnectionRetryTimer(siRetryTimer); });
	//		oThread.join();
	//		//iRetryTimer += 2;
	//	}

	//	int iStatus = connect(m_oSocket, (sockaddr*)&oServerAddress, sizeof(oServerAddress));

	//	if (iStatus == SOCKET_ERROR)
	//	{
	//		std::cout << "Connection Error: " << WSAGetLastError() << ".";

	//		if (WSAGetLastError() == 10061)
	//		{
	//			std::cout << " Retrying... (Attempt " << siConnectionAttempts << ").";
	//			siConnectionAttempts += 1;
	//			bRetry = true;
	//		}

	//		std::cout << std::endl;
	//	}

	//	else
	//	{
	//		bConnected = true;
	//		WSACleanup();
	//	}
	//}

	//std::cout << "Connected.\n";

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
		CUtilities::Print("Connection Error: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
		WSACleanup();
	}

	Receive();
}

void CSocket::ConnectionRetryTimer(short _siSeconds)
{
	std::cout << "waiting\n";
	std::this_thread::sleep_for(std::chrono::seconds(_siSeconds));
}