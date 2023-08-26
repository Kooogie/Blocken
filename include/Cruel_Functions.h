#ifndef _CRUEL
#define _CRUEL

// CPU Custom Memory Addresses, Hints for where values should be stored at to save up on performance
#define LOOP1	(*(volatile unsigned char*)0x00)
#define LOOP2	(*(volatile unsigned char*)0x01)
#define LOOP3	(*(volatile unsigned char*)0x02)
#define LOOP4	(*(volatile unsigned char*)0x03)

#define PPU_SCROLL_X	(*(volatile unsigned char*)0x20)
#define PPU_SCROLL_Y	(*(volatile unsigned char*)0x21)

#define CTRL_STORE_BUFFER		(*(volatile unsigned char*)0x30)
#define CTRL_STORE				(*(volatile unsigned char*)0x31)
#define CTRL_STORE_MOST			(*(volatile unsigned char*)0x32)
#define CTRL_STORE_LEAST		(*(volatile unsigned char*)0x33)
#define CTRL_STORE_MOST_FLAG	(*(volatile unsigned char*)0x34)
#define CTRL_STORE_LEAST_FLAG	(*(volatile unsigned char*)0x35)

#define BPS			(*(volatile unsigned char*)0x40) // BACKGROUND POINTER STORE
#define BPS_LOOP	(*(volatile unsigned char*)0x41) // BACKGROUND POINTER STORE LOOP
#define BPS2		(*(volatile unsigned char*)0x42) // BACKGROUND POINTER STORE 2
#define DRAW_FLAG	(*(volatile unsigned char*)0x43) // FLAG FOR DRAWING



// CPU Memory Addresses
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

// ROM Memory Addresses
	//PAL ROM	$FC00 - $FC0F | $15 Bytes


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

void main(void);

void draw(void);

void get_controller_input(void);

#endif //_CRUEL