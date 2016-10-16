EXE = mp2
# OBJS = mp1.cpp bfs.o dfs.o greedy_search.o astar.o amul.o
OBJS = mp2.cpp

COMPILER = g++
COMPILER_OPTS = -c -g -std=c++11 -Wall -pedantic -Werror
LINKER = g++

all : $(EXE) 

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) -o $(EXE)

# amul.o : amul.h amul.cpp
	# $(COMPILER) $(COMPILER_OPTS) amul.cpp
	
clean :
	-rm -f *.o $(EXE)