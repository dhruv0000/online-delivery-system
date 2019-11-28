CC=g++

CFLAGS = -O3 -w

<<<<<<< HEAD
<<<<<<< HEAD
all: compile run
=======
all: compile clear run

clear: login
	clear
>>>>>>> cc7c8bc139673c3ac7bf75c725e2916fa5a05635

run: login
	./login

<<<<<<< HEAD
vpath %.h /header
compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login

.PHONY: all run
=======
compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login

>>>>>>> 43f5817b9a64695525d6bb5372fb0d80f3e56d83
=======
compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login

.PHONY: all run clear

>>>>>>> cc7c8bc139673c3ac7bf75c725e2916fa5a05635
clean:
	rm -rf login 