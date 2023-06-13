PROJ_NAME=myht
 
C_SOURCE=$(wildcard *.c)
H_SOURCE=$(wildcard *.h)
 
OBJ=$(C_SOURCE:.c=.o)
 
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c         \
				 -W         \
				 -Wall      \

LIBS=-lm

# Compilation and linking
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
		$(CC) -o $@ $^ $(LIBS)
 
%.o: %.c %.h
		$(CC) -o $@ $< $(CC_FLAGS)
 
main.o: main.c $(H_SOURCE)
		$(CC) -o $@ $< $(CC_FLAGS) 

test:
		./$(PROJ_NAME) < teste1.in > teste.out
		diff -w teste.out teste1.out
		./$(PROJ_NAME) < teste2.in > teste.out
		diff -w teste.out teste2.out
		./$(PROJ_NAME) < teste3.in > teste.out
		diff -w teste.out teste3.out
		./$(PROJ_NAME) < teste4.in > teste.out
		diff -w teste.out teste4.out

		rm teste.out

clean:
		rm -rf *.o $(PROJ_NAME) *~