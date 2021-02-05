#ifndef REPLAYDLG_H
#define REPLAYDLG_H

#include "defines.h"


class ReplayFileEntryClass
{
public:
    char Descr[80];         // save-game description
    unsigned Scenario;      // scenario #
    HousesType House;       // house
    int Num;                // save file number (from the extension)
    unsigned long DateTime; // date/time stamp of file
    bool Valid;             // Is the scenario valid?
};


class LoadReplayClass
{
public:
    /*
    ** This defines the style of the dialog
    */
    typedef enum OperationModeEnum
    {
        NONE = 0,
        LOAD,
        SAVE,
        WWDELETE
    } LoadStyleType;

    LoadReplayClass();
    ~LoadReplayClass();
    int Process(void);

protected:
    /*
    ** Internal routines
    */
    void Clear_List(ListClass* list);                   // clears the list & game # array
    void Fill_List(ListClass* list);                    // fills the list & game # array
    static int Compare(const void* p1, const void* p2); // for qsort()

    /*
    ** This is an array of pointers to FileEntryClass objects.  These objects
    ** are allocated on the fly as files are found, and pointers to them are
    ** added to the vector list.  Thus, all the objects must be free'd before
    ** the vector list is cleared.  This list is used for sorting the files
    ** by date/time.
    */
    DynamicVectorClass<ReplayFileEntryClass*> Files;
};

#endif
