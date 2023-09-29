#ifndef EXPRESSAO_HPP
#define EXPRESSAO_HPP

#include "arvore_binaria.hpp"
#include <string>

class Expressao {
    private:
        ArvoreBinaria arvore_expressao;
        bool valores[100];
        std::string tipo;
        // Posfixa posfixa;
        // Infixa infixa;
        // int tipo_exp;
    public:
        Expressao(std::string expressao, std::string valores, std::string tipo);
        void constroiArvore(std::string expressao);
        void leValor(TipoNo** raiz, TipoNo** anterior, std::string expressao, int indice);
        int getPrecedencia(char valor);
        // bool lePosfixa(std::string expressao);
        // bool leInfixa(std::string expressao);
        // bool infParaPos();
        // bool posParaInf();
        // double resolve();
        // std::string getExp();
        // std::string getTipoExp();
};

#endif //EXPRESSAO_HPP