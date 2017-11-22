CFLAGS = -g -Wall -I../../../csrc/.  `sdl-config --cflags`

SRC = $(shell ls ../../../csrc/*.c) $(shell ls *.c) ../dev/ucg_dev_sdl.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o ucg_sdl

clean:	
	-rm $(OBJ) ucg_sdl

