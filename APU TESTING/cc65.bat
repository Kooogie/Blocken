bin\cc65 APU_TEST_CODE.c -O -Or -Os -t nes
bin\ca65 APU_TEST_CODE.s
bin\ld65 APU_TEST_CODE.o -S 8000 -t nes
REM del APU_TEST_CODE.s
del APU_TEST_CODE.o

PAUSE