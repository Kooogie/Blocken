#include <6502.h>
#include "include/Blocken.h"

void main(void) {

	wait_for_vertical();
	fetch_palettes();
	draw_level_meta();

	// Shifting Camera
	PPU_ADDR = 0x20;
	PPU_ADDR = 0x0;
	PPU_DATA = 0x0;

	// Show sprites and background
	PPU_MASK = 0x1E;
	
	wait_for_vertical();
	while (1) {
		wait_for_vertical();
		
		LOOP3++;
		if (LOOP3 == 0x01) {
			LOOP3 = 0x0;
			LOOP2++;
			PPU_SCROLL_X++;
		}
		if (LOOP2 == 0xFF) {
			LOOP2 = 0x0;
			LOOP4++;
		}
		
		/*
		LOOP_MOST = (LOOP4 >> 4) & 0xF;
		LOOP_LEAST = LOOP4 & 0x0F;
		
		if (LOOP_MOST_COMPARE != LOOP_MOST) {
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x20;
			PPU_DATA = LOOP_MOST | 0xF0;
			LOOP_MOST_COMPARE = LOOP_MOST;
		}
		
		if (LOOP_LEAST_COMPARE != LOOP_LEAST) {
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x21;
			PPU_DATA = LOOP_LEAST | 0xF0;
			LOOP_LEAST_COMPARE = LOOP_LEAST;
		}
		
		LOOP_MOST = (LOOP3 >> 4) & 0xF;
		LOOP_LEAST = LOOP3 & 0x0F;
		
		if (LOOP_MOST_COMPARE != LOOP_MOST) {
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x40;
			PPU_DATA = LOOP_MOST | 0xF0;
			LOOP_MOST_COMPARE = LOOP_MOST;
		}
		
		if (LOOP_LEAST_COMPARE != LOOP_LEAST) {
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x41;
			PPU_DATA = LOOP_LEAST | 0xF0;
			LOOP_LEAST_COMPARE = LOOP_LEAST;
		}
		
		LOOP_MOST = (LOOP2 >> 4) & 0xF;
		LOOP_LEAST = LOOP2 & 0x0F;
		
		if (LOOP_MOST_COMPARE != LOOP_MOST) {
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x60;
			PPU_DATA = LOOP_MOST | 0xF0;
			LOOP_MOST_COMPARE = LOOP_MOST;
		}
		
		if (LOOP_LEAST_COMPARE != LOOP_LEAST) {
			PPU_ADDR = 0x20;
			PPU_ADDR = 0x61;
			PPU_DATA = LOOP_LEAST | 0xF0;
			LOOP_LEAST_COMPARE = LOOP_LEAST;
		}
		*/
	}
}




 // Defining Functions in Order
void draw_level() {
	PPU_MASK = 0x0;
	for (BPS = 0x0; BPS2 != 0x1; BPS++) {
		MEM_POINTER = *((unsigned char*)0xEFF0 + BPS);
		PPU_ADDR = 0x20;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
		if (BPS == 0xFF) {
			BPS2 = 0x1;
		}
	}
	BPS2 = 0x0;
	for (BPS = 0x0; BPS2 != 0x1; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF0F0 + BPS);
		PPU_ADDR = 0x21;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
		if (BPS == 0xFF) {
			BPS2 = 0x1;
		}
	}
	BPS2 = 0x0;
	for (BPS = 0x0; BPS2 != 0x1; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF1F0 + BPS);
		PPU_ADDR = 0x22;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
		if (BPS == 0xFF) {
			BPS2 = 0x1;
		}
	}
	BPS2 = 0x0;
	for (BPS = 0x0; BPS2 != 0x1; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF2F0 + BPS);
		PPU_ADDR = 0x23;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
		if (BPS == 0xFF) {
			BPS2 = 0x1;
		}
	}
	// Second Screen
	BPS2 = 0x0;
	for (BPS = 0x0; BPS2 != 0x1; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF3F0 + BPS);
		PPU_ADDR = 0x24;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
		if (BPS == 0xFF) {
			BPS2 = 0x1;
		}
	}
	BPS2 = 0x0;
	for (BPS = 0x0; BPS2 != 0x1; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF4F0 + BPS);
		PPU_ADDR = 0x25;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
		if (BPS == 0xFF) {
			BPS2 = 0x1;
		}
	}
	BPS2 = 0x0;
	for (BPS = 0x0; BPS2 != 0x1; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF5F0 + BPS);
		PPU_ADDR = 0x26;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
		if (BPS == 0xFF) {
			BPS2 = 0x1;
		}
	}
	BPS2 = 0x0;
	for (BPS = 0x0; BPS2 != 0x1; BPS++) {
		MEM_POINTER = *((unsigned char*)0xF6F0 + BPS);
		PPU_ADDR = 0x27;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
		if (BPS == 0xFF) {
			BPS2 = 0x1;
		}
	}
	BPS2 = 0x0;
	PPU_MASK = 0x1E;
}

