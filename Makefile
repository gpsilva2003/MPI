#
# Makefile 
# Compila e gera os executáveis de todos os arquivos com extensão .c
# presentes no diretório
#
CC=mpicc
CFLAGS = -O3 -Wall
LIBS=-lm
RM=rm -vf
MV=mv
BINDIR=./bin/
SRCDIR=./src/

vpath %.c ./src/

SRCFILES= $(wildcard src/*.c)
OBJFILES= $(patsubst src/%.c, %.o, $(SRCFILES))
_PROGS= $(patsubst src/%.c, %, $(SRCFILES))
PROGFILES=$(addprefix $(BINDIR),$(_PROGS))

.PHONY: all clean run

all: $(PROGFILES)

$(BINDIR)%: $(SRCDIR)%.c
	$(CC) $(INC) $< $(CFLAGS) -o $@ $(LIBS)

clean:
	$(RM) $(OBJFILES) $(PROGFILES) *~
## eof Makefile

