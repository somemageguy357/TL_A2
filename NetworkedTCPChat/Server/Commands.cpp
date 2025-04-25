/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Commands.cpp
Description : Contains function definitions for Commands.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "Commands.h"

#include <iostream>

CCommands::ECommand CCommands::CheckForCommand(std::string* _psMessage)
{
	//Trim message of any ending spaces.
	TrimMessage(_psMessage);

	if ((*_psMessage)[0] == '/')
	{
		return DetermineCommand(_psMessage);
	}

	return ECommand::n;
}

CCommands::ECommand CCommands::DetermineCommand(std::string* _psMessage)
{
	std::string sCommand = "";
	int iCommandLength = 0;

	//Get command from message.
	for (size_t i = 0; i < _psMessage->size(); i++)
	{
		if ((*_psMessage)[i] != ' ')
		{
			iCommandLength += 1;
		}

		else
		{
			break;
		}
	}

	sCommand = _psMessage->substr(0, iCommandLength);

	//Convert all lower case to capitals for when the supplied command is not entirely capital. e.g. /Command, /command.
	for (size_t i = 0; i < sCommand.size(); i++)
	{
		if (sCommand[i] > 96 && sCommand[i] < 123)
		{
			sCommand[i] = sCommand[i] - 32;
		}
	}

	if (sCommand == "/CAPITALIZE")
	{
		return CapitalizeMessage(_psMessage);
	}

	else if (sCommand == "/REVERSE")
	{
		return ReverseMessage(_psMessage);
	}

	else if (sCommand == "/GET")
	{
		return ECommand::Get;
	}

	else if (sCommand == "/PUT")
	{
		return PutMessage(_psMessage);
	}

	else if (sCommand == "/QUIT")
	{
		return ECommand::Quit;
	}

	else
	{
		*_psMessage = "Command Error: The command '" + sCommand + "' does not exist.";
		return ECommand::Error;
	}
}

void CCommands::TrimMessage(std::string* _psMessage)
{
	for (size_t i = _psMessage->size() - 1; (*_psMessage)[i] == ' '; i--)
	{
		_psMessage->erase(i, 1);
	}
}

CCommands::ECommand CCommands::CapitalizeMessage(std::string* _psMessage)
{
	//If the message is just the command.
	if (_psMessage->size() == 11)
	{
		*_psMessage = "Command Error: No text was provided after the command.";
		return ECommand::Error;
	}

	//Remove the command from the message.
	*_psMessage = _psMessage->substr(12);

	//Convert all lower case to capitals.
	for (size_t i = 0; i < _psMessage->size(); i++)
	{
		if ((*_psMessage)[i] > 96 && (*_psMessage)[i] < 123)
		{
			(*_psMessage)[i] = (*_psMessage)[i] - 32;
		}
	}

	return ECommand::Capitalize;
}

CCommands::ECommand CCommands::ReverseMessage(std::string* _psMessage)
{
	//If the message is just the command.
	if (_psMessage->size() == 8)
	{
		*_psMessage = "Command Error: No text was provided after the command.";
		return ECommand::Error;
	}

	//Remove the command from the message.
	*_psMessage = _psMessage->substr(9);

	std::string sReversedMessage = "";

	//Reverse string values for new string.
	for (int i = _psMessage->size() - 1; i > -1; i--)
	{
		sReversedMessage += (*_psMessage)[i];
	}

	*_psMessage = sReversedMessage;

	return ECommand::Reverse;
}

CCommands::ECommand CCommands::PutMessage(std::string* _psMessage)
{
	//If the message is just the command.
	if (_psMessage->size() == 4)
	{
		*_psMessage = "Command Error: No text was provided after the command.";
		return ECommand::Error;
	}

	//Remove the command from the message.
	*_psMessage = _psMessage->substr(5);

	return ECommand::Put;
}
