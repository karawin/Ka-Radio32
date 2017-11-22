#!/bin/bash

# "execute do_combine.sh after executing this script"

echo u8glib_4
../bdf2ucg/bdf2ucg -f 1 ../bdf/u8glib_4.bdf ucg_font_u8glib_4 ./pixel/ucg_font_u8glib_4.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/u8glib_4.bdf ucg_font_u8glib_4r ./pixel/ucg_font_u8glib_4r.c > /dev/null

echo m2icon
../bdf2ucg/bdf2ucg -f 1 -b 65 -e 104 ../bdf/m2icon_5.bdf ucg_font_m2icon_5 ./pixel/ucg_font_m2icon_5.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 65 -e 104  ../bdf/m2icon_7.bdf ucg_font_m2icon_7 ./pixel/ucg_font_m2icon_7.c > /dev/null
../bdf2ucg/bdf2ucg  -b 65 -e 105  ../bdf/m2icon_9.bdf ucg_font_m2icon_9 ./pixel/ucg_font_m2icon_9.c > /dev/null

echo cursor
../bdf2ucg/bdf2ucg -s 32 ../bdf/cursor.bdf ucg_font_cursor ./pixel/ucg_font_cursor.c > /dev/null
../bdf2ucg/bdf2ucg -e 80 -s 32 ../bdf/cursorr.bdf ucg_font_cursorr ./pixel/ucg_font_cursorr.c > /dev/null
echo cu12
../bdf2ucg/bdf2ucg ../bdf/cu12.bdf ucg_font_cu12 ./pixel/ucg_font_cu12.c  > /dev/null
../bdf2ucg/bdf2ucg -l 67 -u 75 ../bdf/cu12.bdf ucg_font_cu12_67_75 ./pixel/ucg_font_cu12_67_75.c  > /dev/null
../bdf2ucg/bdf2ucg -l 75 -b 32 -e 79 ../bdf/cu12.bdf ucg_font_cu12_75r ./pixel/ucg_font_cu12_75r.c  > /dev/null
#../bdf2ucg/bdf2ucg -l 78 -u 79 ../bdf/cu12.bdf ucg_font_cu12_78_79 ./pixel/ucg_font_cu12_78_79.c
echo micro
../bdf2ucg/bdf2ucg -f 1 ../bdf/micro.bdf ucg_font_micro ./pixel/ucg_font_micro.c  > /dev/null
#../bdf2ucg/bdf2ucg -f 1 ../bdf/micro.bdf ucg_font_micror ./pixel/ucg_font_micror.c  > /dev/null
echo "4x6"
../bdf2ucg/bdf2ucg -f 1 ../bdf/4x6.bdf ucg_font_4x6 ./pixel/ucg_font_4x6.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/4x6.bdf ucg_font_4x6r ./pixel/ucg_font_4x6r.c  > /dev/null
#../bdf2ucg/bdf2ucg -f 1 -b 42 -e 58 ../bdf/4x6.bdf ucg_font_4x6n ./pixel/ucg_font_4x6n.c  > /dev/null
echo "5x7"
../bdf2ucg/bdf2ucg -f 1 ../bdf/5x7.bdf ucg_font_5x7 ./pixel/ucg_font_5x7.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/5x7.bdf ucg_font_5x7r ./pixel/ucg_font_5x7r.c  > /dev/null
echo "5x8"
../bdf2ucg/bdf2ucg -f 1 ../bdf/5x8.bdf ucg_font_5x8 ./pixel/ucg_font_5x8.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/5x8.bdf ucg_font_5x8r ./pixel/ucg_font_5x8r.c  > /dev/null
echo "6x10"
../bdf2ucg/bdf2ucg -f 1 ../bdf/6x10.bdf ucg_font_6x10 ./pixel/ucg_font_6x10.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/6x10.bdf ucg_font_6x10r ./pixel/ucg_font_6x10r.c  > /dev/null
echo "6x12"
../bdf2ucg/bdf2ucg -f 1 ../bdf/6x12.bdf ucg_font_6x12 ./pixel/ucg_font_6x12.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/6x12.bdf ucg_font_6x12r ./pixel/ucg_font_6x12r.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 67 -u 75 -b 0 -e 255 ../bdf/6x12.bdf ucg_font_6x12_67_75 ./pixel/ucg_font_6x12_67_75.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 75 -b 32 -e 79 ../bdf/6x12.bdf ucg_font_6x12_75r ./pixel/ucg_font_6x12_75r.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 78 -u 79 -b 0 -e 255 ../bdf/6x12.bdf ucg_font_6x12_78_79 ./pixel/ucg_font_6x12_78_79.c  > /dev/null
echo "6x13"
../bdf2ucg/bdf2ucg -f 1 ../bdf/6x13.bdf ucg_font_6x13 ./pixel/ucg_font_6x13.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/6x13.bdf ucg_font_6x13r ./pixel/ucg_font_6x13r.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 67 -u 75 ../bdf/6x13.bdf ucg_font_6x13_67_75 ./pixel/ucg_font_6x13_67_75.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 75 -b 32 -e 79 ../bdf/6x13.bdf ucg_font_6x13_75r ./pixel/ucg_font_6x13_75r.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 78 -u 79 ../bdf/6x13.bdf ucg_font_6x13_78_79 ./pixel/ucg_font_6x13_78_79.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 ../bdf/6x13B.bdf ucg_font_6x13B ./pixel/ucg_font_6x13B.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/6x13B.bdf ucg_font_6x13Br ./pixel/ucg_font_6x13Br.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 ../bdf/6x13O.bdf ucg_font_6x13O ./pixel/ucg_font_6x13O.c  > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/6x13O.bdf ucg_font_6x13Or ./pixel/ucg_font_6x13Or.c  > /dev/null
echo "7x13"
../bdf2ucg/bdf2ucg -f 1 ../bdf/7x13.bdf ucg_font_7x13 ./pixel/ucg_font_7x13.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/7x13.bdf ucg_font_7x13r ./pixel/ucg_font_7x13r.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 67 -u 75 ../bdf/7x13.bdf ucg_font_7x13_67_75 ./pixel/ucg_font_7x13_67_75.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 75 -b 32 -e 79 ../bdf/7x13.bdf ucg_font_7x13_75r ./pixel/ucg_font_7x13_75r.c > /dev/null
#../bdf2ucg/bdf2ucg -l 78 -u 79 ../bdf/7x13.bdf ucg_font_7x13_78_79 ./pixel/ucg_font_7x13_78_79.c
../bdf2ucg/bdf2ucg -f 1 ../bdf/7x13B.bdf ucg_font_7x13B ./pixel/ucg_font_7x13B.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/7x13B.bdf ucg_font_7x13Br ./pixel/ucg_font_7x13Br.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 ../bdf/7x13O.bdf ucg_font_7x13O ./pixel/ucg_font_7x13O.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/7x13O.bdf ucg_font_7x13Or ./pixel/ucg_font_7x13Or.c > /dev/null
echo "7x14"
../bdf2ucg/bdf2ucg -f 1 ../bdf/7x14.bdf ucg_font_7x14 ./pixel/ucg_font_7x14.c > /dev/null
../bdf2ucg/bdf2ucg -f 1  -b 32 -e 127 ../bdf/7x14.bdf ucg_font_7x14r ./pixel/ucg_font_7x14r.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 ../bdf/7x14B.bdf ucg_font_7x14B ./pixel/ucg_font_7x14B.c > /dev/null
../bdf2ucg/bdf2ucg -f 1  -b 32 -e 127 ../bdf/7x14B.bdf ucg_font_7x14Br ./pixel/ucg_font_7x14Br.c > /dev/null
echo "8x13"
../bdf2ucg/bdf2ucg -f 1 ../bdf/8x13.bdf ucg_font_8x13 ./pixel/ucg_font_8x13.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/8x13.bdf ucg_font_8x13r ./pixel/ucg_font_8x13r.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 67 -u 75 ../bdf/8x13.bdf ucg_font_8x13_67_75 ./pixel/ucg_font_8x13_67_75.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -l 75 -b 32 -e 79 ../bdf/8x13.bdf ucg_font_8x13_75r ./pixel/ucg_font_8x13_75r.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 ../bdf/8x13B.bdf ucg_font_8x13B ./pixel/ucg_font_8x13B.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/8x13B.bdf ucg_font_8x13Br ./pixel/ucg_font_8x13Br.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 ../bdf/8x13O.bdf ucg_font_8x13O ./pixel/ucg_font_8x13O.c > /dev/null
../bdf2ucg/bdf2ucg -f 1 -b 32 -e 127 ../bdf/8x13O.bdf ucg_font_8x13Or ./pixel/ucg_font_8x13Or.c > /dev/null
echo "9x15"
../bdf2ucg/bdf2ucg ../bdf/9x15.bdf ucg_font_9x15 ./pixel/ucg_font_9x15.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/9x15.bdf ucg_font_9x15r ./pixel/ucg_font_9x15r.c > /dev/null
../bdf2ucg/bdf2ucg -l 67 -u 75 ../bdf/9x15.bdf ucg_font_9x15_67_75 ./pixel/ucg_font_9x15_67_75.c > /dev/null
../bdf2ucg/bdf2ucg -l 75 -b 32 -e 79 ../bdf/9x15.bdf ucg_font_9x15_75r ./pixel/ucg_font_9x15_75r.c > /dev/null
../bdf2ucg/bdf2ucg -l 78 -u 79 ../bdf/9x15.bdf ucg_font_9x15_78_79 ./pixel/ucg_font_9x15_78_79.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/9x15B.bdf ucg_font_9x15B ./pixel/ucg_font_9x15B.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/9x15B.bdf ucg_font_9x15Br ./pixel/ucg_font_9x15Br.c > /dev/null
echo "9x18"
../bdf2ucg/bdf2ucg ../bdf/9x18.bdf ucg_font_9x18 ./pixel/ucg_font_9x18.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/9x18.bdf ucg_font_9x18r ./pixel/ucg_font_9x18r.c > /dev/null
../bdf2ucg/bdf2ucg -l 67 -u 75 ../bdf/9x18.bdf ucg_font_9x18_67_75 ./pixel/ucg_font_9x18_67_75.c > /dev/null
../bdf2ucg/bdf2ucg -l 75 -b 32 -e 79  ../bdf/9x18.bdf ucg_font_9x18_75r ./pixel/ucg_font_9x18_75r.c > /dev/null
../bdf2ucg/bdf2ucg -l 78 -u 79 ../bdf/9x18.bdf ucg_font_9x18_78_79 ./pixel/ucg_font_9x18_78_79.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/9x18B.bdf ucg_font_9x18B ./pixel/ucg_font_9x18B.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/9x18B.bdf ucg_font_9x18Br ./pixel/ucg_font_9x18Br.c > /dev/null
echo "10x20"
../bdf2ucg/bdf2ucg ../bdf/10x20.bdf ucg_font_10x20 ./pixel/ucg_font_10x20.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/10x20.bdf ucg_font_10x20r ./pixel/ucg_font_10x20r.c > /dev/null
../bdf2ucg/bdf2ucg -l 67 -u 75 ../bdf/10x20.bdf ucg_font_10x20_67_75 ./pixel/ucg_font_10x20_67_75.c > /dev/null
../bdf2ucg/bdf2ucg -l 75  -b 32 -e 79 ../bdf/10x20.bdf ucg_font_10x20_75r ./pixel/ucg_font_10x20_75r.c > /dev/null
../bdf2ucg/bdf2ucg -l 78 -u 79 ../bdf/10x20.bdf ucg_font_10x20_78_79 ./pixel/ucg_font_10x20_78_79.c > /dev/null
echo "profont"
../bdf2ucg/bdf2ucg ../bdf/profont10.bdf ucg_font_profont10 ./pixel/ucg_font_profont10.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/profont11.bdf ucg_font_profont11 ./pixel/ucg_font_profont11.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/profont12.bdf ucg_font_profont12 ./pixel/ucg_font_profont12.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/profont15.bdf ucg_font_profont15 ./pixel/ucg_font_profont15.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/profont17.bdf ucg_font_profont17 ./pixel/ucg_font_profont17.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/profont22.bdf ucg_font_profont22 ./pixel/ucg_font_profont22.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/profont29.bdf ucg_font_profont29 ./pixel/ucg_font_profont29.c > /dev/null

