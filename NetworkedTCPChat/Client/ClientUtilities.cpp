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