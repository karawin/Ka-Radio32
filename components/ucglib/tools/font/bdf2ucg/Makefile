CFLAGS = -g -Wall
#CFLAGS = -O4 -Wall

SRC = bdf2ucg.c

OBJ = $(SRC:.c=.o)

bdf2u8g: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o bdf2ucg

clean:	
	-rm $(OBJ) bdf2ucg

test:	
	./bdf2u8g -f 2 ../bdf/9x18.bdf u8g_aafont_9x18 u8g_aafont_9x18.c