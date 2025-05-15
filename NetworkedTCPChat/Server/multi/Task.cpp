/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Task.cpp
Description : Contains function definitions for Task.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Task.h"

CTask::CTask(std::string _sSendMessage, SOCKET* _poClientSocket)
{
	m_sSendMessage = _sSendMessage;
	m_poClientSocket = _poClientSocket;
}

CTask::~CTask() {}