#include "../include/no.hpp"

TipoNo::TipoNo(std::string valor) {
    this->valor = valor;
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
}