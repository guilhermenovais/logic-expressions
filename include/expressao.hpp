#ifndef EXPRESSAO_HPP
#define EXPRESSAO_HPP

#include "arvore_binaria.hpp"
#include <string>

#define UNIVERSAL 2
#define EXISTENCIAL 3

class Expressao {
    private:
        ArvoreBinaria arvore_expressao;
        int valores[100];
        std::string tipo;
        // Posfixa posfixa;
        // Infixa infixa;
        // int tipo_exp;
    public:
        Expressao(std::string str_expressao, std::string str_valores, std::string str_tipo);
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