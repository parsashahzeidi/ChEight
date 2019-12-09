# 
CCF = -ofast -Wpedantic -Werror -std=c++17 -m64 -pthread -o
CC = g++-9

main: ./main.cpp
	$(CC) ./main.cpp &(CCF) $@

