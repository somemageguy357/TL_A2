/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : Commands.h
Description : Contains commands that are used for clients to interact with when inputing text.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include <string>

class CCommands
{
public:
	enum class ECommand
	{
		n,
		Error,
		Capitalize,
		Reverse,
		Put,
		Get,
		Quit,
	};

	/// <summary>
	/// Checks the string to see if it starts with a "/".
	/// </summary>
	/// <param name="_psMessage:">Pointer to the string to check.</param>
	/// <returns>The command type found if there is one, ECommand::n if there was no command in the string.</returns>
	static ECommand CheckForCommand(std::string* _psMessage);

private:
	CCommands() = delete;
	~CCommands() = delete;

	/// <summary>
	/// Pulls the string apart to find the command. If the command found exists: it will run the appropriate command function or
	/// return the relevant ECommand value. If the found command does not exist, it will return a command error.
	/// </summary>
	/// <param name="_psMessage:">Pointer to the string to check.</param>
	/// <returns>An ECommand relevant to the command found, ECommand::Error if the command does not exist.</returns>
	static ECommand DetermineCommand(std::string* _psMessage);

	/// <summary>
	/// Removes all empty spaces after the last char in the string from the string.
	/// </summary>
	/// <param name="_psMessage:">Pointer to the string to check.</param>
	static void TrimMessage(std::string* _psMessage);

	/// <summary>
	/// Capitalizes all non-capital letters found in the string.
	/// </summary>
	/// <param name="_psMessage:">Pointer to the string to capitalize and change.</param>
	/// <returns>ECommand::Capitalize if the function was successful, ECommand::Error if no text was provided after the command.</returns>
	static ECommand CapitalizeMessage(std::string* _psMessage);

	/// <summary>
	/// Reverses the string.
	/// </summary>
	/// <param name="_psMessage:">Pointer to the string to reverse and change.</param>
	/// <returns>ECommand::Reverse if the function was successful, ECommand::Error if no text was provided after the command.</returns>
	static ECommand ReverseMessage(std::string* _psMessage);

	/// <summary>
	/// Removes the command from the text. Used to store the message on the server, but not display it to any client.
	/// </summary>
	/// <param name="_psMessage:">Pointer to the string whose values are saved to the server.</param>
	/// <returns>ECommand::Put if the function was successful, ECommand::Error if no text was provided after the command.</returns>
	static ECommand PutMessage(std::string* _psMessage);
};