#include <6502.h>


// CPU Custom Memory Addresses
#define LOOP1 (*(volatile unsigned char*)0x00) // Can be used for the beginning before the while loop
#define LOOP2 (*(volatile unsigned char*)0x01)
#define LOOP2_MOST (*(volatile unsigned char*)0x02)
#define LOOP2_COMPARE (*(volatile unsigned char*)0x03)
#define LOOP3 (*(volatile unsigned char*)0x04)
#define LOOP3_MOST (*(volatile unsigned char*)0x05)
#define LOOP3_LEAST (*(volatile unsigned char*)0x06)
#define CTRL_STORE (*(volatile unsigned char*)0x10)
#define CTRL_STORE_BUFFER (*(volatile unsigned char*)0x11)
#define CTRL_PRESSED (*(volatile unsigned char*)0x12)
#define STORED_INT (*(volatile unsigned char*)0x13)
#define STORED_INT_COMPARE (*(volatile unsigned char*)0x14)
#define STORED_INT2 (*(volatile unsigned char*)0x15)
#define STORED_INT_COMPARE2 (*(volatile unsigned char*)0x16)


// CPU Memory Addresses
#define PPU_MASK (*(volatile unsigned char*)0x2001)
#define PPU_STATUS (*(volatile unsigned char*)0x2002)
#define PPU_STATUS_MOST (*(volatile unsigned char*)0x17)
#define OAM_ADDR (*(volatile unsigned char*)0x2003)
#define OAM_DATA (*(volatile unsigned char*)0x2004)
#define PPU_ADDR (*(volatile unsigned char*)0x2006)
#define PPU_DATA (*(volatile unsigned char*)0x2007)
#define SPRITE_DMA (*(volatile unsigned char*)0x4014)
#define CTRL1 (*(volatile unsigned char*)0x4016)

// PPU Memory Addresses
#define PATTERN_TABLE0 = 0x00 // $0000 - $0FFF | $1000 Bytes
#define PATTERN_TABLE1 = 0x10 // $1000 - $1FFF | $1000 Bytes
#define NAMETABLE0 = 0x20 // $2000 - $23FF | $0400 Bytes
#define NAMETABLE0_PALETTE = 0x23C0 // $23C0 - $23FF
#define NAMETABLE1 = 0x24 // $2400 - $27FF | $0400 Bytes
#define NAMETABLE2 = 0x28 // $2800 - $2BFF | $0400 Bytes
#define NAMETABLE3 = 0x2C // $2C00 - $2FFF | $0400 Bytes
#define MIRRORS_2000_2EFF = 0x30 // $3000 - $3EFF | $0F00 Bytes
#define PALETTE_ADDR = 0x3F // $3F00 - $3F1F | $0020 Bytes
#define MIRRORS_3F00_3F1F = 0x3F // $3F20 - $3FFF | $00E0 Bytes

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
	STORED_INT_COMPARE = 0x01;
	STORED_INT_COMPARE2 = 0x01;
	LOOP2_COMPARE = 0x09;

	// Begin changing the background color
	PPU_ADDR = 0x3F;
	PPU_ADDR = 0x00;
	PPU_DATA = 0x30;

	PPU_ADDR = 0x3F;
	PPU_ADDR = 0x01;
	PPU_DATA = 0x3F;

	// Show sprites and background
	PPU_MASK = 0x18;
	
	while (1) {
		LOOP3_MOST = ((LOOP3 >> 4) & 0xF); // ((VALUE >> 4) & 0xF) - Most Significant
		LOOP3_LEAST = (LOOP3 & 0xF); // (VALUE & 0xF) - Least Significant

		LOOP1++;

		// Incerments for the LOOPs
		if (LOOP1 == 0xFF) {
			LOOP2++;
		}
		if (LOOP2 == 0x40) {
			LOOP3++;
			LOOP2 = 0x00;
		}

		if (STORED_INT_COMPARE != LOOP3_LEAST) { // 0xX0
			PPU_MASK = 0x00;
			PPU_ADDR = 0x20;
			PPU_ADDR = 0xC4;
			PPU_DATA = LOOP3_LEAST;
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x01;
			PPU_DATA = 0x00;
			PPU_MASK = 0x18;
			STORED_INT_COMPARE = LOOP3_LEAST;
		}

		if (STORED_INT_COMPARE2 != LOOP3_MOST) { // 0x0X
			PPU_MASK = 0x00;
			PPU_ADDR = 0x20;
			PPU_ADDR = 0xC3;
			PPU_DATA = LOOP3_MOST;
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x01;
			PPU_DATA = 0x00;
			PPU_MASK = 0x18;
			STORED_INT_COMPARE2 = LOOP3_MOST;
		}

		PPU_MASK = 0x0;
		PPU_ADDR = 0x0;
		PPU_ADDR = 0x0;
		PPU_DATA = 0x0;
		PPU_MASK = 0x18;
	}

	return 0;
}

//void GetButtonPress() {
//	struct regs r;
//	CTRL1 = 0x01;
//	CTRL1 = 0x00;
//	for (r.a = 0; r.a != 8; r.a++) {
//		CTRL_STORE_BUFFER = (CTRL1 & 0x1);
//		CTRL_STORE = (CTRL_STORE << 1);
//		CTRL_STORE = CTRL_STORE | CTRL_STORE_BUFFER;
//	}
//}