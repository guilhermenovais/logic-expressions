#ifndef NO_HPP
#define NO_HPP

class TipoNo {
    public:
        TipoNo(char valor);
        char valor;
        TipoNo *esq;
        TipoNo *dir;
        TipoNo *pai;
    friend class ArvoreBinaria;
};

#endif //NO_HPP