#
# postprocessing step after building the fonts
#
# the following files are created:
#
# ucg_font_data.h 			--> copy content to ucg.h
# ucg_font_array.c  			--> can be used to create overview pics
# ucg_pixel_font_data.c 		--> copy into csrc folder 
# ucg_vector_font_data.c		--> copy into csrc folder





# combine individal files together

echo "#include \"ucg.h\"" > ucg_pixel_font_data.c
fgrep -h -v "#include" ./pixel/*.c >> ucg_pixel_font_data.c

echo "#include \"ucg.h\"" > ucg_vector_font_data.c
fgrep -h -v "#include" ./ttf/*.c >> ucg_vector_font_data.c

#generate declarations

fgrep ucg_fntpgm_uint8_t ucg_pixel_font_data.c | sed -e 's/^\([^[]*\).[0-9]*\([^)]*\).*/extern \1[\2);/' > ucg_font_data.h
fgrep ucg_fntpgm_uint8_t ucg_vector_font_data.c | sed -e 's/^\([^[]*\).[0-9]*\([^)]*\).*/extern \1[\2);/' >> ucg_font_data.h

# generate array with all fonts

echo "#include \"ucg.h\"" > ucg_font_array.c
echo "const ucg_fntpgm_uint8_t *ucg_font_array[] = {" >> ucg_font_array.c
cut -d " " -f 4 ucg_font_data.h | sed -e 's|\[\]|,|' >> ucg_font_array.c
echo "NULL" >> ucg_font_array.c
echo "};" >> ucg_font_array.c

echo "char *ucg_font_name[] = {" >> ucg_font_array.c
cut -d " " -f 4 ucg_font_data.h | sed -e 's|^\(.*\)\[\]|\"\1\",|' >> ucg_font_array.c
echo "NULL" >> ucg_font_array.c
echo "};" >> ucg_font_array.c
