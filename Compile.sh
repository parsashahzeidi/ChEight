#! /bin/bash
clear
g++-9 ./UI/main.cpp -Ofast -Wpedantic -Werror -std=c++17 -m64 -pthread $(wx-config --libs --cppflags) -o ./main && ./Launch.sh

