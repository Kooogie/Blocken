#include <6502.h>
#include "include/Blocken.h"

void main(void) {
    LOOP1 = 0x0;
    DEVELOPER_BYTE = 0x0;
    clear_memory();
    fetch_palettes();
    draw_level_meta();

    //Pos camera
    center_screen();
	
    // Show sprites and background
    PPU_MASK = 0x1E;
    PPU_CTRL = 0x80;

    while (1) {
        wait_for_vertical();
		show_loop1();
		show_loop2();
		center_screen();
        LOOP1++;
    }
}



 // Defining Functions in Order

void draw_level_meta() {
    LOOP1 = 0x0; // FOR SHIFTING FROM 0 -> 1 to 20 -> 21 (ALWAYS 0x0 or 0x1F)
    LOOP2 = 0x0; // FOR SHIFTING EACH DRAW TWO PIXELS AWAY (HELPS WITH OVERLAPPING | * 2)
    LOOP3 = 0x0; // FOR SHIFTING DRAW DOWN BY 4 PIXELS (+0x20)
    LOOP4 = 0x0; // FOR ADDING LOOP1, 2, 3, AND BPS2 FOR A POINTER LOCATION
    LOOP5 = 0x0; // FOR INCERMENTING AND STORING 0x10s EACH TIME FOR LOOP3
    LOOP6 = 0x0; // FOR INCERMENTING PPU_ADDR 0x20
    for (BPS = 0x0; LOOP6 < 0x04; BPS++) {
        if (LOOP5 == 0x10) {
            LOOP2 = 0x0;
            LOOP3 = LOOP3 + 0x40;
            LOOP5 = 0x0;
        }
        MEM_POINTER = *((unsigned char*)0xE000 + BPS);
        LOOP1 = 0x0;
        LOOP2 = ((BPS & 0xF) * 0x2);
        for (BPS2 = 0x0; BPS2 < 0x4; BPS2++) {
            LOOP4 = (LOOP1 + LOOP2 + LOOP3 + BPS2);
            if (MEM_POINTER != 0x0) { // Skips these instructions if the pointer is nothing
                MEM_POINTER_STORE = (MEM_POINTER * 0x4) + BPS2;
                MEM_POINTER2 = *((unsigned char*)0xFD00 + MEM_POINTER_STORE);
                PPU_ADDR = 0x20 + LOOP6;
                PPU_ADDR = (0x0 + LOOP4);
                PPU_DATA = MEM_POINTER2;
            }
            if (BPS2 == 0x1) {
                LOOP1 = 0x1E;
            }
            if (LOOP4 == 0xFF) {
                LOOP6++;
            }
        }
        LOOP5++;
    }
}

void center_screen() {
    PPU_ADDR = 0x20;
    PPU_ADDR = 0x00;
    PPU_DATA = 0x00;
}

void fetch_palettes() {
    for (BPS = 0x0; BPS != 0x20; BPS++) {
        PPU_ADDR = 0x3F;
        PPU_ADDR = BPS;
        PPU_DATA = 0x0;
    }
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
}

void wait_for_vertical() {
    PPU_VSYNC = PPU_STATUS;
    if (PPU_VSYNC >= 0x80) {
        if (DEVELOPER_BYTE == 0x1) {
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
        }

        // Continue!
    }
    else {

        if (DEVELOPER_BYTE == 0x1) {
            LOOP1++;
            if (LOOP1 == 0xFF) {
                LOOP5++;
            }
        }

        wait_for_vertical();
    }
}

void clear_memory() {
}

void show_loop1() {
	LOOP_MOST = (LOOP1 >> 4) & 0xF;
	LOOP_LEAST = LOOP1 & 0xF;
	PPU_ADDR = 0x28;
	PPU_ADDR = 0xA0;
	PPU_DATA = 0xF0 + LOOP_MOST;
	PPU_ADDR = 0x28;
	PPU_ADDR = 0xA1;
	PPU_DATA = 0xF0 + LOOP_LEAST;
}

void show_loop2() {
	LOOP_MOST = (LOOP2 >> 4) & 0xF;
	LOOP_LEAST = LOOP2 & 0xF;
	PPU_ADDR = 0x20;
	PPU_ADDR = 0xC0;
	PPU_DATA = 0xF0 + LOOP_MOST;
	PPU_ADDR = 0x20;
	PPU_ADDR = 0xC1;
	PPU_DATA = 0xF0 + LOOP_LEAST;
}