void draw_level_meta() {
	LOOP1 = 0x0;
	LOOP2 = 0x0;
	LOOP4 = 0x0;
	for (BPS = 0x0; BPS < 0x08; BPS++) {

		MEM_POINTER = *((unsigned char*)0xE000 + BPS);
		LOOP1 = 0x0;
		LOOP2 = (BPS * 0x2);

		for (BPS2 = 0x0; BPS2 < 0x4; BPS2++) {

			MEM_POINTER_STORE = (MEM_POINTER * 0x4) + BPS2;
			MEM_POINTER2 = *((unsigned char*)0xFD00 + MEM_POINTER_STORE);
			LOOP4 = (LOOP2 + BPS2 + LOOP1);
			PPU_ADDR = 0x20;
			PPU_ADDR = (0x00 + LOOP4);
			PPU_DATA = MEM_POINTER2;

			if (BPS2 == 0x1) {
				LOOP1 = 0x1E;
			}

		}
	}
}

void center_screen() {
	PPU_ADDR = 0x20;
	PPU_ADDR = 0x00;
	PPU_DATA = 0x00;
}

/*
void fetch_sprites() {
	wait_for_vertical();
	for (BPS2 = 0x0; BPS2 < 0x8; BPS2++) {
		for (BPS = 0x0; BPS < 0x8; BPS++) {
			MEM_POINTER = *((unsigned char*)0x6010 + BPS);
			OAM_ADDR = 0x0;
			OAM_ADDR = BPS;
			OAM_DATA = MEM_POINTER;
		}
	}
}
*/

void fetch_palettes() {
	for (BPS = 0x0; BPS != 0x20; BPS++) {
		MEM_POINTER = *((unsigned char*)0xFC00 + BPS);
		PPU_ADDR = 0x3F;
		PPU_ADDR = BPS;
		PPU_DATA = MEM_POINTER;
	}
}

void get_controller_input() {
	CTRL1 = 0x01;
	CTRL1 = 0x00;
	for (LOOP1 = 0; LOOP1 != 8; LOOP1++) {
		CTRL_STORE_BUFFER = (CTRL1 & 0x1);  // Saves the first bit of CTRL1
		CTRL_STORE = (CTRL_STORE << 1);  // Shifts all the bits of CTRL_STORE once
		CTRL_STORE = CTRL_STORE | CTRL_STORE_BUFFER;  // Apply the bytes from CTRL_STORE with CTRL_STORE_BUFFER
	}
	CTRL_OUTPUT = CTRL_STORE;

	if (CTRL_OUTPUT == 0x1) {
		if (CTRL_OUTPUT != LOOP4) {
			SPRITE_X++;
			LOOP4 = CTRL_OUTPUT;
			//fetch_sprites();
		}
	}
	else if (CTRL_OUTPUT == 0x2) {
		if (CTRL_OUTPUT != LOOP4) {
			SPRITE_X = SPRITE_X - 0x1;
			LOOP4 = CTRL_OUTPUT;
			//fetch_sprites();
		}
	}
	else if (CTRL_OUTPUT == 0x4) {
		if (CTRL_OUTPUT != LOOP4) {
			SPRITE_Y++;
			LOOP4 = CTRL_OUTPUT;
			//fetch_sprites();
		}
	}
	else if (CTRL_OUTPUT == 0x8) {
		if (CTRL_OUTPUT != LOOP4) {
			SPRITE_Y = SPRITE_Y - 0x1;
			LOOP4 = CTRL_OUTPUT;
			//fetch_sprites();
		}
	}
	else if (CTRL_OUTPUT == 0x0) {
		LOOP4 = CTRL_OUTPUT;
	}
}

