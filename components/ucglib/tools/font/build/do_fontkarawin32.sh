#!/bin/sh
#
rm ../karadio32/ucg_karadio32_fonts.c
./do_crox.sh crox1c
./do_crox.sh crox1cb
./do_crox.sh crox1h
./do_crox.sh crox1hb
./do_crox.sh crox1t
./do_crox.sh crox1tb
./do_crox.sh crox2c
./do_crox.sh crox2cb
./do_crox.sh crox2h
./do_crox.sh crox2hb
./do_crox.sh crox2t
./do_crox.sh crox2tb
./do_crox.sh crox3c
./do_crox.sh crox3cb
./do_crox.sh crox3h
./do_crox.sh crox3hb
./do_crox.sh crox3t
./do_crox.sh crox3tb
./do_crox.sh crox4h
./do_crox.sh crox4hb
./do_crox.sh crox4t
./do_crox.sh crox4tb
./do_crox.sh crox5h
./do_crox.sh crox5hb
./do_crox.sh crox5t
./do_crox.sh crox5tb

#for f in ../karadio32/*.c; do cat $f >>../karadio32/ucg_karadio32_fonts.c; done
cat ../karadio32/*.c >> ../karadio32/ucg_karadio32_fonts.c
cp ../karadio32/ucg_karadio32_fonts.c ../../../csrc
