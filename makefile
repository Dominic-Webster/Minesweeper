CC = g++
CFLAGS = -g -Wall -std=c++11

play: main.cc
		$(CC) $(CFLAGS) main.cc -o play