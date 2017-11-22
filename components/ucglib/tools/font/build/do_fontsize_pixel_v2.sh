#!/bin/sh
#
# arg 1: pt 
# arg 2: ttf name
# arg 3: internalname
#
PT=$1
ARG3=$3
BDF=${ARG3}.bdf
CFILE=./pixel/ucg_font_${ARG3}
IDENTIFIER=ucg_font_${ARG3}
echo $2  ... ${CFILE}
../otf2bdf/otf2bdf -p $1 -r 72 $2 -o ${BDF}
# replace BDF if it exists
if test -r ../ttfbdfupdate/${BDF}; then echo ${BDF} "manual update" &&  cp ../ttfbdfupdate/${BDF} .; fi
../bdfconv/bdfconv -b 0 ${BDF} -n ${IDENTIFIER}_tf -o ${CFILE}_tf.c >/dev/null
../bdfconv/bdfconv -b 0 -m '32-127>32'  ${BDF} -n ${IDENTIFIER}_tr -o ${CFILE}_tr.c >/dev/null
../bdfconv/bdfconv -b 0 -m '32,42-58>42' ${BDF} -n ${IDENTIFIER}_tn -o ${CFILE}_tn.c >/dev/null
../bdfconv/bdfconv -b 1 ${BDF} -n ${IDENTIFIER}_hf -o ${CFILE}_hf.c >/dev/null
../bdfconv/bdfconv -b 1 -m '32-127>32'  ${BDF} -n ${IDENTIFIER}_hr -o ${CFILE}_hr.c >/dev/null
../bdfconv/bdfconv -b 1 -m '32,42-58>42' ${BDF} -n ${IDENTIFIER}_hn -o ${CFILE}_hn.c >/dev/null
#cp ${CFILE} ../../../src/.