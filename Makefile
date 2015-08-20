# Makefile
#

CC=gcc
SH = bash
CFLAGS = -g
LDFLAGS = -lm

all: compiler

compiler: lex.yy.c Graph.o y.tab.o Interpreter.o
	gcc -lm $^ -o $@

y.tab.o: y.tab.c y.tab.h
	gcc -c $(CFLAGS) $< -o $@

Graph.o: Graph.c Graph.h
	gcc -c $(CFLAGS) $< -o $@

Interpreter.o: Interpreter.c Interpreter.h Graph.h
	gcc -c $(CFLAGS) $< -o $@

y.tab.c: graph.y Interpreter.h
	yacc -d graph.y

lex.yy.c: graph.l Interpreter.h
	lex graph.l

clean:
	rm -rf *.o;
	rm -rf lex.yy.c
	rm -rf y.tab.c y.tab.h
	rm -rf compiler
