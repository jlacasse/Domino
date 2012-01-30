#include "Souliss.h"
#include "Typicals.h"
#include "MaCaco.h"
#include <WProgram.h>

#include "TypicalIrCommander.h"
#include "IRremote_light.h"
#include "IRremoteInt_light.h"

#define DEBUG 1

IRsend irsend;

/**************************************************************************
/*!
	Define the use of Typical IrCom : IR LED commander(1DI, 1 DO)
*/	
/**************************************************************************/
void Souliss_SetT_IrCom(U8 *memory_map, U8 slot)
{
	memory_map[MaCaco_TYP_s + slot] = Souliss_T_IrCom;
}

/**************************************************************************
/*!
	Typical IrCom : IR LED commander(1DI, 1 DO)
	
	many commands available, see 
	TypicalIrCommander.h ->#define Souliss_T_IrCom_WMC_

	
	The command value shall be placed in MaCaco_IN_s + slot, this can be
	done using the Souliss_DigIn or Souliss_RemoteInput.		
	
*/	
/**************************************************************************/
short toggle = 0;
//unsigned long long Souliss_T_IrCom_Reset = 0xc800F0400LL;
void Souliss_Logic_T_IrCom(U8 *memory_map, U8 slot, U8 *trigger)
{
	// Look for base IR value, add the command
	unsigned long long TOnOff = Souliss_T_IrCom_WMC_IRBase;
	if(memory_map[MaCaco_IN_s + slot] != Souliss_T_IrCom_Reset)		// Memory value is used as timer
	{	
	#ifdef DEBUG
	Serial.print("WMC Command: ");
	Serial.println(memory_map[MaCaco_IN_s + slot],HEX );
	#endif
		if(memory_map[MaCaco_OUT_s + slot] != memory_map[MaCaco_IN_s + slot])  
			*trigger = Souliss_TRIGGED;	// Trig change
		
		//check intervallo comandi 
		if (memory_map[MaCaco_IN_s + slot] >= Souliss_T_IrCom_WMC_Prog_0 && memory_map[MaCaco_IN_s + slot] <= Souliss_T_IrCom_WMC_Photo)	
		{//Windows Media Center
		//add the command to default WMC mask: 0xc800F0400LL
		TOnOff = TOnOff ^ memory_map[MaCaco_IN_s + slot];
		
			//RC6 protocol toggle
		  if (toggle == 0) {
			irsend.sendRC6(TOnOff, WMC_BITS);
		  } else {
			irsend.sendRC6(TOnOff ^ 0x8000, WMC_BITS);
		  }
		  toggle = 1 - toggle;
		
		}
		//Samsung Aircon	(0xF0 to 0xFF) 64bit codes 71-TEMP-FUN-F0
		else if (memory_map[MaCaco_IN_s + slot] >= 0xF0 && memory_map[MaCaco_IN_s + slot] <= 0xFF)	
		{
			;//TODO IRSendSamsung
		}
		
		//add your device here:
		//else if (memory_map[MaCaco_IN_s + slot] >= Souliss_T_IrCom_DEVICE_FIRST_COMMAND && memory_map[MaCaco_IN_s + slot] <= Souliss_T_IrCom_DEVICE_LAST_COMMAND)	
		//{}
				
				
		memory_map[MaCaco_OUT_s + slot] = memory_map[MaCaco_IN_s + slot];	
		memory_map[MaCaco_IN_s + slot] = Souliss_T_IrCom_Reset;			// Reset

	}
}
