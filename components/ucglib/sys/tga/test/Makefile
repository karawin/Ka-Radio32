CFLAGS = -g -Wall -I../../../csrc/.  

SRC = $(shell ls ../../../csrc/*.c) $(shell ls *.c) ../dev/ucg_dev_tga.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o ucg_tga

clean:	
	-rm $(OBJ) ucg_tga

