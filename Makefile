CC=g++
CFLAGS = 
vpath %.h /header

.PHONY: all run clear clean

all: compile clear run

clear: clear
	clear

run: login
	./login


compile:test_login.cpp
	$(CC) $(CFLAGS) test_login.cpp -o login -lncurses



clean:
	rm -rf login 