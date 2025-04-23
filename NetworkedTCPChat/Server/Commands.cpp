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
	//Get command from message.
	std::string sCommand = "";
	int iCommandLength = 0;

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

	//If the start of the message contains the command.
	if (sCommand == "/CAPITALIZE")
	{
		return CapitalizeMessage(_psMessage);
	}

	else if (sCommand == "/GET")
	{
		return GetMessage(_psMessage);
	}

	else if (sCommand == "/PUT")
	{
		return PutMessage(_psMessage);
	}

	else if (sCommand == "/QUIT")
	{
		return Quit(_psMessage);
	}

	else
	{
		*_psMessage = "Command Error: The command " + sCommand + " does not exist.";
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
	if (*_psMessage == "/CAPITALIZE")
	{
		*_psMessage = "Command Error: No text was provided after the command.";
		return ECommand::Error;
	}

	//Remove command from message.
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

CCommands::ECommand CCommands::GetMessage(std::string* _psMessage)
{
	return ECommand::Get;
}

CCommands::ECommand CCommands::PutMessage(std::string* _psMessage)
{
	return ECommand::Put;
}

CCommands::ECommand CCommands::Quit(std::string* _psMessage)
{
	return ECommand::Quit;
}