../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/profont10.bdf ucg_font_profont10r ./pixel/ucg_font_profont10r.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/profont11.bdf ucg_font_profont11r ./pixel/ucg_font_profont11r.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/profont12.bdf ucg_font_profont12r ./pixel/ucg_font_profont12r.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/profont15.bdf ucg_font_profont15r ./pixel/ucg_font_profont15r.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/profont17.bdf ucg_font_profont17r ./pixel/ucg_font_profont17r.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/profont22.bdf ucg_font_profont22r ./pixel/ucg_font_profont22r.c > /dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ../bdf/profont29.bdf ucg_font_profont29r ./pixel/ucg_font_profont29r.c > /dev/null

../bdf2ucg/bdf2ucg -b 42 -e 58 ../bdf/profont22.bdf ucg_font_profont22n ./pixel/ucg_font_profont22n.c > /dev/null
../bdf2ucg/bdf2ucg -b 42 -e 58 ../bdf/profont29.bdf ucg_font_profont29n ./pixel/ucg_font_profont29n.c > /dev/null

echo "unifont"
../bdf2ucg/bdf2ucg -l 0 -u 1 -b 0 -e 255  ../bdf/unifont.bdf ucg_font_unifont ./pixel/ucg_font_unifont.c > /dev/null
../bdf2ucg/bdf2ucg -l 0 -u 1 -b 32 -e 127  ../bdf/unifont.bdf ucg_font_unifontr ./pixel/ucg_font_unifontr.c > /dev/null
../bdf2ucg/bdf2ucg -l 2 -u 3 -b 0 -e 255  ../bdf/unifont.bdf ucg_font_unifont_2_3 ./pixel/ucg_font_unifont_2_3.c > /dev/null
../bdf2ucg/bdf2ucg -l 4 -u 5 -b 0 -e 255  ../bdf/unifont.bdf ucg_font_unifont_4_5 ./pixel/ucg_font_unifont_4_5.c > /dev/null
../bdf2ucg/bdf2ucg -l 18 -u 19 -b 0 -e 255 ../bdf/unifont.bdf ucg_font_unifont_18_19 ./pixel/ucg_font_unifont_18_19.c > /dev/null
../bdf2ucg/bdf2ucg -l 72 -u 73 -b 0 -e 255 ../bdf/unifont.bdf ucg_font_unifont_72_73 ./pixel/ucg_font_unifont_72_73.c > /dev/null
../bdf2ucg/bdf2ucg -l 67 -u 75 -b 16 -e 255 ../bdf/unifont.bdf ucg_font_unifont_67_75 ./pixel/ucg_font_unifont_67_75.c > /dev/null
../bdf2ucg/bdf2ucg -l 75 -b 32 -e 79 ../bdf/unifont.bdf ucg_font_unifont_75r ./pixel/ucg_font_unifont_75r.c > /dev/null
../bdf2ucg/bdf2ucg -l 78 -u 79 -b 1 -e 255 ../bdf/unifont.bdf ucg_font_unifont_78_79 ./pixel/ucg_font_unifont_78_79.c > /dev/null
../bdf2ucg/bdf2ucg -l 86 -u 87 -s 32 -b 32 -e 116 ../bdf/unifont.bdf ucg_font_unifont_86 ./pixel/ucg_font_unifont_86.c > /dev/null
../bdf2ucg/bdf2ucg -l 77 -u 87 -s 32 -b 32 -e 99 ../bdf/unifont.bdf ucg_font_unifont_77 ./pixel/ucg_font_unifont_77.c > /dev/null
../bdf2ucg/bdf2ucg -l 76 -u 87 -s 32 -b 32 -e 159  ../bdf/unifont.bdf ucg_font_unifont_76 ./pixel/ucg_font_unifont_76.c > /dev/null
../bdf2ucg/bdf2ucg -l 8 -u 9 -b 0 -e 255 ../bdf/unifont.bdf ucg_font_unifont_8_9 ./pixel/ucg_font_unifont_8_9.c > /dev/null
../bdf2ucg/bdf2ucg -l 0 -u 8 -S 32  ../bdf/unifont.bdf ucg_font_unifont_0_8 ./pixel/ucg_font_unifont_0_8.c > /dev/null
../bdf2ucg/bdf2ucg -l 12 -u 13 -b 0 -e 255 ../bdf/unifont.bdf ucg_font_unifont_12_13 ./pixel/ucg_font_unifont_12_13.c > /dev/null

