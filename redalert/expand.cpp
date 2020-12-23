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

/* $Header: /CounterStrike/EXPAND.CPP 7     3/17/97 1:05a Steve_tall $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : EXPAND.CPP                                                   *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 11/03/95                                                     *
 *                                                                                             *
 *                  Last Update : Mar 01, 1997 [V.Grippi]                                      *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   EListClass::Draw_Entry -- Draws entry for expansion scenario.                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "function.h"
#include "common/framelimit.h"
#include "common/ini.h"

#ifdef FIXIT_VERSION_3
#include "wolstrng.h"
#endif

//#define CS_DEBUG

#define ARRAYOFFSET 20

/***********************************************************************************************
 * Expansion_CS_Present -- Is the Counterstrike expansion available?                           *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   true if counterstrike installed                                                   *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/5/97 1:59PM ST : Fixed to check for EXPAND.MIX                                         *
 *=============================================================================================*/
bool Expansion_CS_Present(void)
{
    //	ajw 9/29/98
    return Is_Counterstrike_Installed();
    //	RawFileClass file("EXPAND.MIX");
    //	return(file.Is_Available());
}
#ifdef FIXIT_CSII //	checked - ajw 9/28/98
/***********************************************************************************************
 * Expansion_AM_Present -- Is the Aftermath expansion available?                               *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   true if AfterMath is installed                                                    *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    7/9/97 1:59PM BG : Fixed to check for EXPAND2.MIX                                        *
 *=============================================================================================*/
bool Expansion_AM_Present(void)
{
    //	ajw 9/29/98
    return Is_Aftermath_Installed();
    //	RawFileClass file("EXPAND2.MIX");
    //	return(file.Is_Available());
}
#endif

const char* ExpandNames[] = {"SCG20EA", "SCG21EA", "SCG22EA", "SCG23EA", "SCG24EA", "SCG26EA", "SCG27EA", "SCG28EA",
                             "SCU31EA", "SCU32EA", "SCU33EA", "SCU34EA", "SCU35EA", "SCU36EA", "SCU37EA", "SCU38EA",
#ifdef FIXIT_CSII                       //	checked - ajw 9/28/98
                             "SCG43EA", // Harbor Reclamation
                             "SCG41EA", // In the nick of time
                             "SCG40EA", // Caught in the act
                             "SCG42EA", // Production Disruption
                             "SCG47EA", // Negotiations
                             "SCG45EA", // Monster Tank Madness
                             "SCG44EA", // Time Flies
                             "SCG48EA", // Absolut MADness
                             "SCG46EA", // Pawn

                             "SCU43EA", // Testing Grounds
                             "SCU40EA", // Shock Therapy
                             "SCU42EA", // Let's Make a Steal
                             "SCU41EA", // Test Drive
                             "SCU45EA", // Don't Drink The Water
                             "SCU44EA", // Situation Critical
                             "SCU46EA", // Brothers in Arms
                             "SCU47EA", // Deus Ex Machina
                             "SCU48EA", // Grunyev Revolution
#endif
                             NULL};

const char* CampaignNames[] = {"SCG01EA", //0
							"SCG02EA", //1
							"SCG03EA", //2
							"SCG03EB", //3

                            "SCG04EA", //4
                            "SCG05EA", //5
							"SCG05EB", //6
							"SCG05EC", //7

                            "SCG06EA", //8
							"SCG06EB", //9

                            "SCG07EA", //10
                            "SCG08EA", //11
							"SCG08EB", //12

							"SCG09EA", //13
							"SCG09EB", //14

							"SCG10EA", //15
							"SCG10EB", //16

							"SCG11EA", //17
							"SCG11EB", //18

							"SCG12EA", //19
							"SCG13EA", //20
							"SCG14EA", //21

                            "SCU01EA", //22
                            "SCU02EA", //23
							"SCU02EB", //24

                            "SCU03EA", //25
                            "SCU04EA", //26
							"SCU04EB", //27

                            "SCU05EA", //28
                            "SCU06EA", //29
							"SCU06EB", //30

                            "SCU07EA", //31
                            "SCU08EA", //32
							"SCU08EB", //33

                            "SCU09EA", //34
							"SCU10EA", //35
							"SCU11EA", //36
							"SCU11EB", //37

							"SCU12EA", //38
							"SCU13EA", // 39
							"SCU13EB", // 40

							"SCU14EA", // 41
                            NULL};

