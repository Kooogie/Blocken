
#pragma data-name ("IRAM","zp")
#pragma data-name ("UNUSED")
#pragma data-name ("WRAM")

#define PPU_CONTROL (*(unsigned char*)0x2000)
#define PPU_MASK 	(*(unsigned char*)0x2001)
#define PPU_STATUS	(*(unsigned char*)0x2002)
#define OAM_ADDR	(*(unsigned char*)0x2003)
#define OAM_DATA	(*(unsigned char*)0x2004)
#define PPU_SCROLL	(*(unsigned char*)0x2005)
#define PPU_ADDR	(*(unsigned char*)0x2006)
#define PPU_DATA	(*(unsigned char*)0x2007)

#define SQ0_DUTY	(*(unsigned char*)0x4000)
#define SQ0_SWEEP	(*(unsigned char*)0x4001)
#define SQ0_TIMER	(*(unsigned char*)0x4002)
#define SQ0_LENGTH	(*(unsigned char*)0x4003)
#define SQ1_DUTY	(*(unsigned char*)0x4004)
#define SQ1_SWEEP	(*(unsigned char*)0x4005)
#define SQ1_TIMER	(*(unsigned char*)0x4006)
#define SQ1_LENGTH	(*(unsigned char*)0x4007)

#define TRG_LINEAR	(*(unsigned char*)0x4008)
#define TRG_TIMER	(*(unsigned char*)0x400A)
#define TRG_LENGTH	(*(unsigned char*)0x400B)

#define NOISE_VOLUME	(*(unsigned char*)0x400C)
#define NOISE_PERIOD	(*(unsigned char*)0x400E)
#define NOISE_LENGTH	(*(unsigned char*)0x400F)

#define DMC_FREQ	(*(unsigned char*)0x4010)
#define DMC_COUNTER	(*(unsigned char*)0x4011)
#define DMC_ADDR	(*(unsigned char*)0x4012)
#define DMC_LENGTH	(*(unsigned char*)0x4013)

#define SPRITE_DMA	(*(unsigned char*)0x4014)
#define APU_STATUS	(*(unsigned char*)0x4015)

#define CTRL1	(*(unsigned char*)0x4016)
#define CTRL2	(*(unsigned char*)0x4017)

/*

PPU_MASK Bits

0 - Grayscale
1 - Show Background in leftmost 8 pixels of screen
2 - Show sprites in leftmost 8 pixels of screen
3 - Show background
4 - Show sprites
5 - Emphasize red
6 - Emphasize green
7 - Emphasize blue

*/

const unsigned char PLAYERDATA[] = {
	0x20,	// Y
	0x0,	// SPRITE
	0x0,	// PAL
	0x20	// X
};

const unsigned char PALETTES[] = {
	0x30,0x3D,0x2D,0x1D,
	0x31,0x21,0x11,0x01,
	0x36,0x26,0x16,0x06,
	0x3A,0x2A,0x1A,0x0A
};

const unsigned char GOLD_PAL[] = {
	0x38,0x28,0x18,0x08
};

unsigned char IRAM[0x800] 		= {}; //(INTERNAL RAM)
unsigned char UNUSED[0x57FF] 	= {};
unsigned char WRAM[0x2000] 		= {}; //(WORK RAM)

void __MAIN__();

void INIT();
void WAIT_FOR_VSYNC();
void FETCH_PALETTES();
void SHIFT_PALETTES();
void UPDATE_PLAYER_LOCATION();
void GET_CONTROLLER_INPUT();

void INIT() {
		WAIT_FOR_VSYNC();
		FETCH_PALETTES();
}

void WAIT_FOR_VSYNC() {
	IRAM[1] = PPU_STATUS;
	if (IRAM[1] >= 0x80) {
		// Break out of loop!
	}
	else {
		WAIT_FOR_VSYNC();
	}
}

void FETCH_PALETTES() {
	for (IRAM[1]=0x0; IRAM[1] < 0x10; ++IRAM[1]) {
		PPU_ADDR = 0x3F;
		PPU_ADDR = IRAM[1];
		PPU_DATA = PALETTES[IRAM[1]];
	}
}

void SHIFT_PALETTES() {
	PPU_ADDR = 0x3F;
	PPU_ADDR = 0x0;
	PPU_DATA = GOLD_PAL[IRAM[0xA]];
	++IRAM[3];
	if (IRAM[0xA] > 3) {
		IRAM[0xA] = 0;
	}
}

void UPDATE_PLAYER_LOCATION() {
	
}

void GET_CONTROLLER_INPUT () {
	IRAM[0x10] = CTRL1;
}