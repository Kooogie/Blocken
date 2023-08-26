#include <6502.h>
#include "include/Cruel_Functions.h"


void main(void) {

	draw();

	// For loop for getting PAL memory into the NES's PPU.
	for (BPS = 0xBF; BPS != 0x20; BPS++) {
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
	PPU_MASK = 0x1E; // 00011110
	
	while (1) {
		get_controller_input();
	}
}


void draw(void) {
	for (BPS = 0x0; BPS < 0xFF; BPS++) {
		MEM_POINTER = *((unsigned char*)0xEFF0 + BPS);
		PPU_ADDR = 0x20;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
	for (BPS = 0x0; BPS < 0xFF; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF0F0 + BPS);
		PPU_ADDR = 0x21;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
	for (BPS = 0x0; BPS < 0xFF; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF1F0 + BPS);
		PPU_ADDR = 0x22;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
	for (BPS = 0x0; BPS < 0xFF; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF2F0 + BPS);
		PPU_ADDR = 0x23;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
}


void get_controller_input(void) {
	CTRL1 = 0x01;
	CTRL1 = 0x00;
	for (LOOP1 = 0; LOOP1 != 8; LOOP1++) {
		CTRL_STORE_BUFFER = (CTRL1 & 0x1); // Saves the first bit of CTRL1
		CTRL_STORE = (CTRL_STORE << 1); // Shifts all the bits of CTRL_STORE once
		CTRL_STORE = CTRL_STORE | CTRL_STORE_BUFFER; // Apply the bytes from CTRL_STORE with CTRL_STORE_BUFFER
	}
}

