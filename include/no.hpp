#ifndef NO_HPP
#define NO_HPP

#include <string>

class TipoNo {
    public:
        TipoNo(std::string valor);
        std::string valor;
        bool resultado;
        TipoNo *esq;
        TipoNo *dir;
        TipoNo *pai;
    friend class ArvoreBinaria;
};

#endif //NO_HPP