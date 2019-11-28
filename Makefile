CC=g++

CFLAGS = -O3 -w

<<<<<<< HEAD
all: compile run

run: login
	./login

vpath %.h /header
compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login

.PHONY: all run
=======
compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login

>>>>>>> 43f5817b9a64695525d6bb5372fb0d80f3e56d83
clean:
	rm -rf login 