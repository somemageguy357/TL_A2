/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ClientUtilities.h
Description : Contains general functions that are to be used throughout the program.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include <string>

//Contains general functions that are to be used throughout the program.
class CUtilities
{
public:
	//The colour used for console text.
	enum class EColour
	{
		White,
		Red,
		Green,
		Yellow,
		Cyan,
	};

	/// <summary>
	/// Prints the given string to the console window with the chosen number of new lines both before and after it, as well
	/// as its colour. 
	/// </summary>
	/// <param name="_sString:">The text to display.</param>
	/// <param name="_iPreNewLines:">The number of new lines before the text.</param>
	/// <param name="_iPostNewLines:">The number of new lines after the text.</param>
	/// <param name="_eColour:">The colour of the text (defaulted to white).</param>
	static void Print(std::string _sString, int _iPreNewLines, int _iPostNewLines, EColour _eColour = EColour::White);

	static bool CompareStrings(std::string _sString1, std::string _sString2, bool _bCaseSensitive);

private:
	CUtilities() = delete;
	~CUtilities() = delete;

	//Sets the colour of text to the given value.
	static void SetTextColour(EColour _eColour);
};