#include "../include/posfixa.hpp"
#include <iostream>

// Obtém a precedência do operador
int obterPrecedencia(std::string operador) {
    if (operador == "*" || operador == "/") {
        return 2;
    }
    else if (operador == "+" || operador == "-") {
        return 1;
    }
    else {
        return -1;
    }
}

bool Posfixa::leExpressao(std::string expressao) {
    Pilha operandos;
    std::string op_lido = "";
    for (char c : expressao) {
        if (isdigit(c) || c == ',' || c == '.') {
            op_lido += c;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if(op_lido.length() > 0) {
                operandos.empilha(op_lido);
                op_lido = "";
            }
            if (operandos.getTamanho() < 2) {
                return false;
            }
            std::string op2 = operandos.desempilha();
            std::string op1 = operandos.desempilha();
            operandos.empilha("resultado");
        } else if(c == ' ') {
            if(op_lido.length() > 0) {
                operandos.empilha(op_lido);
                op_lido = "";
            }
        } else {
            std::cout << "caractere invalido";
            // caractere inválido
            return false;
        }
    }
    this->expressao = expressao;
    return true;
}

double Posfixa::resolve() {
    double op1, op2;
    std::string op_lido = "";
    double result;

    for (char c : expressao) {
        if (isdigit(c)) {
            op_lido += c;
        } else if(c == ',' || c == '.') {
            op_lido += '.';
        } else if(c == '+' || c == '-' || c == '*' || c == '/') {
            if(op_lido.length() > 0) {
                empilha(op_lido);
                op_lido = "";
            }

            op2 = stod(desempilha());
            op1 = stod(desempilha());

            switch(c) {
                case '+': 
                    result = op1 + op2; 
                    break;
                case '-': 
                    result = op1 - op2; 
                    break;
                case '*': 
                    result = op1 * op2; 
                    break;
                case '/':
                    result = op1 / op2; 
                    break;
            }
            empilha(std::to_string(result));
        } else if(c == ' ') {
            if(op_lido.length() > 0) {
                empilha(op_lido);
                op_lido = "";
            }
        }
    }

    result = stod(desempilha());
    return result;
}

std::string Posfixa::infParaPos(std::string infixa) {
    Pilha pilha = Pilha();
    std::string resultado;
    for (int i = 0; i < infixa.length(); i++) {
        char caractere = infixa[i];
        if (isdigit(caractere) || caractere == ',' || caractere == '.') {
            resultado += caractere;
        }
        else if(caractere == '+' || caractere == '-' || caractere == '*' || caractere == '/') {
            resultado += ' ';
            while(!pilha.vazia() && pilha.getTopo() != "(" && obterPrecedencia(pilha.getTopo()) >= obterPrecedencia(std::string(1, caractere))) {
                resultado += pilha.desempilha();
            }
            pilha.empilha(std::string(1, caractere));
        }
        else if(caractere == '(') {
            pilha.empilha(std::string(1, caractere));
        }
        else if (caractere == ')') {
            while(!pilha.vazia() && pilha.getTopo() != "(") {
                resultado += pilha.desempilha();
            }
            pilha.desempilha();
        }
    }
    while (!pilha.vazia()) {
        resultado += pilha.desempilha();
    }
    leExpressao(resultado);
    return resultado;
}