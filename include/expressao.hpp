#ifndef EXPRESSAO_HPP
#define EXPRESSAO_HPP

#include "infixa.hpp"
#include "posfixa.hpp"
#include <string>

class Expressao {
    private:
        std::string str_expressao;
        Posfixa posfixa;
        Infixa infixa;
        int tipo_exp;
    public:
        bool lePosfixa(std::string expressao);
        bool leInfixa(std::string expressao);
        bool infParaPos();
        bool posParaInf();
        double resolve();
        std::string getExp();
        std::string getTipoExp();
};

#endif //EXPRESSAO_HPP