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
OBJS = $(OBJ)/arvore_binaria.o $(OBJ)/no.o $(OBJ)/pilha.o $(OBJ)/expressao.o $(OBJ)/main.o
HDRS = $(INC)/arvore_binaria.hpp $(INC)/no.hpp $(INC)/pilha.hpp $(INC)/expressao.hpp
CFLAGS = -c -I $(INC)

EXE = $(BIN)/expressoes

all:  $(EXE)

$(BIN)/expressoes: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/arvore_binaria.o: $(HDRS) $(SRC)/arvore_binaria.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/arvore_binaria.o $(SRC)/arvore_binaria.cpp 

$(OBJ)/no.o: $(HDRS) $(SRC)/no.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/no.o $(SRC)/no.cpp 

$(OBJ)/pilha.o: $(HDRS) $(SRC)/pilha.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/pilha.o $(SRC)/pilha.cpp 

$(OBJ)/expressao.o: $(HDRS) $(SRC)/expressao.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/expressao.o $(SRC)/expressao.cpp 

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

run: all
	./bin/expressoes -a "0 | 1" 01

test: all
	clear
	./bin/expressoes -a "0 | 1" 01