echo "adobe courB 08"
../bdf2ucg/bdf2ucg ../bdf/courB08.bdf ucg_font_courB08 ./pixel/ucg_font_courb08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courB08.bdf ucg_font_courB08r ./pixel/ucg_font_courb08r.c > /dev/null
echo "adobe courB 10"
../bdf2ucg/bdf2ucg ../bdf/courB10.bdf ucg_font_courB10 ./pixel/ucg_font_courb10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courB10.bdf ucg_font_courB10r ./pixel/ucg_font_courb10r.c > /dev/null
echo "adobe courB 12"
../bdf2ucg/bdf2ucg ../bdf/courB12.bdf ucg_font_courB12 ./pixel/ucg_font_courb12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courB12.bdf ucg_font_courB12r ./pixel/ucg_font_courb12r.c > /dev/null
echo "adobe courB 14"
../bdf2ucg/bdf2ucg ../bdf/courB14.bdf ucg_font_courB14 ./pixel/ucg_font_courb14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courB14.bdf ucg_font_courB14r ./pixel/ucg_font_courb14r.c > /dev/null
echo "adobe courB 18"
../bdf2ucg/bdf2ucg ../bdf/courB18.bdf ucg_font_courB18 ./pixel/ucg_font_courb18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courB18.bdf ucg_font_courB18r ./pixel/ucg_font_courb18r.c > /dev/null
echo "adobe courB 24"
../bdf2ucg/bdf2ucg ../bdf/courB24.bdf ucg_font_courB24 ./pixel/ucg_font_courb24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courB24.bdf ucg_font_courB24r ./pixel/ucg_font_courb24r.c > /dev/null
../bdf2ucg/bdf2ucg  -b 42 -e 58 ../bdf/courB24.bdf ucg_font_courB24n ./pixel/ucg_font_courb4n.c > /dev/null

