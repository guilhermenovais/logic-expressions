#ifndef EXPRESSAO_HPP
#define EXPRESSAO_HPP

#include "arvore_binaria.hpp"
#include <string>

#define UNIVERSAL 2
#define EXISTENCIAL 3
#define DONT_CARE 4

class Expressao {
    private:
        ArvoreBinaria arvore_expressao;
        int valores[100];
        int qtd_valores;
        std::string tipo;
    public:
        Expressao(std::string str_expressao, std::string str_valores, std::string str_tipo);
        void constroiArvore(std::string expressao);
        void leValor(TipoNo** raiz, TipoNo** anterior, std::string expressao, int indice);
        int getPrecedencia(std::string valor);
        void calculaExpressao();
        void avaliaValores();
        bool avaliaSatisfabilidade(int* variaveis);
        void mergeVariaveis(int* variaveis_1, int* variaveis_2, int* variaveis_mergeadas);
};

#endif //EXPRESSAO_HPP