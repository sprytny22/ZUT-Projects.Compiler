CPP=g++
LEX=flex
YACC=bison
LD=gcc

all:	leks

leks:	def.tab.o lex.yy.o
	$(LD) lex.yy.o def.tab.o -o leks -ll -lstdc++ 

lex.yy.o:	lex.yy.c
	$(CPP) -std=c++11 -c lex.yy.c

lex.yy.c: lex.l
	$(LEX) -d lex.l

def.tab.o:	def.tab.cc
	$(CPP) -std=c++11 -Wall -c def.tab.cc

def.tab.cc:	def.yy
	$(YACC) -d def.yy

clean:
	rm *.o leks def.tab.cc lex.yy.c