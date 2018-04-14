ifeq ($(OS), Windows_NT)
    DETECTED_OS := _WIN32
else
    DETECTED_OS := __unix__
endif

CC=sdcc --model-small -D$(DETECTED_OS)
FLAGS= --code-loc 0x4000 --xram-loc 0x0000

all: main.rel led.rel
	$(CC) $(FLAGS) $^

%.rel: %.c
	$(CC) -c $<

clean:
	rm *.rel *.asm *.ihx .*.mem *.rst *.sym *.map *.lst *.lk *.lnk *.mem
