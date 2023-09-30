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
    public:
        Expressao(std::string str_expressao, std::string str_valores, std::string str_tipo);
        void constroiArvore(std::string expressao);
        void leValor(TipoNo** raiz, TipoNo** anterior, std::string expressao, int indice);
        int getPrecedencia(std::string valor);
        void calculaExpressao();
        void avaliaValores();
        void avaliaSatisfabilidade();
};

#endif //EXPRESSAO_HPP