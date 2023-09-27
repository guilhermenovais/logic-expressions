#include "../include/expressao.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>

bool Expressao::lePosfixa(std::string expressao) {
    tipo_exp = 0;
    bool exp_valida = posfixa.leExpressao(expressao);
    if(exp_valida) str_expressao = expressao;
    return exp_valida;
}

bool Expressao::leInfixa(std::string expressao) {
    tipo_exp = 1;
    bool exp_valida = infixa.leExpressao(expressao);
    if(exp_valida) str_expressao = expressao;
    return exp_valida;
}

bool Expressao::infParaPos() {
    if(str_expressao.empty()) return false;
    
    try {
        str_expressao = posfixa.infParaPos(str_expressao);
        tipo_exp = 0;
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool Expressao::posParaInf() {
    if(str_expressao.empty()) return false;
    try {
        str_expressao = infixa.posParaInf(str_expressao);
        tipo_exp = 1;
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

double Expressao::resolve() {
    if(tipo_exp == 0) {
        return posfixa.resolve();
    } else if(tipo_exp == 1) {
        return infixa.resolve();
    }

    throw std::domain_error("ERRO: EXP NAO EXISTE");
}

std::string Expressao::getExp() {
    return str_expressao;
}

std::string Expressao::getTipoExp() {
    if(tipo_exp == 0) {
        return "POSFIXA";
    } else {
        return "INFIXA";
    }
}