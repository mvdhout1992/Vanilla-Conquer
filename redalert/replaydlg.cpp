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

/* $Header: /CounterStrike/LOADDLG.CPP 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : LOADDLG.CPP                                                  *
 *                                                                                             *
 *                   Programmer : Maria Legg, Joe Bostic, Bill Randolph                        *
 *                                                                                             *
 *                   Start Date : March 19, 1995                                               *
 *                                                                                             *
 *                  Last Update : June 25, 1995 [JLB]                                          *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   LoadOptionsClass::LoadOptionsClass -- class constructor                                   *
 *   LoadOptionsClass::~LoadOptionsClass -- class destructor                                   *
 *   LoadOptionsClass::Process -- main processing routine                                      *
 *   LoadOptionsClass::Clear_List -- clears the list box & Files arrays                        *
 *   LoadOptionsClass::Fill_List -- fills the list box & GameNum arrays                        *
 *   LoadOptionsClass::Num_From_Ext -- clears the list box & GameNum arrays                    *
 *   LoadOptionsClass::Compare -- for qsort                                                    *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "function.h"
#include "msgbox.h"
#include "edit.h"
#include "drop.h"
#include "textbtn.h"
#include "replaydlg.h"
#include "common/file.h"
#include "common/framelimit.h"

/***********************************************************************************************
 * LoadOptionsClass::LoadOptionsClass -- class constructor                                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      style      style for this load/save dialog (LOAD/SAVE/DELETE)                          *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/14/1995 BR : Created.                                                                  *
 *=============================================================================================*/
LoadReplayClass::LoadReplayClass()
{
    Files.Clear();
}

/***********************************************************************************************
 * LoadOptionsClass::~LoadOptionsClass -- class destructor                                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/14/1995 BR : Created.                                                                  *
 *=============================================================================================*/
LoadReplayClass::~LoadReplayClass()
{
    for (int i = 0; i < Files.Count(); i++) {
        delete Files[i];
    }
    Files.Clear();
}

/***********************************************************************************************
 * LoadOptionsClass::Process -- main processing routine                                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      false = User cancelled, true = operation completed                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/14/1995 BR : Created.                                                                  *
 *=============================================================================================*/
