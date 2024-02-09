
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
		if (IRAM[0] > 0x3A) {
			IRAM[0] = 0x0;
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
	if (IRAM[3] == 0x0) {
		PPU_ADDR = 0x3F;
		PPU_ADDR = 0x0;
		PPU_DATA = GOLD_PAL[0];
		++IRAM[3];
		return;
	}
	if (IRAM[3] == 0x1) {
		PPU_ADDR = 0x3F;
		PPU_ADDR = 0x0;
		PPU_DATA = PALETTES[0];
		--IRAM[3];
		return;
	}
}