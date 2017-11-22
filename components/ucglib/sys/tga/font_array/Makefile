# Generate overview pictures based on the list of fonts (font-array) 
# in the build directory.
# The font array must be created with "do_combine.sh" first.

CFLAGS = -g -Wall -I../../../csrc/.  

SRC = $(shell ls ../../../csrc/*.c) $(shell ls *.c) ../dev/ucg_dev_tga.c ../../../tools/font/build/ucg_font_array.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o font_array

clean:	
	-rm $(OBJ) font_array *.tga *.png *.md

