CFLAGS = -g -Wall
#CFLAGS = -O4 -Wall

SRC = main.c bdf_font.c bdf_glyph.c bdf_parser.c bdf_map.c bdf_rle.c bdf_tga.c

OBJ = $(SRC:.c=.o)

bdfconv: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o bdfconv

clean:	
	-rm $(OBJ) bdfconv

test:	
	./bdfconv 