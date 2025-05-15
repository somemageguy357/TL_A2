/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Task.h
Description : A task that is performed during thread pools.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include <WinSock2.h>

#include <thread>
#include <vector>
#include <string>

#include <iostream>

class CTask
{
public:
	CTask() = delete;

	/// <summary>
	/// Creates a task that is used in a threadpool.
	/// </summary>
	/// <param name="_psURL:">The URL of the image to download from.</param>
	/// <param name="_psOutput:">String used to load images from memory.</param>
	CTask(std::string _sSendMessage, SOCKET* _poClientSocket);

	~CTask();

	/// <summary>
	/// Downloads the image using the downloader and outputs the string to load the memory from.
	/// </summary>
	void PerformTask()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		while (true)
		{
			std::cout << "Sending message to client from task...\n";

			int iSend = send(*m_poClientSocket, m_sSendMessage.c_str(), m_sSendMessage.size(), 0);

			if (iSend == SOCKET_ERROR)
			{
				std::cout << "Sending Error: " << WSAGetLastError() << std::endl;
				WSACleanup();
				break;
			}

			break;
		}
	}

private:
	std::string m_sSendMessage = "";
	SOCKET* m_poClientSocket = nullptr;
};