game.gba: src/main.c src/gma/gma.h
	arm-none-eabi-gcc -mthumb -mthumb-interwork -mcpu=arm7tdmi -Isrc/gma/ -c src/main.c -o build/main.o 
	arm-none-eabi-gcc -mthumb-interwork -mcpu=arm7tdmi -specs=gba.specs -mthumb build/main.o -o build/main.elf
	arm-none-eabi-objcopy -O binary build/main.elf game.gba
	gbafix game.gba

clean:
	rm -rv build/* game.gba
