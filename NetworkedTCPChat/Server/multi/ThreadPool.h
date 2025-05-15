/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ThreadPool.h
Description : Contains a queue of tasks for threads to work through.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#pragma once
#include "Task.h"
#include "SafeQueue.h"

#include <thread>
#include <vector>
#include <atomic>

class CThreadPool
{
public:
	/// <summary>
	/// Creates a threadpool and sets up the number of threads that are to be used.
	/// </summary>
	CThreadPool();

	~CThreadPool();

	/// <summary>
	/// Pushes the task to the thread queue.
	/// </summary>
	/// <param name="_oTask:">The task to perform.</param>
	void AddTask(CTask _oTask);

	/// <summary>
	/// Joins all joinable threads to finish the thread pool.
	/// </summary>
	void Stop();

	/// <summary>
	/// Gets the number of tasks processed.
	/// </summary>
	/// <returns>The number of tasks processed.</returns>
	int GetTaskProcessed();

private:
	std::vector<std::thread> m_oVecThreads;
	CSafeQueue<CTask> m_oTaskQueue;

	std::atomic_bool m_bFinished;
	std::atomic_int m_iTasksProcessed;
	unsigned int m_uiThreadCount;

	//Performs each task in the queue.
	void WorkerThread();
};