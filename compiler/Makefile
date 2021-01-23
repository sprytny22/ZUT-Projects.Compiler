CC=gcc
LEX=flex
YACC=bison
LD=gcc
CPP=g++
LD=g++

all:	golonka

golonka:	def.tab.o lex.yy.o
	$(CPP) -std=c++11 lex.yy.o def.tab.o ./src/* -o golonka -ll

lex.yy.o:	lex.yy.c
	$(CC) -c lex.yy.c

lex.yy.c: lex.l
	$(LEX) lex.l

def.tab.o:	def.tab.cc
	$(CPP)  -std=c++11 -c def.tab.cc ./src/*

def.tab.cc:	def.yy
	$(YACC) -d def.yy
clean:
	rm *.o golonka def.tab.cc lex.yy.c
