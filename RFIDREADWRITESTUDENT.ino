#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

MFRC522::MIFARE_Key key;

/**
 * Initialize.
 */
void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    Serial.println("Scan a MIFARE Classic PICC to demonstrate read and write.");
    Serial.print("Using key (for A and B):");
    dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
    Serial.println();
    
    Serial.println("BEWARE: Data will be written to the PICC, in sector #1");
}

/**
 * Main loop.
 */
void loop() {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    // Show some details of the PICC (that is: the tag/card)
    Serial.print("Card UID:");
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print("PICC type: ");
    byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    // Check for compatibility
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println("This sample only works with MIFARE Classic cards.");
        return;
    }

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//																									//
	// Read METHODS																				    	//
	//																									//
	//////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////
	// Sector 1 //
	//////////////

    byte sector         = 1;
    byte blockAddr      = 4;
    byte trailerBlock   = 7;
    byte status;
    byte buffer[18];
    byte size = sizeof(buffer);

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	//////////////
	// Sector 2 //
	//////////////
	sector         = 2;
    blockAddr      = 8;
    trailerBlock   = 11;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	//////////////
	// Sector 3 //
	//////////////
	sector         = 3;
    blockAddr      = 12;
    trailerBlock   = 15;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	//////////////
	// Sector 4 //
	//////////////
	sector         = 4;
    blockAddr      = 16;
    trailerBlock   = 19;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	//////////////
	// Sector 5 //
	//////////////
	sector         = 5;
    blockAddr      = 20;
    trailerBlock   = 23;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	//////////////
	// Sector 6 //
	//////////////
	sector         = 6;
    blockAddr      = 24;
    trailerBlock   = 27;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	//////////////
	// Sector 7 //
	//////////////
	sector         = 7;
    blockAddr      = 28;
    trailerBlock   = 31;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	//////////////
	// Sector 8 //
	//////////////
	sector         = 8;
    blockAddr      = 32;
    trailerBlock   = 35;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	//////////////
	// Sector 9 //
	//////////////
	sector         = 9;
    blockAddr      = 36;
    trailerBlock   = 39;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	///////////////
	// Sector 10 //
	///////////////
	sector         = 10;
    blockAddr      = 40;
    trailerBlock   = 43;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	///////////////
	// Sector 11 //
	///////////////
	sector         = 11;
    blockAddr      = 44;
    trailerBlock   = 47;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

	///////////////
	// Sector 12 //
	///////////////
	sector         = 12;
    blockAddr      = 48;
    trailerBlock   = 51;

    // Authenticate using key A
    Serial.println("Authenticating using key A...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    // Read data from the block
    Serial.print("Reading data from block "); Serial.print(blockAddr);
    Serial.println(" ...");
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print("MIFARE_Read() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
    Serial.print("Data in block "); Serial.print(blockAddr); Serial.println(":");
    dump_byte_array(buffer, 16); Serial.println();
    Serial.println();

    // Authenticate using key B
    Serial.println("Authenticating again using key B...");
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        Serial.print("PCD_Authenticate() failed: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }


	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//																									//
	// WRITE METHODS																					//
	//																									//
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	// Write Block 1
        byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 1, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 1;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");
  
		// Write Block 2
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 2, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 2;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 3
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 3, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 3;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 4
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 4, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 4;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 5
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 5, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 5;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 6
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 6, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 6;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 7
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 7, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 7;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 8
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 8, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 8;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 2
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 9, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 9;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 10
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 10, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 10;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 11
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 11, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 11;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block 
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

		// Write Block 12
		byte buffer[128];  
        byte block;
        byte status, len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: Family name
        Serial.println("Waiting For Question 12, ending with ?");
        len=Serial.readBytesUntil('?', (char *) buffer, 128) ; // read family name from serial
        for (byte i = len; i < 128; i++) buffer[i] = '\s';     // pad with spaces
        
        block = 12;
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print("PCD_Authenticate() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        
        // Write block 
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print("MIFARE_Write() failed: ");
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println("MIFARE_Write() success: ");

    // Dump the sector data
    Serial.println("Current data in sector:");
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
    Serial.println();

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}