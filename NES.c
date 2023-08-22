#include <6502.h>


// CPU Custom Memory Addresses, Hints for where values should be stored at to save up on performance
#define LOOP1			(*(volatile unsigned char*)0x00)
#define LOOP2			(*(volatile unsigned char*)0x01)
#define LOOP3			(*(volatile unsigned char*)0x02)
#define LOOP3_MOST		(*(volatile unsigned char*)0x03)
#define LOOP3_LEAST		(*(volatile unsigned char*)0x04)

#define PPU_SCROLL_X			(*(volatile unsigned char*)0x05)
#define PPU_SCROLL_Y			(*(volatile unsigned char*)0x06)
#define PPU_POINTER				(*(volatile unsigned char*)0x07)
#define PPU_STORED_DATA 		(*(volatile unsigned char*)0x08)
#define PPU_STORED_DATA_COMPARE (*(volatile unsigned char*)0x09)

#define STORED_INT				(*(volatile unsigned char*)0x10)
#define STORED_INT_COMPARE		(*(volatile unsigned char*)0x11)
#define STORED_INT2				(*(volatile unsigned char*)0x12)
#define STORED_INT_COMPARE2 	(*(volatile unsigned char*)0x13)

#define CTRL_STORE_BUFFER		(*(volatile unsigned char*)0x14)
#define CTRL_STORE				(*(volatile unsigned char*)0x15)
#define CTRL_PRESSED_BUFFER 	(*(volatile unsigned char*)0x16)
#define PPU_STATUS_MOST			(*(volatile unsigned char*)0x17)

#define BPS			(*(volatile unsigned char*)0x50) // BACKGROUND POINTER STORE
#define BPS2		(*(volatile unsigned char*)0x51) // BACKGROUND POINTER STORE 2

#define PL1_X		(*(volatile unsigned char*)0x6100) // PLAYER1 X
#define PL1_S		(*(volatile unsigned char*)0x6101) // PLAYER1 SPRITE
#define PL1_P		(*(volatile unsigned char*)0x6102) // PLAYER1 PALETTE
#define PL1_Y		(*(volatile unsigned char*)0x6103) // PLAYER1 Y
#define PL1_CHANGED (*(volatile unsigned char*)0x6104) // PLAYER CHANGED CHECK



// CPU Memory Addresses
#define PPU_MASK		(*(volatile unsigned char*)0x2001)
#define PPU_STATUS		(*(volatile unsigned char*)0x2002)
#define OAM_ADDR		(*(volatile unsigned char*)0x2003)
#define OAM_DATA		(*(volatile unsigned char*)0x2004)
#define PPU_ADDR		(*(volatile unsigned char*)0x2006)
#define PPU_DATA		(*(volatile unsigned char*)0x2007)
#define SPRITE_DMA		(*(volatile unsigned char*)0x4014)
#define CTRL1			(*(volatile unsigned char*)0x4016)



// PPU Memory Addresses
	//PATTERN_TABLE0		$0000 - $0FFF | $1000 Bytes
	//PATTERN_TABLE1		$1000 - $1FFF | $1000 Bytes
	//NAMETABLE0			$2000 - $23BF | $0370 Bytes
	//NAMETABLE0_PALETTE	$23C0 - $23FF | $0030 Bytes
	//NAMETABLE1			$2400 - $27BF | $0370 Bytes
	//NAMETABLE1_PALETTE	$23C0 - $23FF | $0030 Bytes
	//NAMETABLE2			$2800 - $2BBF | $0370 Bytes
	//NAMETABLE2_PALETTE	$23C0 - $23FF | $0030 Bytes
	//NAMETABLE3			$2C00 - $2FBF | $0370 Bytes
	//NAMETABLE3_PALETTE	$23C0 - $23FF | $0030 Bytes
	//MIRRORS				$3000 - $3EFF | $0F00 Bytes
	//PALETTE_ADDR			$3F00 - $3F1F | $0020 Bytes
	//MIRRORS				$3F20 - $3FFF | $00E0 Bytes

// ROM Memory Addresses
	//PAL ROM	$FC00 - $FC0F | $15 Bytes

