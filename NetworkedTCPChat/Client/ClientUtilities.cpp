/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name : ClientUtilities.cpp
Description : Contains function definitions for ClientUtilities.h.
Author : Connor Galvin
Mail : Connor.Galvin@mds.ac.nz
**************************************************************************/

#include "ClientUtilities.h"
#include <iostream>
#include <Windows.h>

void CUtilities::Print(std::string _sString, int _iPreNewLines, int _iPostNewLines, EColour _eColour)
{
    SetTextColour(_eColour);

    for (int i = 0; i < _iPreNewLines; i++)
    {
        std::cout << std::endl;
    }

    std::cout << _sString;

    for (int i = 0; i < _iPostNewLines; i++)
    {
        std::cout << std::endl;
    }

    SetTextColour(EColour::White);
}

void CUtilities::SetTextColour(EColour _eColour)
{
    switch (_eColour)
    {
    case EColour::White:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case EColour::Red:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        break;
    case EColour::Green:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        break;
    case EColour::Yellow:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case EColour::Cyan:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    default:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    }
}

bool CUtilities::CompareStrings(std::string _sString1, std::string _sString2, bool _bCaseSensitive)
{
    //If the two strings are not the same size: return false.
    if (_sString1.size() != _sString2.size())
    {
        return false;
    }

    //If case sensitive: compare strings.
    else if (_bCaseSensitive == true)
    {
        if (_sString1 == _sString2)
        {
            return true;
        }
    }

    else //Convert all lower case letters of both strings to capitals for easy comparison.
    {
        std::string s1 = _sString1;
        std::string s2 = _sString2;

        for (size_t i = 0; i < s1.size(); i++)
        {
            if (s1[i] > 96 && s1[i] < 123)
            {
                s1[i] = s1[i] - 32;
            }
        }

        for (size_t i = 0; i < s2.size(); i++)
        {
            if (s2[i] > 96 && s2[i] < 123)
            {
                s2[i] = s2[i] - 32;
            }
        }

        if (s1 == s2)
        {
            return true;
        }
    }

    return false;
}