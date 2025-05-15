#include "ClientTask.h"
#include "ClientUtilities.h"
#include "ClientThreadPool.h"

#include <iostream>

CTask::CTask(CSocket* _poClientSocket, ETaskType _eTaskType)
{
	m_poClientSocket = _poClientSocket;
	m_eTaskType = _eTaskType;
}

CTask::CTask(CSocket* _poClientSocket, ETaskType _eTaskType, CThreadPool* _poThreadPool)
{
	m_poClientSocket = _poClientSocket;
	m_eTaskType = _eTaskType;
	m_poThreadPool = _poThreadPool;
}

CTask::~CTask() {}

void CTask::PerformTask()
{
	if (m_eTaskType == ETaskType::Receive)
	{
		PerformReceive();
	}

	else if (m_eTaskType == ETaskType::Send)
	{
		PerformSend();
	}
}

void CTask::PerformReceive()
{
	const int kiBufferSize = 257; //Has to be one more than the limit (256).
	char cBuffer[kiBufferSize];

	while (true)
	{
		int iRcv = recv(*m_poClientSocket->GetSocket(), cBuffer, kiBufferSize - 1, 0);

		if (iRcv == SOCKET_ERROR)
		{
			CUtilities::Print("Receiving Error: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
			continue;
		}

		cBuffer[iRcv] = '\0';

		break;
	}

	std::string sBuffer = cBuffer;

	if (sBuffer.size() > 0)
	{
		if (sBuffer.substr(0, 7) == "Server:")
		{
			CUtilities::Print(sBuffer, 1, 1, CUtilities::EColour::Yellow);
		}

		else
		{
			CUtilities::Print(sBuffer, 1, 1, CUtilities::EColour::Cyan);
		}
	}

	else
	{
		std::cout << "No/Empty message received.\n";
	}

	//If the message from the server is not a confirmation of the client leaving the server: recurse.
	if (sBuffer != "Server: Leaving the server.")
	{
		if (m_bSendAddedToPool == false)
		{
			m_bSendAddedToPool = true;
			m_poThreadPool->AddTask(CTask(m_poClientSocket, ETaskType::Send));
		}

		PerformReceive();
	}

	else
	{
		m_poClientSocket->SetHasQuit(true);
	}
}

void CTask::PerformSend()
{
	unsigned int uiLineLength = -1;
	const short ksiMaxInputLength = 256;
	char cBuffer[ksiMaxInputLength];
	std::string sMessage;

	while (true)
	{
		std::cin.getline(cBuffer, uiLineLength);

		sMessage = cBuffer;

		if (sMessage.size() > ksiMaxInputLength)
		{
			CUtilities::Print("Sending Error: Character Limit Exceeded.", 0, 1, CUtilities::EColour::Red);
			continue;
		}

		int iSend = send(*m_poClientSocket->GetSocket(), cBuffer, strlen(cBuffer), 0);

		if (iSend == SOCKET_ERROR)
		{
			CUtilities::Print("Sending Error: " + std::to_string(WSAGetLastError()) + ".", 0, 1, CUtilities::EColour::Red);
			WSACleanup();
			break;
		}

		break;
	}

	//If the user has not entered a message starting with "/quit" (or any variation of) AND the socket has not been set to quit: recurse. 
	if (CUtilities::CompareStrings(sMessage.substr(0, 5), "/QUIT", false) == false && m_poClientSocket->GetHasQuit() == false)
	{
		PerformSend();
	}
}