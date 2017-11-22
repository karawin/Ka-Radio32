CFLAGS = -g -Wall -I../../../csrc/.  

SRC = $(shell ls ../../../csrc/*.c) $(shell ls *.c) ../dev/ucg_dev_tga.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o font_overview

clean:	
	-rm $(OBJ) font_overview ucg_font.tga ucg_font.png

