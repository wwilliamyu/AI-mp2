EXE = mp2
OBJS = mp2.cpp sudoku.o

COMPILER = g++
COMPILER_OPTS = -c -g -std=c++11 -Wall -pedantic -Werror 
LINKER = g++

all : $(EXE) 

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) -o $(EXE)

sudoku.o : sudoku.h sudoku.cpp
	$(COMPILER) $(COMPILER_OPTS) sudoku.cpp
	
clean :
	-rm -f *.o $(EXE)