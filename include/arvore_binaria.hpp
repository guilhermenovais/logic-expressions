#ifndef ARVORE_BINARIA_HPP
#define ARVORE_BINARIA_HPP

#include <string>
#include "../include/no.hpp"

class ArvoreBinaria {
    public:
        ArvoreBinaria();
        ~ArvoreBinaria();
        void insere(std::string valor);
        void caminha(int tipo);
        void limpa();
        void defineRaiz(TipoNo* p);
        void calculaResultados(int* valores);
        TipoNo *raiz;
    protected:
        void insereRecursivo(TipoNo* &p, std::string valor);
        void apagaRecursivo(TipoNo* p);
        void porNivel();
        void preOrdem(TipoNo* p);
        void inOrdem(TipoNo* p);
        void posOrdem(TipoNo* p, int* valores);
};

#endif //ARVORE_BINARIA_HPP