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

/* $Header: /CounterStrike/CCINI.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : CCINI.H                                                      *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 05/24/96                                                     *
 *                                                                                             *
 *                  Last Update : May 24, 1996 [JLB]                                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef CCINI_H
#define CCINI_H

#include "ini.h"
#include "fixed.h"

class TriggerTypeClass;
class BuildingTypeClass;

/*
**	The advanced version of the INI database manager. It handles the C&C expansion types and
**	identifiers. In addition, it automatically stores a message digest with the INI data
**	so that verification can occur.
*/
class CCINIClass : public INIClass
{
public:
    CCINIClass(void)
        : IsDigestPresent(false)
    {
    }

    bool Load(FileClass& file, bool withdigest);
    int Load(Straw& file, bool withdigest);
    int Save(FileClass& file, bool withdigest) const;
    int Save(Pipe& pipe, bool withdigest) const;

    void Get_Buildings(char const* section,
                       char const* entry,
                       DynamicVectorClass<StructType>& dest,
                       const DynamicVectorClass<StructType> defvalue) const;
    UnitType Get_UnitType(char const* section, char const* entry, UnitType defvalue) const;
    AnimType Get_AnimType(char const* section, char const* entry, AnimType defvalue) const;
    ArmorType Get_ArmorType(char const* section, char const* entry, ArmorType defvalue) const;
    BulletType Get_BulletType(char const* section, char const* entry, BulletType defvalue) const;
    HousesType Get_HousesType(char const* section, char const* entry, HousesType defvalue) const;
    void Get_Building_States_Anim_List(char const* section, DynamicVectorClass<AnimControlType*>& vec);
    LEPTON Get_Lepton(char const* section, char const* entry, LEPTON defvalue) const;
    MPHType Get_MPHType(char const* section, char const* entry, MPHType defvalue) const;
    OverlayType Get_OverlayType(char const* section, char const* entry, OverlayType defvalue) const;
    SourceType Get_SourceType(char const* section, char const* entry, SourceType defvalue) const;
    TerrainType Get_TerrainType(char const* section, char const* entry, TerrainType defvalue) const;
    TheaterType Get_TheaterType(char const* section, char const* entry, TheaterType defvalue) const;
    ThemeType Get_ThemeType(char const* section, char const* entry, ThemeType defvalue) const;
    TriggerTypeClass* Get_TriggerType(char const* section, char const* entry) const;
    VQType Get_VQType(char const* section, char const* entry, VQType defvalue) const;
    VocType Get_VocType(char const* section, char const* entry, VocType defvalue) const;
    WarheadType Get_WarheadType(char const* section, char const* entry, WarheadType defvalue) const;
    WeaponType Get_WeaponType(char const* section, char const* entry, WeaponType defvalue) const;
    long Get_Owners(char const* section, char const* entry, long defvalue) const;
    void Get_Owners(char const* section,
                    char const* entry,
                    DynamicVectorClass<std::string>& vec,
                    DynamicVectorClass<std::string> defvalue) const;
    CrateType Get_CrateType(char const* section, char const* entry, CrateType defvalue) const;
    MissionType Get_MissionType(char const* section, char const* entry, MissionType defvalue) const;
    StructType Get_StructType(char const* section, char const* entry, StructType defvalue) const;
    COORDINATE Get_Coordinate_From_Pixels(char const* section, char const* entry, COORDINATE defvalue) const;
    short const* Get_Cell_List(char const* section, char const* entry, short const* defvalue) const;
    RTTIType Get_RTTIType(char const* section, char const* entry, RTTIType defvalue) const;
    FacingType Get_FacingType(char const* section, char const* entry, FacingType defvalue) const;
    void Get_Infantry_Do_Controls_List(char const* section, DynamicVectorClass<DoInfoStruct*>& vec);
    LandType Get_LandType(char const* section, char const* entry, LandType defvalue) const;
    short const* Get_Cell_List(char const* section, char const* entry, short const* defvalue, int defvaluesize);

    bool Put_Building_States_Anim_List(char const* section, DynamicVectorClass<AnimControlType*>& vec);
    bool Put_Infantry_Do_Controls_List(char const* section, DynamicVectorClass<DoInfoStruct*>& vec);
    bool Put_Buildings(char const* section, char const* entry, const DynamicVectorClass<StructType>& value);
    bool Put_RTTIType(char const* section, char const* entry, RTTIType value);
    bool Put_FacingType(char const* section, char const* entry, FacingType value);
    bool Put_StructType(char const* section, char const* entry, StructType value);
    bool Put_AnimType(char const* section, char const* entry, AnimType value);
    bool Put_UnitType(char const* section, char const* entry, UnitType value);
    bool Put_ArmorType(char const* section, char const* entry, ArmorType value);
    bool Put_BulletType(char const* section, char const* entry, BulletType value);
    bool Put_HousesType(char const* section, char const* entry, HousesType value);
    bool Put_Lepton(char const* section, char const* entry, LEPTON value);
    bool Put_MPHType(char const* section, char const* entry, MPHType value);
    bool Put_VQType(char const* section, char const* entry, VQType value);
    bool Put_OverlayType(char const* section, char const* entry, OverlayType value);
    bool Put_Owners(char const* section, char const* entry, DynamicVectorClass<std::string> Owners);
    bool Put_SourceType(char const* section, char const* entry, SourceType value);
    bool Put_TerrainType(char const* section, char const* entry, TerrainType value);
    bool Put_TheaterType(char const* section, char const* entry, TheaterType value);
    bool Put_ThemeType(char const* section, char const* entry, ThemeType value);
    bool Put_TriggerType(char const* section, char const* entry, TriggerTypeClass* value);
    bool Put_VocType(char const* section, char const* entry, VocType value);
    bool Put_WarheadType(char const* section, char const* entry, WarheadType value);
    bool Put_WeaponType(char const* section, char const* entry, const WeaponType value);
    bool Put_Cell_List(char const* section, char const* entry, short const* value);
    bool Put_CrateType(char const* section, char const* entry, CrateType value);
    bool Put_MissionType(char const* section, char const* entry, MissionType value);
    bool Put_Coordinate_Pixels(char const* section, char const* entry, COORDINATE value);

    int Get_Unique_ID(void) const;

private:
    void Calculate_Message_Digest(void);
    void Invalidate_Message_Digest(void);

    bool IsDigestPresent : 1;

    /*
    **	This is the message digest (SHA) of the INI database that was embedded as part of
    **	the INI file.
    */
    unsigned char Digest[20];
};

#endif