echo "adobe courR"
../bdf2ucg/bdf2ucg ../bdf/courR08.bdf ucg_font_courR08 ./pixel/ucg_font_courr08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courR08.bdf ucg_font_courR08r ./pixel/ucg_font_courr08r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/courR10.bdf ucg_font_courR10 ./pixel/ucg_font_courr10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courR10.bdf ucg_font_courR10r ./pixel/ucg_font_courr10r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/courR12.bdf ucg_font_courR12 ./pixel/ucg_font_courr12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courR12.bdf ucg_font_courR12r ./pixel/ucg_font_courr12r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/courR14.bdf ucg_font_courR14 ./pixel/ucg_font_courr14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courR14.bdf ucg_font_courR14r ./pixel/ucg_font_courr14r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/courR18.bdf ucg_font_courR18 ./pixel/ucg_font_courr18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courR18.bdf ucg_font_courR18r ./pixel/ucg_font_courr18r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/courR24.bdf ucg_font_courR24 ./pixel/ucg_font_courr24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/courR24.bdf ucg_font_courR24r ./pixel/ucg_font_courr24r.c > /dev/null
../bdf2ucg/bdf2ucg  -b 42 -e 58 ../bdf/courR24.bdf ucg_font_courR24n ./pixel/ucg_font_courr24n.c > /dev/null

