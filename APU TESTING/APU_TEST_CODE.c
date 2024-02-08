
#include "include/POINTERS.h"

#pragma register-vars (on)
#pragma message (__DATE__)

void __MAIN__(void) {
	
	WAIT_FOR_VSYNC();
	FETCH_PALETTES();
	
	PPU_MASK = 0x18;
	
	PPU_ADDR = 0x20;
	PPU_ADDR = 0x20;
	PPU_DATA = 0x01;
	
	while (1) {
		WAIT_FOR_VSYNC();
		++IRAM[0];
		if (IRAM[0] > 0x20) {
			SHIFT_PALETTES();
		}
	}
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
	 for (IRAM[0] = 0x0; IRAM[0] < 0x4; ++IRAM[0]) {
		PPU_ADDR = 0x3F;
		PPU_ADDR = IRAM[1];
		PPU_DATA = SHIFTING_PAL[IRAM[2]];
		++IRAM[1];
		++IRAM[2];
	}
	IRAM[1] = 0x0;
	IRAM[0] = 0x2;
	for (IRAM[0] = 0x0; IRAM[0] > 0x2; ++IRAM[0]) {
		--IRAM[2];
	}
	if (IRAM[2] > 0x9) {
		IRAM[2] = 0x0;
	}
}