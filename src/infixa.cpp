#include "../include/infixa.hpp"
#include <cstddef>

bool Infixa::leExpressao(std::string expressao) {
    raiz = criaOperacao(&raiz, expressao, 0);
    return raiz != NULL;
}

double Infixa::resolve() {
    return resolveNo(raiz);
}

double Infixa::resolveNo(TipoNo *p) {
    if(p->valor == "+" || p->valor == "-" || p->valor == "*" || p->valor == "/") {
        char operacao = p->valor[0];
        switch (operacao) {
            case '+':
                return resolveNo(p->esq) + resolveNo(p->dir);
                break;
            case '-':
                return resolveNo(p->esq) - resolveNo(p->dir);
                break;
            case '*':
                return resolveNo(p->esq) * resolveNo(p->dir);
                break;
            case '/':
                return resolveNo(p->esq) / resolveNo(p->dir);
                break;
        }
    }

    return std::stod(p->valor);
}

std::string Infixa::posParaInf(std::string posfixa) {
    Pilha pilha;
    for (int i = 0; i < posfixa.length(); i++) {
        char caractere = posfixa[i];
        if (isdigit(caractere)) {
            std::string temp;
            for(; isdigit(posfixa[i]) || posfixa[i] == '.' || posfixa[i] == ','; i++) {
                temp += posfixa[i];
            }
            pilha.empilha(temp);
        }
        else if (caractere == '+' || caractere == '-' || caractere == '*' || caractere == '/') {
            std::string op2 = pilha.desempilha();
            std::string op1 = pilha.desempilha();
            std::string temp = "(" + op1 + caractere + op2 + ")";
            pilha.empilha(temp);
        }
    }
    std::string resultado = pilha.desempilha();
    leExpressao(resultado);
    return resultado;
}

TipoNo* Infixa::criaOperacao(TipoNo** anterior, std::string expressao, int indice) {
    // Pula espaços
    while (indice < expressao.length()) {
        if(expressao[indice] == ' ') indice++;
        else break;
    }
    
    if(indice >= expressao.length()) {
        return *anterior;
    }

    if(isdigit(expressao[indice])) {
        std::string operando = "";
        for(; isdigit(expressao[indice]) || expressao[indice] == ',' || expressao[indice] == '.'; indice++) {
            if(expressao[indice] == ',' || expressao[indice] == '.') operando += '.';
            else operando += expressao[indice];

            if(indice >= expressao.length()) break;
        }
        TipoNo* no = new TipoNo(operando);
        return criaOperacao(&no, expressao, indice);
    }

    if(expressao[indice] == '+' || expressao[indice] == '-' || expressao[indice] == '*' || expressao[indice] == '/') {
        TipoNo* no = new TipoNo(std::string(1, expressao[indice]));
        no->esq = *anterior;
        no->dir = criaOperacao(&no, expressao, indice + 1);
        return no;
    }

    if(expressao[indice] == '(') {
        TipoNo* no = criaOperacao(anterior, expressao, indice + 1);
        for(int i = indice; i < expressao.length(); i++) {
            if(expressao[i] == ')') {
                expressao.erase(indice, i);
                return criaOperacao(&no, expressao, indice + 1);
            }
        }
        return no;
    }

    return *anterior;
}

void Infixa::printExp(TipoNo* p) {
    if(p!=NULL){
        std::cout << '(';
        printExp(p->esq);
        std::cout << p->valor;
        printExp(p->dir);
        std::cout << ')';
    }
}