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