// A :		10000000 0x80
// B :		01000000 0x40
// Select :	00100000 0x20
// Start :	00010000 0x10
// Up :		00001000 0x08
// Down :	00000100 0x04
// Left :	00000010 0x02
// Right :	00000001 0x01



int main(void) {
	struct regs r;
	unsigned char MEM_POINTER;

	PL1_CHANGED = 0x1;

	PL1_X = 0x20;
	PL1_S = 0x1A;
	PL1_P = 0x02;
	PL1_Y = 0x20;


	// TEST DRAWING BEGIN
	
	//WIP CODE
	
	
	
	//END WIP

	for (BPS = 0x00; BPS < 0xFF; BPS++) { // Loop for $F000 - $F0FF
		MEM_POINTER = *((unsigned char*)0xF000 + BPS);
		PPU_ADDR = 0x20;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
	for (BPS = 0x00; BPS < 0xFF; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF100 + BPS);
		PPU_ADDR = 0x21;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
	for (BPS = 0x00; BPS < 0xFF; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF200 + BPS);
		PPU_ADDR = 0x22;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
	for (BPS = 0x00; BPS < 0xC0; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF300 + BPS);
		PPU_ADDR = 0x23;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
	
	// END TEST DRAWING


	PPU_STORED_DATA_COMPARE = 0x0;
	STORED_INT_COMPARE = 0x01;
	STORED_INT_COMPARE2 = 0x01;

	// For loop for getting PAL memory into NES.
	for (BPS = 0xBF; BPS != 0x10; BPS++) {
		MEM_POINTER = *((unsigned char*)0xFC00 + BPS);
		PPU_ADDR = 0x3F;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}

	// Shifting Camera to $2000
	PPU_ADDR = 0x20;
	PPU_ADDR = 0x0;
	PPU_DATA = 0x0;

	// Show sprites and background
	PPU_MASK = 0x1A; // 00011010
	
	while (1) {

		// Get controller input
		CTRL1 = 0x01;
		CTRL1 = 0x00;
		for (r.a = 0; r.a != 8; r.a++) {
			CTRL_STORE_BUFFER = (CTRL1 & 0x1); // Saves the first bit of CTRL1
			CTRL_STORE = (CTRL_STORE << 1); // Shifts all the bits of CTRL_STORE once
			CTRL_STORE = CTRL_STORE | CTRL_STORE_BUFFER; // Apply the bytes from CTRL_STORE with CTRL_STORE_BUFFER
		}


		if (CTRL_STORE == 0x80) { // If pressing A
			if (CTRL_PRESSED_BUFFER != CTRL_STORE) { // Used to stop visual glitches


				CTRL_PRESSED_BUFFER = CTRL_STORE;
			}
		}
		else if (CTRL_STORE == 0x40) { // If pressing B
			if (CTRL_PRESSED_BUFFER != CTRL_STORE) {


				CTRL_PRESSED_BUFFER = CTRL_STORE;
			}
		}
		else if (CTRL_STORE == 0x01) { // If pressing Right
			if (CTRL_PRESSED_BUFFER != CTRL_STORE) {
				PL1_X++;
				PL1_CHANGED++;
				CTRL_PRESSED_BUFFER = CTRL_STORE;
			}
		}
		else if (CTRL_STORE == 0x02) {
			if (CTRL_PRESSED_BUFFER != CTRL_STORE) { // If pressing Left


				CTRL_PRESSED_BUFFER = CTRL_STORE;
			}
		}
		else if (CTRL_STORE == 0x04) { // If pressing Down
			if (CTRL_PRESSED_BUFFER != CTRL_STORE) {


				CTRL_PRESSED_BUFFER = CTRL_STORE;
			}
		}
		else if (CTRL_STORE == 0x08) { // If pressing Up
			if (CTRL_PRESSED_BUFFER != CTRL_STORE) {


				CTRL_PRESSED_BUFFER = CTRL_STORE;
			}
		}
		else {
			CTRL_PRESSED_BUFFER = 0x0;
			CTRL_STORE = 0x0;
		}

		if (PL1_CHANGED != 0x0) {
			PPU_MASK = 0x0;
			SPRITE_DMA = 0x61;
			PPU_MASK = 0x1A;
			PL1_CHANGED = 0x0;
		}
	}

	return 0;
}