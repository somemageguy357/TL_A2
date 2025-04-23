#include <winsock2.h>
#include <iostream>

#include "Commands.h"

int main()
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

	SOCKET oSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (oSocket == INVALID_SOCKET)
	{
		std::cout << "Invalid Socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}

	sockaddr_in oSocketAddress;
	oSocketAddress.sin_family = AF_INET;
	oSocketAddress.sin_port = htons(9999);
	oSocketAddress.sin_addr.S_un.S_addr = INADDR_ANY;

	int iBound = bind(oSocket, (sockaddr*) &oSocketAddress, sizeof(oSocketAddress));

	if (iBound == SOCKET_ERROR)
	{
		std::cout << "Binding Error: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}

	std::cout << "listening...\n";

	int iStatus = listen(oSocket, 5);

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
		FD_SET(oSocket, &oReadSet);

		iNumReady = select(0, &oReadSet, NULL, NULL, &tWait);
	}

	std::cout << "accepting...\n";

	sockaddr_in oClientAddress;
	int iClientAddressLength = sizeof(oClientAddress);
	SOCKET oClientSocket = accept(oSocket, (sockaddr*)&oClientAddress, &iClientAddressLength);

	if (oClientSocket == INVALID_SOCKET)
	{
		std::cout << "Accept Error: " << WSAGetLastError() << std::endl;
		WSACleanup();
	}


	//std::cout << "accepting 2...\n";

	//sockaddr_in oClientAddress2;
	//int iClientAddressLength2 = sizeof(oClientAddress2);
	//SOCKET oClientSocket2 = accept(oSocket, (sockaddr*)&oClientAddress2, &iClientAddressLength2);

	//if (oClientSocket2 == INVALID_SOCKET)
	//{
	//	std::cout << "Accept 2 Error: " << WSAGetLastError() << std::endl;
	//	WSACleanup();
	//}

	std::cout << "receiving...\n";

	const int kiBufferSize = 257; //Has to be one more than the limit (256).
	char cBuffer[kiBufferSize];

	while (true)
	{
		std::cout << "waiting for message...\n";

		int iRcv = recv(oClientSocket, cBuffer, kiBufferSize - 1, 0);

		if (iRcv == SOCKET_ERROR)
		{
			std::cout << "Receiving Error: " << WSAGetLastError() << std::endl;
			continue;
		}

		cBuffer[iRcv] = '\0';

		std::string sBuffer = cBuffer;

		CCommands::ECommand eMessageCommand = CCommands::CheckForCommand(&sBuffer);

		if (eMessageCommand == CCommands::ECommand::Error)
		{
			//notify client of error message.
			std::cout << sBuffer << std::endl;
		}

		else if (eMessageCommand == CCommands::ECommand::Put)
		{
			std::cout << "Secret message has been put.\n";
		}

		else if (eMessageCommand == CCommands::ECommand::Get)
		{
			std::cout << "Secret message has been retrieved.\n";
		}

		else if (eMessageCommand == CCommands::ECommand::Quit)
		{
			std::cout << "Client has left da server.\n";
		}

		else
		{
			//display message to all clients.
			std::cout << "Client Message: " << sBuffer << std::endl;
		}

		//int iRcv2 = recv(oClientSocket2, cBuffer, 256, 0);

		//if (iRcv2 == SOCKET_ERROR)
		//{
		//	std::cout << "Receiving 2 Error: " << WSAGetLastError() << std::endl;
		//	continue;
		//}

		//cBuffer[iRcv2] = '\0';
		//printf("msg: %s\n\n", cBuffer);
	}

	closesocket(oClientSocket);
	closesocket(oSocket);

	while (true)
	{

	}
}