/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ThreadPool.cpp
Description : Contains function definitions for ThreadPool.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "ClientThreadPool.h"

CThreadPool::CThreadPool()
{
	m_uiThreadCount = std::thread::hardware_concurrency();
	m_iTasksProcessed = 0;

	for (size_t i = 0; i < m_uiThreadCount; i++)
	{
		m_oVecThreads.push_back(std::thread(&CThreadPool::WorkerThread, this));
	}
}

CThreadPool::~CThreadPool()
{
	Stop();
}

void CThreadPool::AddTask(CTask _oTask)
{
	m_oTaskQueue.Push(_oTask);
}

void CThreadPool::Stop()
{
	m_bFinished = true;
	m_oTaskQueue.UnblockAll();

	for (size_t i = 0; i < m_uiThreadCount; i++)
	{
		if (m_oVecThreads[i].joinable() == true)
		{
			m_oVecThreads[i].join();
		}
	}
}

int CThreadPool::GetTaskProcessed()
{
	return m_iTasksProcessed;
}

void CThreadPool::WorkerThread()
{
	CTask oTask(nullptr, CTask::ETaskType::n);

	while (m_bFinished == false)
	{
		if (m_oTaskQueue.BlockPop(oTask) == true)
		{
			oTask.PerformTask();
			m_iTasksProcessed += 1;
		}
	}
}