CFLAGS = -g -Wall -I../../../csrc/.  `sdl-config --cflags`

SRC = $(shell ls ../../../csrc/*.c) $(shell ls *.c)

OBJ = $(SRC:.c=.o)

all: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o ucg_com

clean:	
	-rm $(OBJ) ucg_com

