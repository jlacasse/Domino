/**************************************************************************
	Souliss Home Automation
    Copyright (C) 2011  Veseo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
	Originally developed by Dario Di Maio
		developed by shine@angelic.it
	
***************************************************************************/
/*!
    \file 
    \ingroup
*/
#ifndef TYP_IR_H
#define TYP_IR_H

#include "types.h"

#include "Typicals.h"


// Defines for Typical 22
#define Souliss_T_IrCom					33
#define Souliss_T_IrCom_Cmd				0x05
#define Souliss_T_IrCom_Reset			0x00
#define Souliss_T_IrCom_Timer_Val		0x15
#define Souliss_T_IrCom_Timer_Off		0x05
#define Souliss_T_IrCom_LimSwitch_Close	0x04
#define Souliss_T_IrCom_LimSwitch_Open	0x03

//Windows Media Center (0x00 to 0x49)
#define Souliss_T_IrCom_WMC_IRBase			0xc800F0400LL
#define Souliss_T_IrCom_WMC_Power			0x0c
#define Souliss_T_IrCom_WMC_WmcButton		0x0d
#define Souliss_T_IrCom_WMC_Prog_1		0x01
#define Souliss_T_IrCom_WMC_Prog_2		0x02
#define Souliss_T_IrCom_WMC_Prog_3		0x03
#define Souliss_T_IrCom_WMC_Prog_4		0x04
#define Souliss_T_IrCom_WMC_Prog_5		0x05
#define Souliss_T_IrCom_WMC_Prog_6		0x06
#define Souliss_T_IrCom_WMC_Prog_7		0x07
#define Souliss_T_IrCom_WMC_Prog_8		0x08
#define Souliss_T_IrCom_WMC_Prog_9		0x09
#define Souliss_T_IrCom_WMC_Prog_0		0x00
#define Souliss_T_IrCom_WMC_Volume_Up		0x10
#define Souliss_T_IrCom_WMC_Volume_Down		0x11
#define Souliss_T_IrCom_WMC_Prog_Up		0x12
#define Souliss_T_IrCom_WMC_Prog_Down	0x13
#define Souliss_T_IrCom_WMC_Forward		0x14
#define Souliss_T_IrCom_WMC_Rewind		0x15
#define Souliss_T_IrCom_WMC_Play		0x16
#define Souliss_T_IrCom_WMC_Rec			0x17
#define Souliss_T_IrCom_WMC_Pause		0x18
#define Souliss_T_IrCom_WMC_Stop		0x19
#define Souliss_T_IrCom_WMC_Ok			0x22
#define Souliss_T_IrCom_WMC_Back		0x23
#define Souliss_T_IrCom_WMC_TVPlay		0x25
#define Souliss_T_IrCom_WMC_TVList		0x26
#define Souliss_T_IrCom_WMC_Music		0x47
#define Souliss_T_IrCom_WMC_Photo		0x49

//Panasonic 
#define Souliss_T_IrCom_Panasonic_Stop 			0x40040538
#define Souliss_T_IrCom_Panasonic_Volume_Down 	0x40040500

//Samsung Aircon	(0xF0 to 0xFF) 64bit codes 71-TEMP-FUN-F0
#define Souliss_T_IrCom_Samsung_temp_16C			OxFF
#define Souliss_T_IrCom_Samsung_temp_20C			OxFD
#define Souliss_T_IrCom_Samsung_temp_24C			OxFE 
#define Souliss_T_IrCom_Samsung_Pow_On				OxF0 
#define Souliss_T_IrCom_Samsung_Pow_Off				OxFC
//TODO: fan high/med/low
#define Souliss_T_IrCom_Samsung_Fun_Auto			Ox4F 
#define Souliss_T_IrCom_Samsung_Fun_Dry				Ox7B
#define Souliss_T_IrCom_Samsung_Fun_Heat			Ox2D
#define Souliss_T_IrCom_Samsung_Fun_Cool			Ox77

#define Souliss_RstCmd				0x00
#define Souliss_NOTTRIGGED			0x00
#define Souliss_TRIGGED				0x01


void Souliss_SetT_IrCom(U8 *memory_map, U8 slot);
void Souliss_Logic_T_IrCom(U8 *memory_map, U8 slot, U8 *trigger);
/*
void Souliss_SetT31(U8 *memory_map, U8 slot);
void Souliss_Logic_T31(U8 *memory_map, U8 slot, U8 *trigger);
*/
#endif