// ant, demo and v0.9c beta
const char* BonusMissions[] = { "SCA01EA", //0 ant 1
								"SCA02EA", //1 ant 2
								"SCA03EA", //2 ant 3
								"SCA04EA", //3 ant 4
								
								"SCG02EA_DEMO", //4 demo allied mission 2
								"SCG05EB_DEMO", //5 demo allied mission 5b
								"SCU01EA_DEMO", //6 demo soviet mission 1?
						
								"LOSTMISSION", //7 Recreation of lost mission from early trailers, by Chad1233 and tomsons26
											   // from v0.9c beta files

								
							"SCG01EA_BETA", //8
							"SCG02EA_BETA", //9
							"SCG03EA_BETA", //10
							"SCG03EB_BETA", //11

							"SCG04EA_BETA", //12
							"SCG05EA_BETA", //13
							"SCG05EB_BETA", //14
							"SCG05EC_BETA", //15

							"SCG06EA_BETA", //16
							"SCG06EB_BETA", //17

							"SCG07EA_BETA", //18
							"SCG08EA_BETA", //19
							"SCG08EB_BETA", //20
							"SCG08WA_BETA",

							"SCG09EA_BETA", //21
							"SCG09EB_BETA", //22

							"SCG10EA_BETA", //23
							"SCG10EB_BETA", //24

							"SCG11EA_BETA", //25
							"SCG11EB_BETA", //26

							"SCG12EA_BETA", //27
							"SCG13EA_BETA", //28
							"SCG14EA_BETA", //29

							"SCU01EA_BETA", //30
							"SCU02EA_BETA", //31
							"SCU02EB_BETA", //32

							"SCU03EA_BETA", //33
							"SCU04EA_BETA", //34
							"SCU04EB_BETA", //35

							"SCU05EA_BETA", //36
							"SCU06EA_BETA", //37
							"SCU06EB_BETA", //38

							"SCU07EA_BETA", //39
							"SCU08EA_BETA", //40
							"SCU08EB_BETA", //41

							"SCU09EA_BETA", //42
							"SCU10EA_BETA", //43
							"SCU11EA_BETA", //44
							"SCU11EB_BETA", //45

							"SCU12EA_BETA", //46
							"SCU13EA_BETA", // 47
							"SCU13EB_BETA", // 48

							"SCU14EA", // 49
								NULL };

#ifdef GERMAN
const char* XlatNames[] = {"Zusammenstoss",
                           "Unter Tage",
                           "Kontrollierte Verbrennung",
                           "Griechenland 1 - Stavros",
                           "Griechenland 2 - Evakuierung",
                           "Sibirien 1 - Frische Spuren",
                           "Sibirien 2 - In der Falle",
                           "Sibirien 3 - Wildnis",
                           "Das Feld der Ehre",
                           "Belagerung",
                           "Mausefalle",
                           "Teslas Erbe",
                           "Soldat Volkov",
                           "Die Spitze der Welt",
                           "Paradoxe Gleichung",
                           "Nukleare Eskalation",
#ifdef FIXIT_CSII                                           //	checked - ajw 9/28/98
                           "Ein sicherer Hafen",            //	"SCG43EA",		// Harbor Reclamation
                           "Zeitkritische Routine",         //	"SCG41EA",		// In the nick of time
                           "Auf frischer Tat ertappt",      //	"SCG40EA",		// Caught in the act
                           "Drastischer Baustopp",          //	"SCG42EA",		// Production Disruption
                           "Harte Verhandlungen",           //	"SCG47EA",		// Negotiations
                           "Ferngelenktes Kriegsspielzeug", //	"SCG45EA",		// Monster Tank Madness
                           "Licht aus",                     //	"SCG44EA",		// Time Flies
                           "Molekulare Kriegsfhrung",      //	"SCG48EA",		// Absolut MADness
                           "Bauernopfer",                   //	"SCG46EA",		// Pawn

                           "Testgel„nde",                 //	"SCU43EA",		// Testing Grounds
                           "Schocktherapie",              //	"SCU40EA",		// Shock Therapy
                           "Der Letzte seiner Art",       //	"SCU42EA",		// Let's Make a Steal
                           "Probefahrt",                  //	"SCU41EA",		// Test Drive
                           "Schlaftrunk",                 //	"SCU45EA",		// Don't Drink The Water
                           "Der jngste Tag",             //	"SCU44EA",		// Situation Critical
                           "Waffenbrder",                //	"SCU46EA",		// Brothers in Arms
                           "Deus Ex Machina",             //	"SCU47EA",		// Deus Ex Machina
                           "Die Replikanten von Grunyev", //	"SCU48EA",		// Grunyev Revolution

#endif
                           NULL};

