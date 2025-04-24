#include "Socket.h"

int main()
{
	//WORD wVersionRequested;
	//WSADATA wsaData;
	//wVersionRequested = MAKEWORD(2, 2);

	//int iResult = WSAStartup(wVersionRequested, &wsaData);

	//if (iResult != 0)
	//{
	//	std::cout << "WSAStartUp failed. Result: " << iResult << std::endl;
	//}

	//if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	//{
	//	std::cout << "WSAStartUp failed. Version not available." << std::endl;
	//}

	//PCSTR str = "";
	//addrinfo* addrInfo;

	//if (getaddrinfo(str, NULL, 0, &addrInfo) != 0)
	//{
	//	std::cout << "name error: " << WSAGetLastError() << std::endl;
	//}

	//int i = 0;

	//for (addrinfo* ptr = addrInfo; ptr != NULL; ptr = ptr->ai_next)
	//{
	//	std::cout << "response: " << i;
	//	i += 1;
	//	std::cout << ", family: " << ptr->ai_family << std::endl;

	//	if (ptr->ai_family != AF_INET)
	//	{
	//		continue;
	//	}
	//	
	//	char str2[256];
	//	sockaddr_in* addin = (sockaddr_in*)ptr->ai_addr;
	//	inet_ntop(AF_INET, &addin->sin_addr, str2, 256);
	//	std::cout << "IPv4 address: " << str2 << std::endl;
	//}

	//SOCKET oSocket;
	
	//oSocket = socket(AF_INET, SOCK_STREAM, 0);

	//if (oSocket == INVALID_SOCKET)
	//{
	//	std::cout << "Invalid Socket: " << WSAGetLastError() << std::endl;
	//}

	//sockaddr_in oSocketAddress;
	//oSocketAddress.sin_family = AF_INET;
	//oSocketAddress.sin_port = htons(10001);
	//oSocketAddress.sin_addr.S_un.S_addr = INADDR_ANY;

	//sockaddr_in oRecvAddress;
	//oRecvAddress.sin_family = AF_INET;
	//oRecvAddress.sin_port = htons(10000);

	//InetPton(AF_INET, L"127.0.0.1", &oRecvAddress.sin_addr.S_un.S_addr);

	//int iStatus = connect(oSocket, (sockaddr*)&oRecvAddress, sizeof(oRecvAddress));

	//if (iStatus == SOCKET_ERROR)
	//{
	//	std::cout << "Connection Error: " << WSAGetLastError() << std::endl;
	//	WSACleanup();
	//}

	//char cBuffer[256];

	//while (true)
	//{
	//	std::cout << "Enter a message to send:\n";

	//	std::cin.getline(cBuffer, 256);

	//	int iSend = send(oSocket, cBuffer, strlen(cBuffer), 0);

	//	if (iSend == SOCKET_ERROR)
	//	{
	//		std::cout << "Sending Error: " << WSAGetLastError() << std::endl;
	//		break;
	//	}
	//}

	//closesocket(oSocket);

	CSocket* poSocket = new CSocket(10001, 9999);
	poSocket->Send();
	poSocket->Receive();

	while (true)
	{

	}

	delete poSocket;
}