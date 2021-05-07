#!/usr/bin/env bash

# Dependencis
# avr-gcc (GCC) 5.4.0
project="GateRC"
dir=$(dirname $(readlink -f $0))

cd $dir
echo "------------------------------------------"
echo "Removing old compilations"
rm -r "$dir/bin/"
mkdir ./bin

echo "COMPILE STAGE"
CPP_FLAGS="-I/$dir/mylib"
for f in $(find /$dir -name '*.cpp')
do
	filename=$(basename -- "$f")
	filenamenoext="${filename%.*}"
	echo $f
	avr-gcc -Os -Wall $CPP_FLAGS -mmcu=atmega328p -DF_CPU=16000000 -c "$f" -o "$dir/bin/$filenamenoext.o"
done

echo ""
echo "LINKING STAGE"
for f in "$dir"/bin/*.o
do
	filename=$(basename -- "$f")
	fileslist="$fileslist $dir/bin/$filename"
done

#echo $fileslist
avr-gcc -mmcu=atmega328p -DF_CPU=16000000 $fileslist -o "$dir/bin/$project.elf"
avr-objcopy -O ihex -j .text -j .data "$dir/bin/$project.elf" "$dir/bin/$project.hex"

