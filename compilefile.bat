bin\ca65 source\NES.s
bin\ld65 source\NES.o -C cfg\nes.cfg -S 8000

pause