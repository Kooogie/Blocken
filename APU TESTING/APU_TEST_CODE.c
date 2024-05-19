
#include "include/POINTERS.h"

#pragma register-vars (on)
#pragma message (__DATE__)

void __MAIN__(void) {
	
	INIT();
	
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
			++IRAM[0xA];
		}
	}
}