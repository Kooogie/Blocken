
#pragma register-vars (on)
#pragma message (__DATE__)

#pragma data-name ("IRAM","zeropage")
#pragma data-name ("OTHERRAM","absolute")
#pragma data-name ("WRAM","absolute")

#define BYTE0 (*(unsigned char*)0x0)
#define BYTE1 (*(unsigned char*)0x1)
#define BYTE2 (*(unsigned char*)0x2)

#define PPU_CONTROL (*(unsigned char*)0x2000)
#define PPU_MASK 	(*(unsigned char*)0x2001)
#define PPU_STATUS	(*(unsigned char*)0x2002)

#define PPU_ADDR	(*(unsigned char*)0x2006)
#define PPU_DATA	(*(unsigned char*)0x2007)


const unsigned char PALETTES[] = {
	0x30,0x3D,0x2D,0x1D,
	0x31,0x21,0x11,0x01,
	0x36,0x26,0x16,0x06,
	0x3A,0x2A,0x1A,0x0A
};

unsigned char IRAM[0x2000] = {};
unsigned char OTHERRAM[0x4000] = {};
unsigned char WRAM[0x2000] = {};

static unsigned short TEST;

void __MAIN__(void) {

	IRAM[0x26] = 0x01;
	IRAM[0x25] = 0x02;

	BYTE1 = 0x20;
	BYTE2 = 0x1E;

	for (BYTE0 = 0x0; BYTE0 < 0x10; ++BYTE0) {
		++BYTE1;
		++BYTE2;
		if (IRAM[BYTE1] == 0x01 || IRAM[BYTE2] == 0x01) {
			if (IRAM[BYTE0] == 0x2) {
				IRAM[0x30] = 0xFF;
			}
		}
	}
	
	while (1) {}
}