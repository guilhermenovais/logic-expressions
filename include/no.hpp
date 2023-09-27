#ifndef NO_HPP
#define NO_HPP

#include <string>

class TipoNo {
    public:
        TipoNo(std::string valor);
        std::string valor;
        TipoNo *esq;
        TipoNo *dir;
    friend class ArvoreBinaria;
};

#endif //NO_HPP