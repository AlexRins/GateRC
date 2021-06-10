#!/usr/bin/env bash

# Dependencis
# compile.sh
# burn.sh

dir=$(dirname $(readlink -f $0))
cd $dir
bash compile.sh

# choose USB
LSL=$(ls /dev/tty* | grep -e USB -e ACM)
declare -a ARR
ARR=($LSL)

echo ${ARR[@]}
select PORT in ${ARR[@]}
do
	bash burn.sh $PORT
	exit
done
#bash burn.sh /dev/ttyUSB1