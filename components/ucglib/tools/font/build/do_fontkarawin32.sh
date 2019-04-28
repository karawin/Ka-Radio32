#!/bin/sh
#
rm ../karadio32/ucg_karadio32_fonts.c
./do_fontkar.sh crox1c
./do_fontkar.sh crox1cb
./do_fontkar.sh crox1h
./do_fontkar.sh crox1hb
./do_fontkar.sh crox1t
./do_fontkar.sh crox1tb
./do_fontkar.sh crox2c
./do_fontkar.sh crox2cb
./do_fontkar.sh crox2h
./do_fontkar.sh crox2hb
./do_fontkar.sh crox2t
./do_fontkar.sh crox2tb
./do_fontkar.sh crox3c
./do_fontkar.sh crox3cb
./do_fontkar.sh crox3h
./do_fontkar.sh crox3hb
./do_fontkar.sh crox3t
./do_fontkar.sh crox3tb
./do_fontkar.sh crox4h
./do_fontkar.sh crox4hb
./do_fontkar.sh crox4t
./do_fontkar.sh crox4tb
./do_fontkar.sh crox5h
./do_fontkar.sh crox5hb
./do_fontkar.sh crox5t
./do_fontkar.sh crox5tb
./do_fontkar.sh 5x7_gr
./do_fontkar.sh 6x13_gr
./do_fontkar.sh 9x15_gr
./do_fontkar.sh 9x16_gr
./do_fontkar.sh helvR12_gr
./do_fontkar.sh helvR14_gr
./do_fontkar.sh helvR18_gr
./do_fontkar.sh helvR24_gr
./do_fontkar.sh ncenR12_gr
./do_fontkar.sh ncenR14_gr
./do_fontkar.sh ncenR24_gr

echo "Generate ucg_karadio32_fonts.c"
cat ../karadio32/*.c >> ../karadio32/ucg_karadio32_fonts.c
echo "copy ucg_karadio32_fonts.c to csrc"
cp ../karadio32/ucg_karadio32_fonts.c ../../../csrc
echo "Success"