echo "adobe helvB"
../bdf2ucg/bdf2ucg ../bdf/helvB08.bdf ucg_font_helvB08 ./pixel/ucg_font_helvb08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvB08.bdf ucg_font_helvB08r ./pixel/ucg_font_helvb08r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvB10.bdf ucg_font_helvB10 ./pixel/ucg_font_helvb10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvB10.bdf ucg_font_helvB10r ./pixel/ucg_font_helvb10r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvB12.bdf ucg_font_helvB12 ./pixel/ucg_font_helvb12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvB12.bdf ucg_font_helvB12r ./pixel/ucg_font_helvb12r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvB14.bdf ucg_font_helvB14 ./pixel/ucg_font_helvb14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvB14.bdf ucg_font_helvB14r ./pixel/ucg_font_helvb14r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvB18.bdf ucg_font_helvB18 ./pixel/ucg_font_helvb18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvB18.bdf ucg_font_helvB18r ./pixel/ucg_font_helvb18r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvB24.bdf ucg_font_helvB24 ./pixel/ucg_font_helvb24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvB24.bdf ucg_font_helvB24r ./pixel/ucg_font_helvb24r.c > /dev/null
../bdf2ucg/bdf2ucg  -b 42 -e 58  ../bdf/helvB24.bdf ucg_font_helvB24n ./pixel/ucg_font_helvb24n.c > /dev/null

echo "adobe helvR"
../bdf2ucg/bdf2ucg ../bdf/helvR08.bdf ucg_font_helvR08 ./pixel/ucg_font_helvr08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvR08.bdf ucg_font_helvR08r ./pixel/ucg_font_helvr08r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvR10.bdf ucg_font_helvR10 ./pixel/ucg_font_helvr10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvR10.bdf ucg_font_helvR10r ./pixel/ucg_font_helvr10r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvR12.bdf ucg_font_helvR12 ./pixel/ucg_font_helvr12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvR12.bdf ucg_font_helvR12r ./pixel/ucg_font_helvr12r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvR14.bdf ucg_font_helvR14 ./pixel/ucg_font_helvr14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvR14.bdf ucg_font_helvR14r ./pixel/ucg_font_helvr14r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvR18.bdf ucg_font_helvR18 ./pixel/ucg_font_helvr18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvR18.bdf ucg_font_helvR18r ./pixel/ucg_font_helvr18r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/helvR24.bdf ucg_font_helvR24 ./pixel/ucg_font_helvr24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/helvR24.bdf ucg_font_helvR24r ./pixel/ucg_font_helvr24r.c > /dev/null
../bdf2ucg/bdf2ucg  -b 42 -e 58  ../bdf/helvR24.bdf ucg_font_helvR24n ./pixel/ucg_font_helvr24n.c > /dev/null

echo "adobe ncenB"
../bdf2ucg/bdf2ucg ../bdf/ncenB08.bdf ucg_font_ncenB08 ./pixel/ucg_font_ncenb08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenB08.bdf ucg_font_ncenB08r ./pixel/ucg_font_ncenb08r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenB10.bdf ucg_font_ncenB10 ./pixel/ucg_font_ncenb10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenB10.bdf ucg_font_ncenB10r ./pixel/ucg_font_ncenb10r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenB12.bdf ucg_font_ncenB12 ./pixel/ucg_font_ncenb12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenB12.bdf ucg_font_ncenB12r ./pixel/ucg_font_ncenb12r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenB14.bdf ucg_font_ncenB14 ./pixel/ucg_font_ncenb14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenB14.bdf ucg_font_ncenB14r ./pixel/ucg_font_ncenb14r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenB18.bdf ucg_font_ncenB18 ./pixel/ucg_font_ncenb18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenB18.bdf ucg_font_ncenB18r ./pixel/ucg_font_ncenb18r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenB24.bdf ucg_font_ncenB24 ./pixel/ucg_font_ncenb24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenB24.bdf ucg_font_ncenB24r ./pixel/ucg_font_ncenb24r.c > /dev/null
../bdf2ucg/bdf2ucg  -b 42 -e 58  ../bdf/ncenB24.bdf ucg_font_ncenB24n ./pixel/ucg_font_ncenb24n.c > /dev/null

