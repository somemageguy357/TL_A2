#include "ServerSocket.h"

CServerSocket::CServerSocket(int _iPortNumber)
{
	WSASetup();
	SetupSocket(_iPortNumber);
	Listen();
	Accept();
}

CServerSocket::~CServerSocket()
{
	closesocket(m_oClientSocket);
	closesocket(m_oServerSocket);
}

void CServerSocket::Send(std::string _sMessage)
{
	while (true)
	{
		std::cout << "Sending message to client...\n";

		int iSend = send(m_oClientSocket, _sMessage.c_str(), _sMessage.size(), 0);

		if (iSend == SOCKET_ERROR)
		{
			std::cout << "Sending Error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			break;
		}

		break;
	}

	if (m_iClientCount > 0)
	{
		Receive();
	}
}

void CServerSocket::Receive()
{
	std::cout << "receiving...\n";

	const int kiBufferSize = 257; //Has to be one more than the limit (256).
	char cBuffer[kiBufferSize];
	bool bConnectionLost = false; //If the client was disconnected without using the command. e.g. the client window was closed with [x].

	std::string sSendingMessage = "Server: ";

	while (true)
	{
		std::cout << "Waiting for message from client...\n";

		int iRcv = recv(m_oClientSocket, cBuffer, kiBufferSize - 1, 0);

		if (iRcv == SOCKET_ERROR)
		{
			std::cout << "Receiving Error: " << WSAGetLastError();

			if (WSAGetLastError() == 10054)
			{
				std::cout << ": Connection with client was lost.\n";
			}

			std::cout << std::endl;

			m_iClientCount -= 1;
			bConnectionLost = true;
			break;
		}

		cBuffer[iRcv] = '\0';

		std::string sBuffer = cBuffer;

		std::cout << "\nClient Message: " << sBuffer << std::endl;

		CCommands::ECommand eMessageCommand = CCommands::CheckForCommand(&sBuffer);

		if (eMessageCommand == CCommands::ECommand::Put)
		{
			m_sSavedMessage = sBuffer;
			sSendingMessage += "Message Saved.";
		}

		else if (eMessageCommand == CCommands::ECommand::Get)
		{
			sSendingMessage += "Saved Message: " + m_sSavedMessage;
		}

		else if (eMessageCommand == CCommands::ECommand::Quit)
		{
			sSendingMessage += "Leaving the server.";
			m_iClientCount -= 1;
		}

		else if (eMessageCommand == CCommands::ECommand::Error)
		{
			sSendingMessage += sBuffer;
		}

		else
		{
			sSendingMessage = "User: " + sBuffer;
		}

		break;
	}

	if (bConnectionLost == false || m_iClientCount > 0)
	{
		Send(sSendingMessage);
	}
}

void CServerSocket::WSASetup()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);

	int iResult = WSAStartup(wVersionRequested, &wsaData);

	if (iResult != 0)
	{
		std::cout << "WSAStartUp failed. Result: " << iResult << std::endl;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		std::cout << "WSAStartUp failed. Version not available." << std::endl;
	}
}

void CServerSocket::SetupSocket(int _iPortNumber)
{
	m_oServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_oServerSocket == INVALID_SOCKET)
	{
		std::cout << "Invalid Socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}

	sockaddr_in oSocketAddress;
	oSocketAddress.sin_family = AF_INET;
	oSocketAddress.sin_port = htons(_iPortNumber);
	oSocketAddress.sin_addr.S_un.S_addr = INADDR_ANY;

	int iBound = bind(m_oServerSocket, (sockaddr*)&oSocketAddress, sizeof(oSocketAddress));

	if (iBound == SOCKET_ERROR)
	{
		std::cout << "Binding Error: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}
}

void CServerSocket::Listen()
{
	std::cout << "listening...\n";

	int iStatus = listen(m_oServerSocket, 5);

	if (iStatus == SOCKET_ERROR)
	{
		std::cout << "Listening Error: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}

	TIMEVAL tWait;
	tWait.tv_sec = 1;
	tWait.tv_usec = 0;

	int iNumReady = 0;
	int iCount = 0;

	while (iNumReady == 0)
	{
		std::cout << "\rtime waiting for connection " << iCount;
		iCount += 1;

		fd_set oReadSet;
		FD_ZERO(&oReadSet);
		FD_SET(m_oServerSocket, &oReadSet);

		iNumReady = select(0, &oReadSet, NULL, NULL, &tWait);
	}
}

void CServerSocket::Accept()
{
	sockaddr_in oClientAddress;
	int iClientAddressLength = sizeof(oClientAddress);
	m_oClientSocket = accept(m_oServerSocket, (sockaddr*)&oClientAddress, &iClientAddressLength);

	if (m_oClientSocket == INVALID_SOCKET)
	{
		std::cout << "Accept Error: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}

	m_iClientCount += 1;

	Send("Server: Connection successful.\n\nServer: You can use the following commands:");
	//Send("'/CAPITALIZE [message]' - Capitalizes all letters in the message.");
	//Send("'/REVERSE [message]' - Reverses the order of all letters in the message.");
	//Send("'/PUT [message]' - Saves the message to the server which can be retrieved using /GET.");
	//Send("'/GET' - Gets your saved message from the server if there is one.");
	//Send("'/QUIT' - Disconnects the client from the server.");
}