#!/bin/bash

./xpwh.rb $1 >out
for ((i=0; i<$1; i++)); do (cat xpwh; grep "^$i	" out | cut -f2- ; echo '&q') >out-$i; done
for ((i=0; i<$1; i++)); do 
	echo -e "&(R='out-$i');\n&q" | fer64 | egrep "[0-9]+-[0-9]+-[0-9]+" | sed -e 's/ [ ]\+/	/g' >fer-$i &
done

wait
