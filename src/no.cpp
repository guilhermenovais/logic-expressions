#include "../include/no.hpp"

TipoNo::TipoNo(char valor) {
    this->valor = valor;
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
}