CC = gcc
INCDIR = header
SRCDIR = src
OBJDIR = obj
CFLAGS = -c -Wall -O2 -static -lpthread -I$(INCDIR)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
EXE = ./BCP

all: clean $(EXE)

$(EXE): $(OBJ)
				$(CC) $(OBJDIR)/*.o -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
							 	@mkdir -p $(@D)
							 	$(CC) $(CFLAGS) $< -o $@

clean:
			-rm -f $(OBJDIR)/*.o $(EXE)
