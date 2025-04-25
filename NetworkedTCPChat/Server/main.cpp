/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : main.cpp
Description : The entry point of the program.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

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