int LoadReplayClass::Process(void)
{
    /*
    ** Dialog & button dimensions
    */
    int factor = (SeenBuff.Get_Width() == 320) ? 1 : 2;
    int d_dialog_w = 250 * factor;                             // dialog width
    int d_dialog_h = 156 * factor;                             // dialog height
    int d_dialog_x = (SeenBuff.Get_Width() - d_dialog_w) / 2;  // centered x-coord
    int d_dialog_y = (SeenBuff.Get_Height() - d_dialog_h) / 2; // centered y-coord
    int d_dialog_cx = d_dialog_x + (d_dialog_w / 2);           // coord of x-center
    int d_txt8_h = 11 * factor;                                // ht of 8-pt text
    int d_margin = 7 * factor;                                 // margin width/height
    int x_margin = 16 * factor;                                // margin width/height

    int d_list_w = d_dialog_w - (x_margin * 2);
    int d_list_h = 104 * factor;
    int d_list_x = d_dialog_x + x_margin;
    int d_list_y = d_dialog_y + d_margin + d_txt8_h + d_margin;

    int d_edit_w = d_dialog_w - (x_margin * 2);
    int d_edit_h = 13 * factor;
    int d_edit_x = d_dialog_x + x_margin;
    int d_edit_y = d_list_y + d_list_h - (30 * factor) + d_margin + d_txt8_h;

#if (GERMAN | FRENCH)
    int d_button_w = 50 * factor;
#else
    int d_button_w = 40 * factor;
#endif
    int d_button_h = 13 * factor;
    int d_button_x = d_dialog_cx - d_button_w - d_margin;
    int d_button_y = d_dialog_y + d_dialog_h - d_button_h - d_margin;

#if defined(GERMAN) || defined(FRENCH)
    int d_cancel_w = 60 * factor; // BG:40
#else
    int d_cancel_w = 40 * factor;
#endif
    int d_cancel_h = 13 * factor;
    int d_cancel_x = d_dialog_cx + d_margin;
    int d_cancel_y = d_dialog_y + d_dialog_h - d_cancel_h - d_margin;

    /*
    ** Button enumerations
    */
    enum
    {
        BUTTON_LOAD = 100,
        BUTTON_SAVE,
        BUTTON_DELETE,
        BUTTON_CANCEL,
        BUTTON_LIST,
        BUTTON_EDIT,
    };

    /*
    ** Redraw values: in order from "top" to "bottom" layer of the dialog
    */
    typedef enum
    {
        REDRAW_NONE = 0,
        REDRAW_BUTTONS,
        REDRAW_BACKGROUND,
        REDRAW_ALL = REDRAW_BACKGROUND
    } RedrawType;

    /*
    ** Dialog variables
    */
    bool cancel = false;    // true = user cancels
    int list_ht = d_list_h; // adjusted list box height

    /*
    ** Other Variables
    */
    int btn_txt;                        // text on the 'OK' button
    int btn_id;                         // ID of 'OK' button
    int caption;                        // dialog caption
    int game_idx = 0;                   // index of game to save/load/etc
    int game_num = 0;                   // file number of game to load/save/etc
    char game_descr[DESCRIP_MAX] = {0}; // save-game description
    char fname[_MAX_NAME + _MAX_EXT];   // for generating filename to delete
    int rc;                             // return code

    /*
    ** Buttons
    */
    ControlClass* commands = NULL; // the button list

        btn_txt = TXT_LOAD_BUTTON;
        btn_id = BUTTON_LOAD;
        // caption = TXT_LOAD_MISSION;


    TextButtonClass button(btn_id, btn_txt, TPF_BUTTON, d_button_x, d_button_y, d_button_w);
    TextButtonClass cancelbtn(BUTTON_CANCEL, TXT_CANCEL, TPF_BUTTON, d_cancel_x, d_cancel_y, d_cancel_w);

    ListClass listbtn(BUTTON_LIST,
                      d_list_x,
                      d_list_y,
                      d_list_w,
                      list_ht,
                      TPF_6PT_GRAD | TPF_NOSHADOW,
                      MFCD::Retrieve("BTN-UP.SHP"),
                      MFCD::Retrieve("BTN-DN.SHP"));

    EditClass editbtn(BUTTON_EDIT,
                      game_descr,
                      sizeof(game_descr) - 4,
                      TPF_6PT_GRAD | TPF_NOSHADOW,
                      d_edit_x,
                      d_edit_y,
                      d_edit_w,
                      -1,
                      EditClass::ALPHANUMERIC);

    /*
    ** Initialize.
    */
    Set_Logic_Page(SeenBuff);

    Fill_List(&listbtn);

    /*
    ** Do nothing if list is empty.
    */
    if (listbtn.Count() == 0) {
        Clear_List(&listbtn);
        WWMessageBox().Process(TXT_NO_SAVES);
        return (false);
    }
    /*
    ** Create the button list.
    */
    commands = &button;
    cancelbtn.Add_Tail(*commands);
    listbtn.Add_Tail(*commands);

    /*
    ** Main Processing Loop.
    */
    Keyboard->Clear();
    bool firsttime = true;
    bool display = true;
    bool process = true;
    while (process) {

        /*
        ** Invoke game callback.
        */
        if (Session.Type == GAME_NORMAL || Session.Type == GAME_SKIRMISH) {
            Call_Back();
        } else {
            if (Main_Loop()) {
                process = false;
                cancel = true;
            }
        }

        /*
        ** If we have just received input focus again after running in the background then
        ** we need to redraw.
        */
        if (AllSurfaces.SurfacesRestored) {
            AllSurfaces.SurfacesRestored = false;
            display = true;
        }

        /*
        ** Refresh display if needed.
        */
        if (display) {

            Hide_Mouse();
            /*
            ** Display the dialog box.
            */
            if (display) {
                Dialog_Box(d_dialog_x, d_dialog_y, d_dialog_w, d_dialog_h);
                Draw_Caption("Load Replay", d_dialog_x, d_dialog_y, d_dialog_w);
            }

            /*
            ** Redraw the buttons.
            */
            if (display) {
                commands->Flag_List_To_Redraw();
            }
            Show_Mouse();
            display = false;
        }

        /*
        ** Get user input.
        */
        KeyNumType input = commands->Input();

        /*
        ** The first time through the processing loop, set the edit
        ** gadget to have the focus if this is the save dialog. The
        ** focus must be set here since the gadget list has changed
        ** and this change will cause any previous focus setting to be
        ** cleared by the input processing routine.
        */
            firsttime = false;
            editbtn.Set_Focus();
            editbtn.Flag_To_Redraw();

        /*
        ** If the <RETURN> key was pressed, then default to the appropriate
        ** action button according to the style of this dialog box.
        */
        if (input == KN_RETURN || input == (BUTTON_EDIT | KN_BUTTON)) {
            ToggleClass* toggle = NULL;
                input = (KeyNumType)(BUTTON_LOAD | KN_BUTTON);
                cancelbtn.Turn_Off();
                toggle = (ToggleClass*)commands->Extract_Gadget(BUTTON_LOAD);
                if (toggle != NULL) {
                    toggle->IsOn = true;
                    toggle->IsPressed = true;
                }

            }
            Hide_Mouse();
            commands->Draw_All(true);
            Show_Mouse();
        

        /*
        ** Process input.
        */
        switch (input) {
        /*
        ** Load: if load fails, present a message, and stay in the dialog
        ** to allow the user to try another game
        */
        case (BUTTON_LOAD | KN_BUTTON):
            game_idx = listbtn.Current_Index();
            game_num = Files[game_idx]->Num;
            
            if (Files[game_idx]->Valid) {
                Session.RecordFile.Set_Name(listbtn.Current_Item());
                Session.Play = true;
                Session.Record = false;
                process = false;
            } else {
                WWMessageBox().Process(TXT_OBSOLETE_SAVEGAME);
            }
            break;

        /*
        ** ESC/Cancel: break
        */
        case (KN_ESC):
        case (BUTTON_CANCEL | KN_BUTTON):
            cancel = true;
            process = false;
            break;

        default:
            break;
        }

        Frame_Limiter();
    }

    Clear_List(&listbtn);

    if (cancel)
        return (false);

    return (true);
}