#endif

#ifdef FRENCH
const char* XlatNames[] = {
    "Gaz Sarin 1: Ravitaillement Fatal",
    "Gaz Sarin 2: En Sous-sol",
    "Gaz Sarin 3: Attaque Chirurgicale",
    "GrŠce Occup‚e 1: Guerre Priv‚e",
    "GrŠce Occup‚e 2: Evacuation",
    "Conflit Sib‚rien 1: Traces FraŒches",
    "Conflit Sib‚rien 2: Pris au PiŠge",
    "Conflit Sib‚rien 3: Terres de Glace",
    "Mise … l'Epreuve",
    "Assi‚g‚s",
    "La SouriciŠre",
    "L'H‚ritage de Tesla",
    "Tandem de Choc",
    "Jusqu'au Sommet du Monde",
    "Effets Secondaires",
    "Intensification nucl‚aire",
#ifdef FIXIT_CSII             //	checked - ajw 9/28/98
    "Le vieux port",          //	"SCG43EA",		// Harbor Reclamation
    "Juste … temps",          //	"SCG41EA",		// In the nick of time
    "La main dans le sac",    //	"SCG40EA",		// Caught in the act
    "Production interrompue", //	"SCG42EA",		// Production Disruption
    "N‚gociations",           //	"SCG47EA",		// Negotiations
    "Tanks en folie!",        //	"SCG45EA",		// Monster Tank Madness
    "Le temps passe",         //	"SCG44EA",		// Time Flies
    "D‚mence absolue",        //	"SCG48EA",		// Absolut MADness
    "Le pion",                //	"SCG46EA",		// Pawn

    "Terrains d'essais",        //	"SCU43EA",		// Testing Grounds
    "Th‚rapie de choc",         //	"SCU40EA",		// Shock Therapy
    "Au voleur!",               //	"SCU42EA",		// Let's Make a Steal
    "Essai de conduite",        //	"SCU41EA",		// Test Drive
    "Ne buvez pas la tasse",    //	"SCU45EA",		// Don't Drink The Water
    "Situation critique",       //	"SCU44EA",		// Situation Critical
    "FrŠres d'armes",           //	"SCU46EA",		// Brothers in Arms
    "Deus Ex Machina",          //	"SCU47EA",		// Deus Ex Machina
    "La R‚volution de Grunyev", //	"SCU48EA",		// Grunyev Revolution

#endif

    NULL,
};

#endif

#define OPTION_WIDTH 560
#ifdef FIXIT_CSII //	checked - ajw 9/28/98
#define OPTION_HEIGHT 332
#else
#define OPTION_HEIGHT 300
#endif
#define OPTION_X ((640 - OPTION_WIDTH) / 2)
#define OPTION_Y (400 - OPTION_HEIGHT) / 2

struct EObjectClass
{
    HousesType House;
	bool ShowPlayerHouse;
    int Scenario;
    char Name[128];
    char FullName[128];
};

/*
**	Derived from list class to handle expansion scenario listings. The listings
**	are recorded as EObjectClass objects. The data contained specifies the scenario
**	number, side, and text description.
*/
class EListClass : public ListClass
{
public:
    EListClass(int id, int x, int y, int w, int h, TextPrintType flags, void const* up, void const* down)
        : ListClass(id, x, y, w, h, flags, up, down){};

