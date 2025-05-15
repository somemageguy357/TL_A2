#pragma once
#include "ClientSocket.h"

class CThreadPool; //Forward declared.

class CTask
{
public:
	enum class ETaskType
	{
		n,
		Send,
		Receive,
	};

	CTask() = delete;
	CTask(CSocket* _poClientSocket, ETaskType _eTaskType);
	CTask(CSocket* _poClientSocket, ETaskType _eTaskType, CThreadPool* _poThreadPool);
	~CTask();

	void PerformTask();

private:
	CSocket* m_poClientSocket = nullptr;
	ETaskType m_eTaskType;
	CThreadPool* m_poThreadPool = nullptr;
	bool m_bSendAddedToPool = false;

	void PerformReceive();

	void PerformSend();
};