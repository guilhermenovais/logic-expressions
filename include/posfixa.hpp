#ifndef POSFIXA_HPP
#define POSFIXA_HPP

#include "pilha.hpp"
#include <string>

class Posfixa:Pilha {
    private:
        std::string expressao;
    public:
        bool leExpressao(std::string expressao);
        double resolve();
        std::string infParaPos(std::string infixa);
};

#endif //POSFIXA_HPP