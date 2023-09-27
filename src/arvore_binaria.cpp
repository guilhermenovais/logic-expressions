#include "../include/arvore_binaria.hpp"
#include <iostream>

ArvoreBinaria::ArvoreBinaria() {
    raiz = NULL;
}

ArvoreBinaria::~ArvoreBinaria() {
    limpa();
}

void ArvoreBinaria::insere(std::string valor) {
    insereRecursivo(raiz,valor);
}

void ArvoreBinaria::insereRecursivo(TipoNo* &p, std::string valor) {
    if(p==NULL){
        p = new TipoNo(valor);
    } else{
        if(valor < p->valor)
            insereRecursivo(p->esq, valor);
        else
            insereRecursivo(p->dir, valor);
    }
}

void ArvoreBinaria::preOrdem(TipoNo *p){
    if(p!=NULL){
        std::cout << p->valor;
        preOrdem(p->esq);
        preOrdem(p->dir);
    }
}

void ArvoreBinaria::inOrdem(TipoNo *p){
    if(p!=NULL){
        inOrdem(p->esq);
        std::cout << p->valor;
        inOrdem(p->dir);
    }
}

void ArvoreBinaria::posOrdem(TipoNo *p){
    if(p!=NULL){
        posOrdem(p->esq);
        posOrdem(p->dir);
        std::cout << p->valor;
    }
}

void ArvoreBinaria::limpa(){
    apagaRecursivo(raiz);
    raiz = NULL;
}

void ArvoreBinaria::apagaRecursivo(TipoNo *p){
    if(p!=NULL){
        apagaRecursivo(p->esq);
        apagaRecursivo(p->dir);
        delete p;
    }
}