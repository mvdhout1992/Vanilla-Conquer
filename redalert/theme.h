//
// Copyright 2020 Electronic Arts Inc.
//
// TiberianDawn.DLL and RedAlert.dll and corresponding source code is free
// software: you can redistribute it and/or modify it under the terms of
// the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

// TiberianDawn.DLL and RedAlert.dll and corresponding source code is distributed
// in the hope that it will be useful, but with permitted additional restrictions
// under Section 7 of the GPL. See the GNU General Public License in LICENSE.TXT
// distributed with this program. You should have received a copy of the
// GNU General Public License along with permitted additional restrictions
// with this program. If not, see https://github.com/electronicarts/CnC_Remastered_Collection

/* $Header: /CounterStrike/THEME.H 1     3/03/97 10:26a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : THEME.H                                                      *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : August 14, 1994                                              *
 *                                                                                             *
 *                  Last Update : August 14, 1994   [JLB]                                      *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef THEME_H
#define THEME_H

typedef struct
{
    char Filename[128]; // Filename of score.
    int NameId;         // Text number for full score name.
    char Name[128];     // Name used if NameId is -1
    int Scenario;       // Scenario when it first becomes available.
    int Duration;       // Duration of theme in seconds.
    bool Normal;        // Allowed in normal game play?
    bool Repeat;        // Always repeat this score?
    bool Available;     // Is the score available?
    int Owner;          // What houses are allowed to play this theme (bit field)?
    bool IsHardcoded; // If hard-coded apply RulesClass::Themes() for this song
} ThemeControl;

class ThemeClass
{
private:
    char const* Theme_File_Name(ThemeType theme);

    int Current;       // Handle to current score.
    ThemeType Score;   // Score number currently being played.
    ThemeType Pending; // Score to play next.
    ThemeType IntroTheme; // Theme to play on main menu
    ThemeType MapTheme;   // Theme to play on map screen
    ThemeType ScoreTheme; // Score to play on the SP score screen
    ThemeType FirstTheme;           // First theme that plays on scenario load
    ThemeType CreditsTheme;              // Theme to play on credits screen
    ThemeType MatchEndSkirmishMenuTheme; // Theme to use in skirmish menu after skirmish match ended
    bool AtleastOneThemeAllowed; // To prevent infinite loop when no songs are allowed
    bool RandomFirstScore; //  play Random score as 'first' score on scenario load

    DynamicVectorClass<ThemeControl*> Themes;

    enum
    {
        THEME_DELAY = TIMER_SECOND
    };

public:
    ThemeClass(void);
	~ThemeClass(void);

    ThemeType From_Name(char const* name) const;
    ThemeType Next_Song(ThemeType index) const;
   
    ThemeType Match_End_Skirmish_Menu_Theme(void) const
    {
        return MatchEndSkirmishMenuTheme;
    }

    ThemeType Map_Theme(void) const
    {
        return MapTheme;
    }

    ThemeType Credits_Theme(void) const
    {
        return CreditsTheme;
    }

    ThemeType Intro_Theme(void) const
    {
        return IntroTheme;
    }

   ThemeType Score_Theme(void) const
    {
        return ScoreTheme;
    }

    ThemeType First_Theme(void) const;

    ThemeType What_Is_Playing(void) const
    {
        return Score;
    }
    bool Is_Allowed(ThemeType index) const;
    bool Is_Regular(ThemeType theme) const
    {
        return (theme != THEME_NONE && Themes[theme]->Normal);
    }
    char const* Base_Name(ThemeType index) const;
    char const* Full_Name(ThemeType index) const;
    int Max_Themes(void) const
    {
        return Themes.Count();
    }
    int Play_Song(ThemeType index);
    int Still_Playing(void) const;
    int Track_Length(ThemeType index) const;
    void Scan(void);
    void AI(void);
    void Fade_Out(void)
    {
        Queue_Song(THEME_QUIET);
    }
    void Queue_Song(ThemeType index);
    void Set_Theme_Data(ThemeType theme, int scenario, int owners);
    void Stop(void);
    void Suspend(void);
    bool Is_Hard_Coded(ThemeType theme);
};

#endif
