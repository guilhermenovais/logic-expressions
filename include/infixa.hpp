#ifndef INFIXA_HPP
#define INFIXA_HPP

#include "arvore_binaria.hpp"
#include "no.hpp"
#include "posfixa.hpp"
#include <string>

class Infixa:ArvoreBinaria {
    private:
        TipoNo* criaOperacao(TipoNo** anterior, std::string expressao, int indice);
        double resolveNo(TipoNo *p);
    public:
        bool leExpressao(std::string expressao);
        double resolve();
        std::string posParaInf(std::string posfixa);
        void printExp(TipoNo* p);
};

#endif //INFIXA_HPP