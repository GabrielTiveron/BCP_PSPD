# Executavel
BINFOLDER := bin/
# .hpp
INCFOLDER := inc/
# .cpp
SRCFOLDER := src/
# .o
OBJFOLDER := obj/

CC := g++

CFLAGS := -W -Wall -ansi -O2 -static -pedantic -std=c++0x

# Qualquer coisa de extensão .cpp
SRCFILES := $(wildcard src/*.cpp)

# SRCFILES transforma o .cpp em .o para a pasta obj
all: create_folders $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) $(CFLAGS) obj/*.o -o bin/prog

# Compila o programa classe por classe.
obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I./inc

create_folders:
	@mkdir -p $(OBJFOLDER) $(BINFOLDER)
run: bin/prog
	bin/prog

.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*
