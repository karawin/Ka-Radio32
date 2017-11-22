#!/bin/bash
#
# for ((i=10; i<40;i=i+1)); do ./do_ttf.sh $i newscycle-regular.ttf; done;
#
# do a test on a specified ttf
#
# arg 1: point
# arg 2: ttf file
#
PT=$1

#../../../tools/font/otf2bdf/otf2bdf -n -p $1 -r 72 $2 -o ucg_font.bdf
#../../../tools/font/bdf2ucg/bdf2ucg -b 32 -e 255 ucg_font.bdf ucg_font ucg_font.c >/dev/null
#echo ">>> make -n"
#make
#echo ">>> font_overview nh"
#./font_overview $2$' nh pt '$1
#mv ucg_font.png ucg_font_${PT}_nh.png

../../../tools/font/otf2bdf/otf2bdf -a -p $1 -r 72 $2 -o ucg_font.bdf
../../../tools/font/bdf2ucg/bdf2ucg -@ -b 32 -e 127 ucg_font.bdf ucg_font ucg_font.c >/dev/null
echo ">>> make -a"
make
echo ">>> font_overview -a"
./font_overview $2$' autohint pt '$1
mv ucg_font.png ucg_font_${PT}_a.png

../../../tools/font/otf2bdf/otf2bdf -p $1 -r 72 $2 -o ucg_font.bdf
../../../tools/font/bdf2ucg/bdf2ucg -@ -b 32 -e 127 ucg_font.bdf ucg_font ucg_font.c >/dev/null
echo ">>> make"
make
echo ">>> font_overview default options"
./font_overview $2$' pt '$1
mv ucg_font.png ucg_font_${PT}_d.png
rm ucg_font.tga


