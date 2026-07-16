game.gba: src/main.c
	arm-none-eabi-gcc -mthumb -c src/main.c -o build/main.o
	arm-none-eabi-gcc -specs=gba.specs -mthumb build/main.o -o build/main.elf
	arm-none-eabi-objcopy -O binary build/main.elf game.gba
	gbafix game.gba

clean:
	rm -rv build/* game.gba