void wait_for_vertical() {
	PPU_VSYNC = PPU_STATUS;
	if (PPU_VSYNC >= 0x80) {

		/*
		LOOP_MOST = (LOOP1 >> 4) & 0xF;
		LOOP_LEAST = LOOP1 & 0x0F;
		PPU_ADDR = 0x20;
		PPU_ADDR = 0x82;
		PPU_DATA = LOOP_MOST | 0xF0;
		PPU_ADDR = 0x20;
		PPU_ADDR = 0x83;
		PPU_DATA = LOOP_LEAST | 0xF0;
		LOOP_MOST = (LOOP5 >> 4) & 0xF;
		LOOP_LEAST = LOOP5 & 0x0F;
		PPU_ADDR = 0x20;
		PPU_ADDR = 0x80;
		PPU_DATA = LOOP_MOST | 0xF0;
		PPU_ADDR = 0x20;
		PPU_ADDR = 0x81;
		PPU_DATA = LOOP_LEAST | 0xF0;
		LOOP1 = 0x0;
		LOOP5 = 0x0;
		center_screen();
		*/

		// Continue!
	}
	else {
		LOOP1++;
		if (LOOP1 == 0xFF) {
			LOOP5++;
		}
		wait_for_vertical();
	}
}


/* BACK BURNER|UNUSED CODE
void water_sprites(void) {
	if (LOOP2_FLAG == 0x0) {
		if (LOOP2 == 0x50) {
			SPRITE = 0x36;
		}
		else if (LOOP2 == 0xA9) {
			SPRITE = 0x37;
			LOOP2_FLAG = 0x1;
		}
	}
	if (LOOP2_FLAG == 0x1) {
		SPRITE_Y = SPRITE_Y + ACC;
		ACC++;
		if (SPRITE_Y > 0x80) {
			LOOP2_FLAG = 0x02;
			SPRITE_Y = 0x45;
			SPRITE = 0x38;
			ACC = 0x0;
		}
	}
	if (LOOP2_FLAG == 0x2) {
		if (LOOP2 == 0xFF) {
			LOOP2_FLAG = 0x0;
			SPRITE = 0x35;
		}
	}
}

void water_sprites2(void) {
	if (LOOP2_FLAG2 == 0x0) {
		if (LOOP2 == 0x65) {
			SPRITE2 = 0x36;
		}
		else if (LOOP2 == 0xD5) {
			SPRITE2 = 0x37;
			LOOP2_FLAG2 = 0x1;
		}
	}
	if (LOOP2_FLAG2 == 0x1) {
		SPRITE_Y2 = SPRITE_Y2 + ACC2;
		ACC2++;
		if (SPRITE_Y2 > 0x80) {
			LOOP2_FLAG2 = 0x02;
			SPRITE_Y2 = 0x45;
			SPRITE2 = 0x38;
			ACC2 = 0x0;
		}
	}
	if (LOOP2_FLAG2 == 0x2) {
		if (LOOP2 == 0x60) {
			LOOP2_FLAG2 = 0x0;
			SPRITE2 = 0x35;
		}
	}
}
*/
