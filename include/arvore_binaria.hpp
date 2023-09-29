#ifndef ARVORE_BINARIA_HPP
#define ARVORE_BINARIA_HPP

#include <string>
#include "../include/no.hpp"

class ArvoreBinaria {
    public:
        ArvoreBinaria();
        ~ArvoreBinaria();
        void insere(char valor);
        void caminha(int tipo);
        void limpa();
        void defineRaiz(TipoNo* p);
    protected:
        void insereRecursivo(TipoNo* &p, char valor);
        void apagaRecursivo(TipoNo* p);
        void porNivel();
        void preOrdem(TipoNo* p);
        void inOrdem(TipoNo* p);
        void posOrdem(TipoNo* p);
        TipoNo *raiz;
};

#endif //ARVORE_BINARIA_HPP