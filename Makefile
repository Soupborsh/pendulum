CC?=cc

all: main.c
	$(CC) main.c -o main -Wall -O3 -lraylib -lm
clean:
	rm main
