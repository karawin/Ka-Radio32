#!/bin/sh
#
# arg 1: pt 
# arg 2: ttf name
# arg 3: internalname
#
PT=$1
ARG3=$3
BDF=${ARG3}.bdf
CFILE=./ttf/ucg_font_${ARG3}.c
CFILER=./ttf/ucg_font_${ARG3}r.c
CFILEN=./ttf/ucg_font_${ARG3}n.c
IDENTIFIER=ucg_font_${ARG3}
echo $2  ... ${CFILE}
../otf2bdf/otf2bdf -a -p $1 -r 72 $2 -o ${BDF}
# replace BDF if it exists
if test -r ../ttfbdfupdate/${BDF}; then echo ${BDF} "manual update" &&  cp ../ttfbdfupdate/${BDF} .; fi
../bdf2ucg/bdf2ucg ${BDF} ${IDENTIFIER} ${CFILE} >/dev/null
../bdf2ucg/bdf2ucg -b 32 -e 127 ${BDF} ${IDENTIFIER}r ${CFILER} >/dev/null
../bdf2ucg/bdf2ucg -b 42 -e 58 ${BDF} ${IDENTIFIER}n ${CFILEN} >/dev/null
#cp ${CFILE} ../../../src/.