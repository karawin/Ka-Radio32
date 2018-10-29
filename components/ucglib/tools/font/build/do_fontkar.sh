#!/bin/sh
#
# arg 1: bdf file 
#
ARG1=$1
BDF=../bdf/win_${ARG1}.bdf
CFILE=../karadio32/ucg_font_${ARG1}.c
IDENTIFIER=ucg_font_${ARG1}
echo ${IDENTIFIER}  ... ${CFILE}
../bdfconv/bdfconv.exe -f 0 -b 0 ${BDF}  -r   -n ${IDENTIFIER} -o ${CFILE}
