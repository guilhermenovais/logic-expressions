#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o resolvedor de expressões
# Autor		: Guilherme Novais de Souza
# Histórico	: 2023-09-28 arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo e executa o exemplo
#			: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/arvore_binaria.o $(OBJ)/no.o $(OBJ)/expressao.o $(OBJ)/main.o
HDRS = $(INC)/arvore_binaria.hpp $(INC)/no.hpp $(INC)/expressao.hpp
CFLAGS = -c -g -I $(INC)

EXE = $(BIN)/expressoes

mkdir:
	[ -d obj ] || mkdir obj
	[ -d bin ] || mkdir bin

all: mkdir $(EXE)

$(BIN)/expressoes: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/arvore_binaria.o: $(HDRS) $(SRC)/arvore_binaria.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/arvore_binaria.o $(SRC)/arvore_binaria.cpp 

$(OBJ)/no.o: $(HDRS) $(SRC)/no.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/no.o $(SRC)/no.cpp 

$(OBJ)/expressao.o: $(HDRS) $(SRC)/expressao.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/expressao.o $(SRC)/expressao.cpp 

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

run: all
	./bin/expressoes -a "0 & ( 1 | 2 )" 111

test: all
	valgrind --leak-check=full --show-leak-kinds=all ./bin/expressoes -a "0 & ( 1 | 2 )" 011
	gdb -args ./bin/expressoes -a "0 & ( 1 | 2 )" 011