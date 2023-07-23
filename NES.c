#include <6502.h>


// CPU Custom Memory Addresses, Hints for where values should be stored at to save up on performance
#define LOOP1			(*(volatile unsigned char*)0x00)
#define LOOP2			(*(volatile unsigned char*)0x01)
#define LOOP3			(*(volatile unsigned char*)0x02)
#define LOOP3_MOST		(*(volatile unsigned char*)0x03)
#define LOOP3_LEAST		(*(volatile unsigned char*)0x04)

#define PPU_SCROLL_X (*(volatile unsigned char*)0x05)
#define PPU_SCROLL_Y (x(volatile unsigned char*)0x06)

#define STORED_INT			(*(volatile unsigned char*)0x10)
#define STORED_INT_COMPARE	(*(volatile unsigned char*)0x11)
#define STORED_INT2			(*(volatile unsigned char*)0x12)
#define STORED_INT_COMPARE2 (*(volatile unsigned char*)0x13)

#define CTRL_STORE_BUFFER	(*(volatile unsigned char*)0x14)
#define CTRL_STORE			(*(volatile unsigned char*)0x15)
#define CTRL_PRESSED_BUFFER (*(volatile unsigned char*)0x16)


// CPU Memory Addresses
#define PPU_MASK		(*(volatile unsigned char*)0x2001)
#define PPU_STATUS		(*(volatile unsigned char*)0x2002)
#define PPU_STATUS_MOST (*(volatile unsigned char*)0x17)
#define OAM_ADDR		(*(volatile unsigned char*)0x2003)
#define OAM_DATA		(*(volatile unsigned char*)0x2004)
#define PPU_ADDR		(*(volatile unsigned char*)0x2006)
#define PPU_DATA		(*(volatile unsigned char*)0x2007)
#define SPRITE_DMA		(*(volatile unsigned char*)0x4014)
#define CTRL1			(*(volatile unsigned char*)0x4016)

#define SPRITE1_Y		(*(volatile unsigned char*)0x8F00)
#define SPRITE1_SPR		(*(volatile unsigned char*)0x8F01)
#define SPRITE1_PAL		(*(volatile unsigned char*)0x8F02)
#define SPRITE1_X		(*(volatile unsigned char*)0x8F03)



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

// A :		10000000
// B :		01000000
// Select :	00100000
// Start :	00010000
// Up :		00001000
// Down :	00000100
// Left :	00000010
// Right :	00000001


int main(void) {
	struct regs r;
	unsigned char sprite1_x_most;
	unsigned char sprite1_x_least;

	STORED_INT_COMPARE = 0x01;
	STORED_INT_COMPARE2 = 0x01;

	// Begin changing the background color
	PPU_ADDR = 0x3F;
	PPU_ADDR = 0x00;
	PPU_DATA = 0x30;

	PPU_ADDR = 0x3F;
	PPU_ADDR = 0x01;
	PPU_DATA = 0x3F;

	// Changing Sprite PAL
	PPU_ADDR = 0x3F;
	PPU_ADDR = 0x11;
	PPU_DATA = 0x30; // White

	PPU_ADDR = 0x3F;
	PPU_ADDR = 0x12;
	PPU_DATA = 0x12; // Blue

	PPU_ADDR = 0x3F;
	PPU_ADDR = 0x13;
	PPU_DATA = 0x3F; // Black

	SPRITE_DMA = 0x8F;

	// Show sprites and background
	PPU_MASK = 0x18;
	
	while (1) {
		LOOP3_MOST = ((LOOP3 >> 4) & 0xF); // ((VALUE >> 4) & 0xF) - Most Significant
		LOOP3_LEAST = (LOOP3 & 0xF); // (VALUE & 0xF) - Least Significant

		// LOOP1++;

		// Incerments for the LOOPs
		if (LOOP1 == 0xFF) {
			LOOP2++;
		}
		if (LOOP2 == 0x40) {
			LOOP3++;
			LOOP2 = 0x00;
		}

		// Get controller input
		CTRL1 = 0x01;
		CTRL1 = 0x00;
		for (r.a = 0; r.a != 8; r.a++) {
			CTRL_STORE_BUFFER = (CTRL1 & 0x1);
			CTRL_STORE = (CTRL_STORE << 1);
			CTRL_STORE = CTRL_STORE | CTRL_STORE_BUFFER;
		}

		//// If player pressed A
		//if (CTRL_STORE == 0x80) {
		//	if (CTRL_PRESSED_BUFFER != CTRL_STORE) {
		//		SPRITE1_X++;
		//		PPU_MASK = 0x0;
		//		PPU_ADDR = 0x
		//		PPU_MASK = 0x18;
		//		CTRL_PRESSED_BUFFER = CTRL_STORE;
		//	}
		//}
		//else if (CTRL_STORE == 0x0) {
		//	CTRL_PRESSED_BUFFER = 0xF;
		//}

		sprite1_x_most = ((SPRITE1_X >> 4) & 0xF);
		sprite1_x_least = (SPRITE1_X) & 0xF;

		// Counters for the X value on Sprite 1
		if (STORED_INT_COMPARE != sprite1_x_most) { // 0xX0
			PPU_MASK = 0x00;
			PPU_ADDR = 0x20;
			PPU_ADDR = 0xC4;
			PPU_DATA = sprite1_x_most;
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x01;
			PPU_DATA = 0x00;
			PPU_MASK = 0x18;
			STORED_INT_COMPARE = sprite1_x_most;
		}

		if (STORED_INT_COMPARE2 != sprite1_x_least) { // 0x0X
			PPU_MASK = 0x00;
			PPU_ADDR = 0x20;
			PPU_ADDR = 0xC3;
			PPU_DATA = sprite1_x_least;
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x01;
			PPU_DATA = 0x00;
			PPU_MASK = 0x18;
			STORED_INT_COMPARE2 = sprite1_x_least;
		}
	}

	return 0;
}