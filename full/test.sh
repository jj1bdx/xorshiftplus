#!/bin/bash

bits=$1

export IFS=$'\t'

grep "	1\$" irred${bits}.txt | cut -f1,2 | while read NAME POLY; do
	# Set polynomial modulo
	echo -en "===== $NAME ====="
	( echo -e "&t;\n&E;\n&a;\n&(_d=10000);\n&(p=2);\n&(J=x);\n&(P=$POLY);"; java it.unimi.dsi.test.XorShiftPoly $bits; echo -e "!!('$NAME OK');\n&q" ) | fer64 
done