    virtual int Add_Object(EObjectClass* obj)
    {
        return (ListClass::Add_Item((char const*)obj));
    }
    virtual EObjectClass* Get_Object(int index) const
    {
        return ((EObjectClass*)ListClass::Get_Item(index));
    }
    virtual EObjectClass* Current_Object(void)
    {
        return ((EObjectClass*)ListClass::Current_Item());
    }
	virtual int Add_Item(char const* text)
	{
		return (ListClass::Add_Item(text));
	};
	virtual int Add_Item(int text)
	{
		return (ListClass::Add_Item(text));
	};
	virtual char const* Current_Item(void) const
	{
		return (ListClass::Current_Item());
	};
	virtual char const* Get_Item(int index) const
	{
		return (ListClass::Get_Item(index));
	};

protected:
    virtual void Draw_Entry(int index, int x, int y, int width, int selected);

};

/***********************************************************************************************
 * EListClass::Draw_Entry -- Draws entry for expansion scenario.                               *
 *                                                                                             *
 *    This overrides the normal list class draw action so that the scenario name will be       *
 *    displayed along with the house name.                                                     *
 *                                                                                             *
 * INPUT:   index    -- The index of the entry that should be drawn.                           *
 *                                                                                             *
 *          x,y      -- Coordinate of upper left region to draw the entry into.                *
 *                                                                                             *
 *          width    -- Width of region (pixels) to draw the entry.                            *
 *                                                                                             *
 *          selected -- Is this entry considered selected?                                     *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/17/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
void EListClass::Draw_Entry(int index, int x, int y, int width, int selected)
{
	char buffer[128];
	RemapControlType* scheme = GadgetClass::Get_Color_Scheme();

	int text = TXT_NONE;
	if (Get_Object(index)->House == HOUSE_GOOD) {
		text = TXT_ALLIES;
	}
	else {
		text = TXT_SOVIET;
	}
	if (Get_Object(index)->ShowPlayerHouse) {
		sprintf(buffer, "%s: %s", Text_String(text), Get_Object(index)->Name);
	}
	else {
		sprintf(buffer, "%s", Get_Object(index)->Name);
	}

    TextPrintType flags = TextFlags;

    if (selected) {
        flags = flags | TPF_BRIGHT_COLOR;
        LogicPage->Fill_Rect(x, y, x + width - 1, y + LineHeight - 1, 1);
    } else {
        if (!(flags & TPF_USE_GRAD_PAL)) {
            flags = flags | TPF_MEDIUM_COLOR;
        }
    }

    Conquer_Clip_Text_Print(buffer, x + 100, y, scheme, TBLACK, flags & ~(TPF_CENTER), width, Tabs);
}

void Update_Mission_Category_Tabs_On_Off_Status(TextButtonClass *CSButton, TextButtonClass *AMButton, TextButtonClass *FanButton, TextButtonClass *CampaignButton,
	bool CSon, bool AMon, bool FanOn, bool CampaignOn) {
	// Check bool args to see if only one tab is turned on, if none or multiple are on then force Counterstrike tab only on
	int count = 0;
	count += (int)CSon + (int)AMon + (int)FanOn + (int)CampaignOn;
	if (count != 1) {
		CSon = true;
		AMon = FanOn = CampaignOn = false;
	}
	CSButton->IsOn = CSon;
	AMButton->IsOn = AMon;
	FanButton->IsOn = FanOn;
	CampaignButton->IsOn = CampaignOn;
}

void Set_Show_Mission_Global_Variables(bool CSon, bool AMon, bool FanOn, bool CampaignOn) {
	ShowCSMissions = CSon;
	ShowAMMissions = AMon;
	ShowNewMissions = FanOn;
	ShowCampaignMissions = CampaignOn;
}

bool Expansion_Dialog(bool &forceOneTimeOnly)
{
    GadgetClass* buttons = NULL;

	TextButtonClass showCSBut(203, TXT_WOL_CS_MISSIONS, TPF_BUTTON, OPTION_X + 35, OPTION_Y + 20);
	TextButtonClass showAMBut(204, TXT_WOL_AM_MISSIONS, TPF_BUTTON, OPTION_X + 250, OPTION_Y + 20);
	TextButtonClass showFanBut(205, TXT_NEW_MISSIONS, TPF_BUTTON, OPTION_X + 430, OPTION_Y + 20);
	TextButtonClass showCampaignBut(206, "Campaign", TPF_BUTTON, OPTION_X + 600, OPTION_Y + 20);

	showCSBut.IsToggleType = true;
	showAMBut.IsToggleType = true;
	showFanBut.IsToggleType = true;
	showCampaignBut.IsToggleType = true;

	showCSBut.IsOn = ShowCSMissions;
	showAMBut.IsOn = ShowAMMissions;
	showFanBut.IsOn = ShowNewMissions;
	showCampaignBut.IsOn = ShowCampaignMissions;


    TextButtonClass ok(200, TXT_OK, TPF_BUTTON, OPTION_X + 40, OPTION_Y + OPTION_HEIGHT - 40);
    TextButtonClass cancel(201, TXT_CANCEL, TPF_BUTTON, OPTION_X + OPTION_WIDTH - 85, OPTION_Y + OPTION_HEIGHT - 40);

    EListClass list(202,
                    OPTION_X + 35,
                    OPTION_Y + 40,
                    OPTION_WIDTH - 70,
                    OPTION_HEIGHT - 85,
                    TPF_BUTTON,
                    MFCD::Retrieve("BTN-UP.SHP"),
                    MFCD::Retrieve("BTN-DN.SHP"));


    buttons = &ok;

	showFanBut.Add(*buttons);
	showAMBut.Add(*buttons);
	showCSBut.Add(*buttons);
	showCampaignBut.Add(*buttons);

    cancel.Add(*buttons);
    list.Add(*buttons);


    Set_Logic_Page(SeenBuff);
    bool recalc = true;
    bool display = true;
    bool process = true;
    bool okval = true;

    while (process) {

		//if(showAMBut.IsPressed || showCSBut.IsPressed || showFanBut.IsPressed) {

		if (recalc) {
			recalc = false;
			display = true;

			char buffer3[256];
			bool restoreSelected = false;

			// save current selected list item if any before emptying list
			if (list.Current_Item() != NULL) {
				strcpy_s(buffer3, 256, list.Current_Item());
				restoreSelected = true;
			}

			while (list.Count() > 0) {
				list.Remove_Item(0);
			}


			Update_Mission_Category_Tabs_On_Off_Status(&showCSBut, &showAMBut, &showFanBut, &showCampaignBut,
				ShowCSMissions, ShowAMMissions, ShowNewMissions, ShowCampaignMissions);

			/*
			**	Add in all the expansion scenarios.
			*/
			CCFileClass file;
			char buffer[128], buffer2[128];
			INIClass ini;

			int start = 20;
			if (showCampaignBut.IsOn ) {
				start = 0;
			}
			else if (showFanBut.IsOn) {
				start = 1;
			}

			int limit = (36 + 18);
			if (showFanBut.IsOn) {
				limit = 999;
			}
			else if (showCampaignBut.IsOn)
			{
				limit = 41;
			}

			for (int index = start; index < limit; index++) {

				if (showAMBut.IsOn || showCSBut.IsOn) {
					strcpy(buffer, ExpandNames[index - 20]);
					strcpy(buffer2, ExpandNames[index - 20]);
				}
				else if (showCampaignBut.IsOn)
				{
					strcpy(buffer, CampaignNames[index]);
					strcpy(buffer2, CampaignNames[index]);
				}
				else if (showFanBut.IsOn) {
					sprintf(buffer, "cmu%02dea", index);
					sprintf(buffer2, "cmu%02dea", index);
				}

				if (buffer[0] == NULL)
					break;

				strcat(buffer, ".INI");
				strcat(buffer2, ".INI");
				Scen.Set_Scenario_Name(buffer);
				Scen.Scenario = index;
				file.Set_Name(buffer);

				bool bOk = false;
				if ((index < 36) && showCSBut.IsOn) {
					bOk = true;
				}
				else if ((index >= 36) && showAMBut.IsOn) {
					bOk = true;
				}
				else if (showCampaignBut.IsOn || showFanBut.IsOn) {
					bOk = true;
				}

				if (bOk && file.Is_Available()) {
					if (ShowCampaignMissions) {
						forceOneTimeOnly = true;
					}
					EObjectClass* obj = new EObjectClass;
					ini.Clear();
					ini.Load(file);
					ini.Get_String("Basic", "Name", "x", buffer, sizeof(buffer));
#if defined(GERMAN) || defined(FRENCH)
					strcpy(obj->Name, XlatNames[index - ARRAYOFFSET]);
#else
					strcpy(obj->Name, buffer);
#endif
					strcpy(obj->FullName, buffer2);

					obj->Scenario = index;
					obj->ShowPlayerHouse = false;
					

					switch (buffer[2]) {

					case 'G':
					case 'g':
						obj->House = HOUSE_GOOD;
						obj->ShowPlayerHouse = true;

						break;

					case 'U':
					case 'u':
						obj->House = HOUSE_GOOD;
						obj->ShowPlayerHouse = true;
						break;

					default:
						break;
					}
					list.Add_Object(obj);
				}
			}
			if (restoreSelected) {
				list.Set_Selected_Index(buffer3);

			}
		}



		//if (showAMBut.IsOn != ShowAMMissions) {
		if (showAMBut.IsPressed) {
			Set_Show_Mission_Global_Variables(false, true, false, false);
			//ShowAMMissions = showAMBut.IsOn;
			recalc = true;
		}
		//if (showCSBut.IsOn != ShowCSMissions) {
		if (showCSBut.IsPressed) {
			Set_Show_Mission_Global_Variables(true, false, false, false);
			//ShowCSMissions = showCSBut.IsOn;
			recalc = true;
		}
		//if (showFanBut.IsOn != ShowNewMissions) {
		if (showFanBut.IsPressed) {
			Set_Show_Mission_Global_Variables(false, false, true, false);
			recalc = true;
		}

		//if (showCampaignBut.IsOn != ShowCampaignMissions) {
		if (showCampaignBut.IsPressed) {
			Set_Show_Mission_Global_Variables(false, false, false, true);
			recalc = true;
		}


        /*
        ** If we have just received input focus again after running in the background then
        ** we need to redraw.
        */
        if (AllSurfaces.SurfacesRestored) {
            AllSurfaces.SurfacesRestored = false;
            display = true;
        }

        Call_Back();

        if (display) {
            display = false;

            Hide_Mouse();

            /*
            **	Load the background picture.
            */
            Load_Title_Page();
            CCPalette.Set();

            Dialog_Box(OPTION_X, OPTION_Y, OPTION_WIDTH, OPTION_HEIGHT);

            //Draw_Caption(TXT_NEW_MISSIONS, OPTION_X, OPTION_Y, OPTION_WIDTH);

            buttons->Draw_All();
            Show_Mouse();
        }


        KeyNumType input = buttons->Input();
        switch (input) {
        case 200 | KN_BUTTON:
            Whom = list.Current_Object()->House;
            Scen.Scenario = list.Current_Object()->Scenario;
            strcpy(Scen.ScenarioName, list.Current_Object()->FullName);
            process = false;
            okval = true;
            break;

        case KN_ESC:
        case 201 | KN_BUTTON:
            process = false;
            okval = false;
            break;

        case (KN_RETURN):
            Whom = list.Current_Object()->House;
            Scen.Scenario = list.Current_Object()->Scenario;
            strcpy(Scen.ScenarioName, list.Current_Object()->FullName);
            process = false;
            okval = true;
            break;

        default:
            break;
        }

		
        Frame_Limiter();
    }

    /*
    **	Free up the allocations for the text lines in the list box.
    */
    for (int index = 0; index < list.Count(); index++) {
        delete list.Get_Object(index);
    }

	FileClass *config_file = new CCFileClass(CONFIG_FILE_NAME);
	if (config_file->Is_Available()) {
		INIClass ini;
		ini.Load(*config_file);

		ini.Put_Bool("Options", "ShowAMMissions", ShowAMMissions);
		ini.Put_Bool("Options", "ShowCSMissions", ShowCSMissions);
		ini.Put_Bool("Options", "ShowNewMissions", ShowNewMissions);
		ini.Put_Bool("Options", "ShowCampaignMissions", ShowCampaignMissions);
		ini.Save(*config_file);
	}

    return (okval);
}
