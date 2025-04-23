#include "Socket.h"
#include <thread>
#include <chrono>

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

std::string CSocket::GetIPv4Address()
{
	return m_sIPv4;
}

void CSocket::SendRequest()
{
	unsigned int uiLineLength = -1;

	const short ksiMaxInputLength = 256;

	char cBuffer[ksiMaxInputLength];

	while (true)
	{
		std::cout << "Enter a message to send:\n";

		std::cin.getline(cBuffer, uiLineLength);

		std::string sMessage = cBuffer;

		if (sMessage.size() > ksiMaxInputLength)
		{
			std::cout << "Sending Error: Character Limit Exceeded.\n";
			continue;
		}

		int iSend = send(m_oSocket, cBuffer, strlen(cBuffer), 0);

		if (iSend == SOCKET_ERROR)
		{
			std::cout << "Sending Error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			break;
		}
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
		std::cout << "WSAStartUp failed. Result: " << iResult << std::endl;
		WSACleanup();
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		std::cout << "WSAStartUp failed. Version not available." << std::endl;
		WSACleanup();
	}
}

void CSocket::RetrieveIPv4Address()
{
	PCSTR sHostName = "";
	addrinfo* poAddressInfo;

	if (getaddrinfo(sHostName, NULL, 0, &poAddressInfo) != 0)
	{
		std::cout << "name error: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}

	for (addrinfo* poAI = poAddressInfo; poAI != NULL; poAI = poAI->ai_next)
	{
		if (poAI->ai_family != AF_INET)
		{
			continue;
		}

		char csBuffer[256];
		sockaddr_in* poAddIn = (sockaddr_in*)poAI->ai_addr;
		inet_ntop(AF_INET, &poAddIn->sin_addr, csBuffer, 256);
		m_sIPv4 = csBuffer;
	}
}

void CSocket::SetupSocket(int _iPortNumber)
{
	m_oSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_oSocket == INVALID_SOCKET)
	{
		std::cout << "Invalid Socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}

	sockaddr_in oSocketAddress;
	oSocketAddress.sin_family = AF_INET;
	oSocketAddress.sin_port = htons(_iPortNumber);
	oSocketAddress.sin_addr.S_un.S_addr = INADDR_ANY;
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

	std::cout << "Connecting to Server...\n";

	sockaddr_in oServerAddress;
	oServerAddress.sin_family = AF_INET;
	oServerAddress.sin_port = htons(_iServerPortNumber);

	InetPton(AF_INET, L"127.0.0.1", &oServerAddress.sin_addr.S_un.S_addr);

	int iStatus = connect(m_oSocket, (sockaddr*)&oServerAddress, sizeof(oServerAddress));

	if (iStatus == SOCKET_ERROR)
	{
		std::cout << "Connection Error: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}

	else
	{
		std::cout << "Connected.\n";
	}
}

void CSocket::ConnectionRetryTimer(short _siSeconds)
{
	std::cout << "waiting\n";
	std::this_thread::sleep_for(std::chrono::seconds(_siSeconds));
}