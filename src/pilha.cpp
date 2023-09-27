#include "../include/pilha.hpp"
#include <stdexcept>

Pilha::Pilha() {
    tamanho = 0;
    topo = -1;
}

int Pilha::getTamanho() {
    return tamanho;
}

bool Pilha::vazia() {
    return tamanho == 0;
}

void Pilha::empilha(std::string item) {
    if(tamanho == MAXTAM)
        throw std::overflow_error("A pilha está cheia");
    topo++;
    itens[topo] = item;
    tamanho++;
}

std::string Pilha::desempilha() {
    if(vazia())
        throw std::underflow_error("Nao pode desempilhar pilha vazia");
    std::string desempilhado = itens[topo];
    topo--;
    tamanho--;
    return desempilhado;
}

void Pilha::limpa() {
    topo = -1;
    tamanho = 0;
}

std::string Pilha::getTopo() {
    if(vazia())
        throw std::underflow_error("Pilha vazia nao tem topo");
    return itens[topo];
}