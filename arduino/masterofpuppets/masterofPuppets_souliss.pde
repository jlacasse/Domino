#include <memoryfree.h>

/**************************************************************************
	Souliss Home Automation - Example 7 (IR Devices)
	
	A basic Souliss configuration, with a single node based on
        Arduino ethernet. The board commands a IR LED connected to PIN 3
        
        TypicalIrCommander.h is used to define devices.
	
	Applicable for : 
			- TVs,
			- Stereo systems.
                        - Air Conditioners
	
	The Local Device has
		- A IR LED on Pin 3
		- A debug LED on pin 4
		
 
	*************************Definitions*************************
	Configuration file		Parameter
	vNet_Config.h			#define VNET_SUPERNODE  0
	vNet_Config.h			#define VNET_MEDIA1_ENABLE  1
	vNet_Config.h			#define VNET_MEDIA2_ENABLE  0
	vNet_Config.h			#define VNET_MEDIA3_ENABLE  0
	vNet_Config.h			#define VNET_MEDIA4_ENABLE  0
	vNet_Config.h			#define VNET_MEDIA5_ENABLE  0

	ethUsrCfg.h				#define ETH_CLASS   		1	
	ethUsrCfg.h				const uint8_t DEFAULT_BASEIPADDRESS[] = {...}
	ethUsrCfg.h				const uint8_t DEFAULT_SUBMASK[]       = {...}
	ethUsrCfg.h				const uint8_t DEFAULT_GATEWAY[]       = {...}
	ethUsrCfg.h				const uint8_t MAC_ADDRESS[]           = {...}		
	
	It's important define the proper MAC address for each board, two nodes
	that share the same MAC address will not communicate. You can found a
	proper MAC address on the sticker behind the board.
		
***************************************************************************/
#include "Souliss.h"
#include "Typicals.h"
#include "MaCaco.h"
#include "vNet.h"
#include <IRremote_light.h>
#include <SPI.h>

#include "TypicalIrCommander.h"
#include "SoulissJSONServer.h"

#define network_address_1	0x00B1
#define network_my_subnet	0xFF00
#define network_my_supern	0x0000

#define time_base 			10				// Time cycle in milliseconds
#define num_phases			100				// Number of phases

#define USED_SLOT1_N1			0			// This is the memory slot used for the execution of the logic in network_address1
#define USED_SLOT1_N2			0			// This is the memory slot used for the execution of the logic in network_address2
#define USED_SLOT2_N1			1			// This is the memory slot used for the execution of the logic in network_address1
#define USED_SLOT2_N2			1			// This is the memory slot used for the execution of the logic in network_address2

#define JSON_LOCAL_ID			0			// This ID identify local data in JSON memory map
#define NODE_NUM				1			// Number of nodes with output states

// define the shared memory map
U8 memory_map[MaCaco_MEMMAP] = {0x00};
U8 json_memory_map[MaCaco_TYPLEN+MaCaco_SUBSCRLEN] = {0x00};

// flag 
U8 data_changed = 0;
U8 healty = 0x25, count = 0;

U8 phase=0;
unsigned long tmr=0;  

void setup()
{	
        Serial.begin(115200);
	// Setup the network configuration
	//
	//	The vNet address is 11(hex) that is 17(dec), so the IP address is
	//	the base IP address with 17 as last octect (ex. 192.168.0.17)
	Souliss_SetAddress(network_address_1, network_my_subnet, network_my_supern);		

	// Set the typical to use in slot 0 and 1
	Souliss_SetT12(memory_map, USED_SLOT1_N1);
	Souliss_SetT_IrCom(memory_map, USED_SLOT2_N1);
	
	// Define inputs, outputs pins
	//pinMode(6, INPUT);	// Hardware pulldown required
	//pinMode(4, INPUT);	// Hardware pulldown required
        //digitalWrite(4,LOW);
        //digitalWrite(6,LOW);
	
	//pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
        Serial.println(freeMemory());
}

void loop()
{ 
  
	if(abs(millis()-tmr) > time_base)
	{	
		tmr = millis();
		phase = (phase + 1) % num_phases;

		// Execute the code every time_base
		if (!(phase % 1))
		{                 
		} 
	  
		// Execute the code every 2 time_base		
		if (!(phase % 2))
		{
			// Use Pin2 as ON/OFF command
			//Souliss_DigIn(6, Souliss_T12_Cmd, memory_map, USED_SLOT1_N1);			

			// Use Pin3 as ON/OFF command
			//Souliss_DigIn(6, Souliss_T12_Cmd, memory_map, USED_SLOT2_N1);			
			
			// Execute the logic
			//Souliss_Logic_T12(memory_map, USED_SLOT1_N1, &data_changed);
                        Souliss_Logic_T_IrCom(memory_map, USED_SLOT2_N1, &data_changed);

			// Use Pin9 as output on the electrical load
			//Souliss_DigOut(3, Souliss_T12_Coil, memory_map, USED_SLOT2_N1);	

			if(memory_map[MaCaco_IN_s + USED_SLOT2_N1] != Souliss_T_IrCom_Reset)
			{
                          digitalWrite(5, HIGH);
                        }
			
		} 
		
		// Execute the code every 5 time_base		  
		if (!(phase % 5))
		{   
			// Retreive data from the communication channel
			Souliss_SerialData(memory_map, &data_changed);
			
			// Place data from local memory_map to json_memory_map
			SoulissJSON_LocalToSharedMap(memory_map, json_memory_map, JSON_LOCAL_ID);
			
			// Parse and reply to HTTP/JSON request
			SoulissJSONServer(memory_map, json_memory_map, JSON_LOCAL_ID, NULL, NULL, NODE_NUM);				
		}

		// Execute the code every 10 time_base		  
		if (!(phase % 10))
		{   
		}		
		
		// Execute the code every 20 time_base		  
		if (!(phase % 20))
		{   
		}		
		
		// Execute the code every 50 time_base		  
		if (!(phase % 50))
		{
			// The timer handle timed-on states
			Souliss_T12_Timer(memory_map, USED_SLOT1_N1);
			//Souliss_T12_Timer(memory_map, USED_SLOT2_N1);		
		}		
		
		// Execute the code every 100 time_base		 
		if (!(phase % 500))
		{
                 Serial.println(freeMemory());
                 if(memory_map[MaCaco_IN_s + USED_SLOT2_N1] == Souliss_T_IrCom_Reset)
			{
                          digitalWrite(5, LOW);
                        }
		}
	}	
} 
