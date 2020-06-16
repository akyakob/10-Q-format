CC = gcc
CFLAGS = -O3 -g -Wall -std=c99 -pedantic -lm -DEN_TIME
MFLAGS = -O3 -g -Wall -std=c99 -pedantic -lm
SOURCE = intTest.c rootfinding.c
OBJ = $(patsubst %.c, %.o, $(SOURCE))
EXE = intTest
EXEMEM = intTest_mem
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes 
RESULTS = out.txt
MEMTXT = mem.txt
VERB = VERBOSE

.SILENT:
all: $(EXE) $(EXEMEM)

$(EXE): $(SOURCE)
	@echo "Compiling intTest with timing enabled"
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE)

$(EXEMEM): $(SOURCE)
	@echo "Compiling intTest with timing disabled"
	$(CC) $(MFLAGS) $(SOURCE) -o $(EXEMEM)

test: $(EXE) 
	@echo "Testing... "
	./$(EXE) > $(RESULTS) 2>&1
	@echo "check out.txt for results"

.PHONY: mem clean test all help
mem: $(EXEMEM)
	@echo "running valgrind..."
	$(VALGRIND) ./$(EXEMEM) > $(MEMTXT) 2>&1
	@echo "valgrind output in mem.txt"

clean: 
	-rm -f $(EXE) $(RESULTS) $(MEMTXT) $(EXEMEM)

help:
	@echo "make options are: all, clean, mem, test"

