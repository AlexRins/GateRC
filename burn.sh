#!/usr/bin/env bash

# Dependencis
# avrdude version 6.3

# relative to script .HEX file path

project="VGA_PS2"
relativePath="/bin/$project.hex"

dir=$(dirname $(readlink -f $0))
cd $dir

# Prpgramming
echo "PROGRAMMING STAGE"

# choose USB
LSL=$(ls /dev/tty* | grep -e USB -e ACM)
declare -a ARR
ARR=($LSL)

echo ${ARR[@]}
select PORT in ${ARR[@]}
do
#	bash burn.sh $PORT
    avrdude -p atmega328p -c arduino -b 115200 -P $PORT -U flash:w:"$dir$relativePath":i
	exit
done

# avrdude -p atmega328p -c arduino -b 115200 -P $1 -U flash:w:"$dir$relativePath":i