echo "adobe ncenR"
../bdf2ucg/bdf2ucg ../bdf/ncenR08.bdf ucg_font_ncenR08 ./pixel/ucg_font_ncenr08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenR08.bdf ucg_font_ncenR08r ./pixel/ucg_font_ncenr08r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenR10.bdf ucg_font_ncenR10 ./pixel/ucg_font_ncenr10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenR10.bdf ucg_font_ncenR10r ./pixel/ucg_font_ncenr10r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenR12.bdf ucg_font_ncenR12 ./pixel/ucg_font_ncenr12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenR12.bdf ucg_font_ncenR12r ./pixel/ucg_font_ncenr12r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenR14.bdf ucg_font_ncenR14 ./pixel/ucg_font_ncenr14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenR14.bdf ucg_font_ncenR14r ./pixel/ucg_font_ncenr14r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenR18.bdf ucg_font_ncenR18 ./pixel/ucg_font_ncenr18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenR18.bdf ucg_font_ncenR18r ./pixel/ucg_font_ncenr18r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/ncenR24.bdf ucg_font_ncenR24 ./pixel/ucg_font_ncenr24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/ncenR24.bdf ucg_font_ncenR24r ./pixel/ucg_font_ncenr24r.c > /dev/null
../bdf2ucg/bdf2ucg  -b 42 -e 58  ../bdf/ncenR24.bdf ucg_font_ncenR24n ./pixel/ucg_font_ncenr24n.c > /dev/null


echo "adobe timB"
../bdf2ucg/bdf2ucg ../bdf/timB08.bdf ucg_font_timB08 ./pixel/ucg_font_timb08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timB08.bdf ucg_font_timB08r ./pixel/ucg_font_timb08r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timB10.bdf ucg_font_timB10 ./pixel/ucg_font_timb10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timB10.bdf ucg_font_timB10r ./pixel/ucg_font_timb10r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timB12.bdf ucg_font_timB12 ./pixel/ucg_font_timb12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timB12.bdf ucg_font_timB12r ./pixel/ucg_font_timb12r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timB14.bdf ucg_font_timB14 ./pixel/ucg_font_timb14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timB14.bdf ucg_font_timB14r ./pixel/ucg_font_timb14r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timB18.bdf ucg_font_timB18 ./pixel/ucg_font_timb18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timB18.bdf ucg_font_timB18r ./pixel/ucg_font_timb18r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timB24.bdf ucg_font_timB24 ./pixel/ucg_font_timb24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timB24.bdf ucg_font_timB24r ./pixel/ucg_font_timb24r.c > /dev/null
../bdf2ucg/bdf2ucg  -b 42 -e 58  ../bdf/timB24.bdf ucg_font_timB24n ./pixel/ucg_font_timb24n.c > /dev/null

echo "adobe timR"
../bdf2ucg/bdf2ucg ../bdf/timR08.bdf ucg_font_timR08 ./pixel/ucg_font_timr08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timR08.bdf ucg_font_timR08r ./pixel/ucg_font_timr08r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timR10.bdf ucg_font_timR10 ./pixel/ucg_font_timr10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timR10.bdf ucg_font_timR10r ./pixel/ucg_font_timr10r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timR12.bdf ucg_font_timR12 ./pixel/ucg_font_timr12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timR12.bdf ucg_font_timR12r ./pixel/ucg_font_timr12r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timR14.bdf ucg_font_timR14 ./pixel/ucg_font_timr14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timR14.bdf ucg_font_timR14r ./pixel/ucg_font_timr14r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timR18.bdf ucg_font_timR18 ./pixel/ucg_font_timr18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timR18.bdf ucg_font_timR18r ./pixel/ucg_font_timr18r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/timR24.bdf ucg_font_timR24 ./pixel/ucg_font_timr24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/timR24.bdf ucg_font_timR24r ./pixel/ucg_font_timr24r.c > /dev/null
../bdf2ucg/bdf2ucg  -b 42 -e 58  ../bdf/timR24.bdf ucg_font_timR24n ./pixel/ucg_font_timr24n.c > /dev/null

