//bdfconv.exe -v -f 1 -m "$20-$ff,$a0-$ff,$a0-$17F,$0400-$058f" ../bdf/9x15.bdf -o 9x15.c -n u8g2_font_9x15_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/4x6.bdf -o 4x6.c -n u8g2_font_4x6_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/5x7.bdf -o 5x7.c -n u8g2_font_5x7_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/5x8.bdf -o 5x8.c -n u8g2_font_5x8_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/6x12.bdf -o 6x12.c -n u8g2_font_6x12_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/6x13.bdf -o 6x13.c -n u8g2_font_6x13_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/7x13.bdf -o 7x13.c -n u8g2_font_7x13_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/8x13.bdf -o 8x13.c -n u8g2_font_8x13_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/9x15.bdf -o 9x15.c -n u8g2_font_9x15_t_latcyr
..\bdfconv\bdfconv.exe -v -f 1 -m "$20-$7f,$a0-$17F,$0370-$058f" ../bdf/10x20.bdf -o 10x20.c -n u8g2_font_10x20_t_latcyr
del u8g2_karadio32_fonts.c
type header.cc *.c > u8g2_karadio32_fonts.cc
rename u8g2_karadio32_fonts.cc u8g2_karadio32_fonts.c
