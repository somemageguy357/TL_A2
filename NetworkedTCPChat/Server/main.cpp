#include "ServerSocket.h"

int main()
{
	CServerSocket* poServerSocket = new CServerSocket(9999);

	delete poServerSocket;

	std::cout << "\nServer end of program.";

	while (true)
	{

	}
}