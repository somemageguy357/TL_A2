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

#include "ClientSocket.h"
#include "ClientThreadPool.h"

#include <string>

int main()
{
	CSocket* poSocket = new CSocket(10001, 9999);

	CThreadPool oThreadPool;

	//Creates a task for the thread pool. After the client has received a connection message from the server, it will add
	//another task that handles the client sending to the server.
	oThreadPool.AddTask(CTask(poSocket, CTask::ETaskType::Receive, &oThreadPool));

	while (oThreadPool.GetTaskProcessed() < 2) {}

	oThreadPool.Stop();

	delete poSocket;

	std::cout << "\nClient end of program.";

	while (true)
	{

	}
}