echo "adobe symb"
../bdf2ucg/bdf2ucg ../bdf/symb08.bdf ucg_font_symb08 ./pixel/ucg_font_symb08.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/symb08.bdf ucg_font_symb08r ./pixel/ucg_font_symb08r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/symb10.bdf ucg_font_symb10 ./pixel/ucg_font_symb10.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/symb10.bdf ucg_font_symb10r ./pixel/ucg_font_symb10r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/symb12.bdf ucg_font_symb12 ./pixel/ucg_font_symb12.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/symb12.bdf ucg_font_symb12r ./pixel/ucg_font_symb12r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/symb14.bdf ucg_font_symb14 ./pixel/ucg_font_symb14.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/symb14.bdf ucg_font_symb14r ./pixel/ucg_font_symb14r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/symb18.bdf ucg_font_symb18 ./pixel/ucg_font_symb18.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/symb18.bdf ucg_font_symb18r ./pixel/ucg_font_symb18r.c > /dev/null
../bdf2ucg/bdf2ucg ../bdf/symb24.bdf ucg_font_symb24 ./pixel/ucg_font_symb24.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127 ../bdf/symb24.bdf ucg_font_symb24r ./pixel/ucg_font_symb24r.c > /dev/null


echo "contributed"
../bdf2ucg/bdf2ucg  -b 32 -e 127  ../bdf/freedoomr25n.bdf ucg_font_freedoomr25n ./pixel/ucg_font_freedoomr25n.c > /dev/null
../bdf2ucg/bdf2ucg  -b 32 -e 127  ../bdf/freedoomr10r.bdf ucg_font_freedoomr10r ./pixel/ucg_font_freedoomr10r.c > /dev/null


echo "fontstruct"
./do_fontsize_pixel.sh 8 ../ttf/pixel/p01type.ttf p01type
./do_fontsize_pixel.sh 8 ../ttf/pixel/lucasfont_alternate.ttf lucasfont_alternate
./do_fontsize_pixel.sh 8 ../ttf/pixel/chikita.ttf chikita
./do_fontsize_pixel.sh 8 ../ttf/pixel/pixelle_micro.ttf pixelle_micro
./do_fontsize_pixel.sh 8 ../ttf/pixel/trixel_square.ttf trixel_square
./do_fontsize_pixel.sh 16 ../ttf/pixel/robot_de_niro.ttf robot_de_niro
./do_fontsize_pixel.sh 8 ../ttf/pixel/baby.ttf baby
./do_fontsize_pixel.sh 8 ../ttf/pixel/blipfest_07.ttf blipfest_07

echo "04B"
./do_fontsize_pixel_f1.sh 8 ../ttf/pixel/04B_03B_.TTF 04b_03b 
./do_fontsize_pixel_f1.sh 8 ../ttf/pixel/04B_03__.TTF 04b_03 
./do_fontsize_pixel_f1.sh 8 ../ttf/pixel/04B_24__.TTF 04b_24 

echo "orgdot"
./do_fontsize_pixel.sh 8 ../ttf/pixel/TEACPSS_.TTF tpss 
./do_fontsize_pixel.sh 8 ../ttf/pixel/TEACPSSB.TTF tpssb 
./do_fontsize_pixel_f1.sh 8 ../ttf/pixel/ORG_V01_.TTF orgv01 
./do_fontsize_pixel_f1.sh 8 ../ttf/pixel/FIXED_V0.TTF fixed_v0 



echo "various ttf"

#./do_fontsize.sh 15 ../ttf/GenBasR.ttf gdr9
#./do_fontsize.sh 17 ../ttf/GenBasR.ttf gdr10
#./do_fontsize.sh 18 ../ttf/GenBasR.ttf gdr11
#./do_fontsize.sh 19 ../ttf/GenBasR.ttf gdr12
#./do_fontsize.sh 23 ../ttf/GenBasR.ttf gdr14
#./do_fontsize.sh 27 ../ttf/GenBasR.ttf gdr17
#./do_fontsize.sh 32 ../ttf/GenBasR.ttf gdr20
#./do_fontsize.sh 40 ../ttf/GenBasR.ttf gdr25
#./do_fontsize.sh 48 ../ttf/GenBasR.ttf gdr30
  
#./do_fontsize.sh 18 ../ttf/GenBasB.ttf gdb11
#./do_fontsize.sh 19 ../ttf/GenBasB.ttf gdb12
#./do_fontsize.sh 23 ../ttf/GenBasB.ttf gdb14
#./do_fontsize.sh 27 ../ttf/GenBasB.ttf gdb17
#./do_fontsize.sh 32 ../ttf/GenBasB.ttf gdb20
#./do_fontsize.sh 40 ../ttf/GenBasB.ttf gdb25
#./do_fontsize.sh 48 ../ttf/GenBasB.ttf gdb30

