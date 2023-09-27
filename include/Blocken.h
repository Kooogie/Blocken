#ifndef _BLOCKEN
#define _BLOCKEN

// CPU Custom Memory Addresses, Hints for where values should be stored at to save up on performance
#define LOOP1				(*(volatile unsigned char*)0x00)
#define LOOP2				(*(volatile unsigned char*)0x01)
#define LOOP3				(*(volatile unsigned char*)0x02)
#define LOOP4				(*(volatile unsigned char*)0x03)
#define LOOP5				(*(volatile unsigned char*)0x04)
#define LOOP6				(*(volatile unsigned char*)0x05)
#define LOOP_LEAST 			(*(volatile unsigned char*)0x06)
#define LOOP_MOST			(*(volatile unsigned char*)0x07)
#define LOOP_LEAST_COMPARE	(*(volatile unsigned char*)0x08)
#define LOOP_MOST_COMPARE	(*(volatile unsigned char*)0x09)
#define TEMP_LOOP			(*(volatile unsigned char*)0x0A)
#define TEMP_FORLOOP_COUNTER	(*(volatile unsigned char*)0x0B)

#define LOOP2_FLAG		(*(volatile unsigned char*)0x0B)
#define ACC				(*(volatile unsigned char*)0x0C)
#define LOOP2_FLAG2		(*(volatile unsigned char*)0x0D)
#define ACC2			(*(volatile unsigned char*)0x0E)

#define PPU_SCROLL_X		(*(volatile unsigned char*)0x20)
#define PPU_SCROLL_Y		(*(volatile unsigned char*)0x21)
#define PPU_VSYNC 			(*(volatile unsigned char*)0x22)

#define CTRL_STORE_BUFFER		(*(volatile unsigned char*)0x30)
#define CTRL_STORE				(*(volatile unsigned char*)0x31)
#define CTRL_OUTPUT				(*(volatile unsigned char*)0x32)
#define CTRL_STORE_MOST			(*(volatile unsigned char*)0x33)
#define CTRL_STORE_LEAST		(*(volatile unsigned char*)0x34)
#define CTRL_STORE_MOST_FLAG	(*(volatile unsigned char*)0x35)
#define CTRL_STORE_LEAST_FLAG	(*(volatile unsigned char*)0x36)

#define BPS			(*(volatile unsigned char*)0x40) // BACKGROUND POINTER STORE
#define BPS_LOOP	(*(volatile unsigned char*)0x41) // BACKGROUND POINTER STORE LOOP
#define BPS2		(*(volatile unsigned char*)0x42) // BACKGROUND POINTER STORE 2
#define DRAW_FLAG	(*(volatile unsigned char*)0x43) // FLAG FOR DRAWING

#define MEM_POINTER_STORE (*(volatile unsigned char*)0x50)

#define SPRITE_Y	(*(volatile unsigned char*)0x6010)
#define SPRITE		(*(volatile unsigned char*)0x6011)
#define SPRITE_PAL	(*(volatile unsigned char*)0x6012)
#define SPRITE_X	(*(volatile unsigned char*)0x6013)
#define SPRITE_Y2	(*(volatile unsigned char*)0x6014)
#define SPRITE2		(*(volatile unsigned char*)0x6015)
#define SPRITE_PAL2	(*(volatile unsigned char*)0x6016)
#define SPRITE_X2	(*(volatile unsigned char*)0x6017)

// CPU CUSTOM POINTERS MEMORY USED: 0.034KBs



// CPU Memory Addresses
#define PPU_CTRL	(*(volatile unsigned char*)0x2000)
#define PPU_MASK	(*(volatile unsigned char*)0x2001)
#define PPU_STATUS	(*(volatile unsigned char*)0x2002)
#define OAM_ADDR	(*(volatile unsigned char*)0x2003)
#define OAM_DATA	(*(volatile unsigned char*)0x2004)
#define PPU_SCROLL	(*(volatile unsigned char*)0x2005)
#define PPU_ADDR	(*(volatile unsigned char*)0x2006)
#define PPU_DATA	(*(volatile unsigned char*)0x2007)

#define SPRITE_DMA	(*(volatile unsigned char*)0x4014)
#define CTRL1		(*(volatile unsigned char*)0x4016)



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

// Custom ROM Memory Addresses
	//PPU META MAPPING		$E000 - $E0FF | $255 Bytes
	//PPU MEMORY DUMP		$F010 - $F3AF | $944 Bytes
	//PPU PAL MEMORY DUMP	$F3B0 - $F3EF | $64 Bytes
	//PAL ROM				$FC00 - $FC1F | $15 Bytes
	//???					$FD00 - $FD03 | $4 Bytes
	//METATABLES			$FD00 - $FDFF | $255 Bytes
	
/*

TOTAL NES ROM MEMORY:		40.984KBs

LIST OF USED MEMORY--
	CURRENT INSTRUCTIONS MEMORY USED: 	0.924KBs
	CURRENT CUSTOM MEMORY USED: 		1.027KBs
	CURRENT SPRITE MEMORY USED:			1.152KBs	

MEMORY ADDED UP--
	TOTAL MEMORY USED: 3.103KBs
	LEFT OVER MEMORY: 37.881KBs
	
*/


// Controller Codes
	// A :		10000000 0x80
	// B :		01000000 0x40
	// Select :	00100000 0x20
	// Start :	00010000 0x10
	// Up :		00001000 0x08
	// Down :	00000100 0x04
	// Left :	00000010 0x02
	// Right :	00000001 0x01

unsigned char MEM_POINTER;
unsigned char MEM_POINTER2;

void main();

void store_level();

void draw_level_meta();

void draw_level();

void center_screen();

void fetch_sprites();

void fetch_palettes();

void get_controller_input();

void wait_for_vertical();

/* UNUSED FUNCTIONS
void water_sprites(void);
void water_sprites2(void);
*/

#endif //_BLOCKEN