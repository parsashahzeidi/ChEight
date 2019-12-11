#! /bin/bash

# Initialization
rm ./BIN/main
rm ./BIN/main.out
clear

# Compilation
/usr/bin/g++-9 \
	"/home/jamiejacker/Documents/VS code/CHEIGHT/ChEight/UI/main.cpp" \
	-O0 -Wpedantic -Werror -std=c++17 -m64 -pthread \
	$(wx-config --libs --cppflags) \
	-o "/home/jamiejacker/Documents/VS code/CHEIGHT/ChEight/BIN/main.out" && 
echo Compilation done successfully. 

# Linking
ld \
	"/home/jamiejacker/Documents/VS code/CHEIGHT/ChEight/BIN/main.out" \
	-o "/home/jamiejacker/Documents/VS code/CHEIGHT/ChEight/BIN/main" && 
echo Linking done successfully.

# Running
./Launch.sh
