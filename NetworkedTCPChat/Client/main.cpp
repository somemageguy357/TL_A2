#include "Socket.h"

int main()
{
	CSocket* poSocket = new CSocket(10001, 9999);

	delete poSocket;

	std::cout << "\nClient end of program.";

	while (true)
	{

	}
}