/***********************************************************************************************
 * LoadOptionsClass::Clear_List -- clears the list box & Files arrays                          *
 *                                                                                             *
 * This step is essential, because it frees all the strings allocated for list items.          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/14/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void LoadReplayClass::Clear_List(ListClass* list)
{
    /*
    ** For every item in the list, free its buffer & remove it from the list.
    */
    int j = list->Count();
    for (int i = 0; i < j; i++) {
        list->Remove_Item(list->Get_Item(0));
    }

    /*
    ** Clear the array of game numbers
    */
    for (int i = 0; i < Files.Count(); i++) {
        delete Files[i];
    }
    Files.Clear();
}

/***********************************************************************************************
 * LoadOptionsClass::Fill_List -- fills the list box & GameNum arrays                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/14/1995 BR : Created.                                                                  *
 *   06/25/1995 JLB : Shows which saved games are "(old)".                                     *
 *=============================================================================================*/
void LoadReplayClass::Fill_List(ListClass* list)
{
    ReplayFileEntryClass* fdata; // for adding entries to 'Files'
    char descr[DESCRIP_MAX + 32];
    unsigned scenario; // scenario #
    HousesType house;  // house
    Find_File_Data* ff = nullptr;
    int id = 0;

    /*
    ** Make sure the list is empty
    */
    Clear_List(list);

    /*
    ** Find all savegame files
    */
    bool rc = Find_First("*.REPLAY*", 0, &ff);

    while (rc) {


            /*
            ** Extract the game ID from the filename
            */
            id = id++;

            /*
            ** get the game's info; if success, add it to the list
            */
            
            //bool ok = Get_Savefile_Info(id, descr, &scenario, &house);
            // TODO implement replay file checking
            bool ok = true;


            fdata = new ReplayFileEntryClass;

            fdata->Descr[0] = '\0';
            
            if (!ok) {
               sprintf(fdata->Descr, "(%s) ", "Incompatible");
            }

            strncat(fdata->Descr, ff->GetName(), (sizeof(fdata->Descr) - strlen(fdata->Descr)) - 1);
            fdata->Valid = ok;
            fdata->Scenario = 0;  //scenario;
            fdata->House = (HousesType)0; //house;
            fdata->Num = id++;
            fdata->DateTime = ff->GetTime();
            Files.Add(fdata);

        /*
        ** Find the next file
        */
        rc = Find_Next(ff);
    }
    Find_Close(ff);


    /*
    ** Now sort the list in order of Date/Time (newest first, oldest last)
    */
    qsort((void*)(&Files[0]), Files.Count(), sizeof(class FileEntryClass*), LoadReplayClass::Compare);

    /*
    ** Now add every file's name to the list box
    */
    for (int i = 0; i < Files.Count(); i++) {
        list->Add_Item(Files[i]->Descr);
    }
}


/***********************************************************************************************
 * LoadOptionsClass::Compare -- for qsort                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      p1,p2      ptrs to elements to compare                                                 *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      0 = same, -1 = (*p1) goes BEFORE (*p2), 1 = (*p1) goes AFTER (*p2)                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/14/1995 BR : Created.                                                                  *
 *=============================================================================================*/
int LoadReplayClass::Compare(const void* p1, const void* p2)
{
    class ReplayFileEntryClass *fe1, *fe2;

    fe1 = *((class ReplayFileEntryClass**)p1);
    fe2 = *((class ReplayFileEntryClass**)p2);

    if (fe1->DateTime > fe2->DateTime)
        return (-1);
    if (fe1->DateTime < fe2->DateTime)
        return (1);
    return (0);
}