./do_fontsize_a.sh 16 ../ttf/fu/FreeUniversal-Bold.ttf fub11
./do_fontsize_a.sh 20 ../ttf/fu/FreeUniversal-Bold.ttf fub14
./do_fontsize_a.sh 23 ../ttf/fu/FreeUniversal-Bold.ttf fub17
./do_fontsize_a.sh 27 ../ttf/fu/FreeUniversal-Bold.ttf fub20
./do_fontsize_a.sh 34 ../ttf/fu/FreeUniversal-Bold.ttf fub25
./do_fontsize_a.sh 40 ../ttf/fu/FreeUniversal-Bold.ttf fub30
./do_fontsize_a_n.sh 49 ../ttf/fu/FreeUniversal-Bold.ttf fub35n
./do_fontsize_a_n.sh 58 ../ttf/fu/FreeUniversal-Bold.ttf fub42n
./do_fontsize_a_n.sh 68 ../ttf/fu/FreeUniversal-Bold.ttf fub49n
  
./do_fontsize_a.sh 15 ../ttf/fu/FreeUniversal-Regular.ttf fur11
./do_fontsize_a.sh 19 ../ttf/fu/FreeUniversal-Regular.ttf fur14
./do_fontsize_a.sh 23 ../ttf/fu/FreeUniversal-Regular.ttf fur17
./do_fontsize_a.sh 28 ../ttf/fu/FreeUniversal-Regular.ttf fur20
./do_fontsize_a.sh 34 ../ttf/fu/FreeUniversal-Regular.ttf fur25
./do_fontsize_a.sh 40 ../ttf/fu/FreeUniversal-Regular.ttf fur30
./do_fontsize_a_n.sh 48 ../ttf/fu/FreeUniversal-Regular.ttf fur35n
./do_fontsize_a_n.sh 58 ../ttf/fu/FreeUniversal-Regular.ttf fur42n
./do_fontsize_a_n.sh 68 ../ttf/fu/FreeUniversal-Regular.ttf fur49n

./do_fontsize_a.sh 25 ../ttf/os/OldStandard-Bold.ttf osb18
./do_fontsize_a.sh 28 ../ttf/os/OldStandard-Bold.ttf osb21
./do_fontsize_a.sh 34 ../ttf/os/OldStandard-Bold.ttf osb26
./do_fontsize_a.sh 38 ../ttf/os/OldStandard-Bold.ttf osb29
./do_fontsize_a.sh 48 ../ttf/os/OldStandard-Bold.ttf osb35
#./do_fontsize_a.sh 55 ../ttf/os/OldStandard-Bold.ttf osb41

./do_fontsize_a.sh 26 ../ttf/os/OldStandard-Regular.ttf osr18
./do_fontsize_a.sh 29 ../ttf/os/OldStandard-Regular.ttf osr21
./do_fontsize_a.sh 36 ../ttf/os/OldStandard-Regular.ttf osr26
./do_fontsize_a.sh 41 ../ttf/os/OldStandard-Regular.ttf osr29
./do_fontsize_a.sh 49 ../ttf/os/OldStandard-Regular.ttf osr35
#./do_fontsize_a.sh 57 ../ttf/os/OldStandard-Reglar.ttf osr41

echo "logisoso"

./do_fontsize_a.sh 23 ../ttf/log/Logisoso.ttf logisoso16
./do_fontsize_a.sh 27 ../ttf/log/Logisoso.ttf logisoso18
./do_fontsize_a.sh 30 ../ttf/log/Logisoso.ttf logisoso20
./do_fontsize_a.sh 32 ../ttf/log/Logisoso.ttf logisoso22
./do_fontsize_a.sh 34 ../ttf/log/Logisoso.ttf logisoso24
./do_fontsize_a.sh 38 ../ttf/log/Logisoso.ttf logisoso26
./do_fontsize_a.sh 40 ../ttf/log/Logisoso.ttf logisoso28
./do_fontsize_a_no_64.sh 43 ../ttf/log/Logisoso.ttf logisoso30
./do_fontsize_a_no_64.sh 45 ../ttf/log/Logisoso.ttf logisoso32
./do_fontsize_a_no_64.sh 49 ../ttf/log/Logisoso.ttf logisoso34
./do_fontsize_a_no_64.sh 54 ../ttf/log/Logisoso.ttf logisoso38
./do_fontsize_a_no_64.sh 60 ../ttf/log/Logisoso.ttf logisoso42
./do_fontsize_a_no_64.sh 66 ../ttf/log/Logisoso.ttf logisoso46
./do_fontsize_a_no_64.sh 71 ../ttf/log/Logisoso.ttf logisoso50
./do_fontsize_a_n.sh  77 ../ttf/log/Logisoso.ttf logisoso54n
./do_fontsize_a_n.sh  83 ../ttf/log/Logisoso.ttf logisoso58n
./do_fontsize_a_n.sh  89 ../ttf/log/Logisoso.ttf logisoso62n

echo "execute do_combine.sh after executing this script"
