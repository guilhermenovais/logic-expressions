#include "../include/expressao.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>

Expressao::Expressao(std::string expressao, std::string valores, std::string str_tipo) {
    constroiArvore(expressao);
    if(tipo == "-a") tipo = "avaliador" ;
    else tipo =  "satisfabilidade";
}

void Expressao::constroiArvore(std::string expressao) {
    TipoNo* raiz = nullptr;
    leValor(&raiz, &raiz, expressao, 0);
    arvore_expressao = ArvoreBinaria();
    arvore_expressao.defineRaiz(raiz);
    std::cout << "\n\n";
    arvore_expressao.caminha(1);
    std::cout << "\n\n";
}

void Expressao::leValor(TipoNo** raiz, TipoNo** anterior, std::string expressao, int indice) {
    // Pula espaços
    while (indice < expressao.length()) {
        if(expressao[indice] == ' ') indice++;
        else break;
    }

    if(indice >= expressao.length()) {
        return;
    }

    TipoNo* atual = new TipoNo(expressao[indice]);

    if(*raiz == nullptr) *raiz = atual;
    else if(atual->valor == '(') {
        atual->pai = *anterior;
        (*anterior)->dir = atual;
    } else if(atual->valor == ')') {
        TipoNo* candidato_a_filho = *anterior;
        while(1) {
            if(candidato_a_filho->valor == '(') {
                atual->pai = candidato_a_filho->pai;
                candidato_a_filho->pai->dir = atual;
                atual->esq = candidato_a_filho;
                candidato_a_filho->pai = atual;
                break;
            }
            candidato_a_filho = candidato_a_filho->pai;
        }
    } else {
        TipoNo* candidato_a_pai = *anterior;
        while(1) {
            // Caso a precedência do pai seja menor
            if(getPrecedencia(atual->valor) > getPrecedencia(candidato_a_pai->valor)) {
                atual->pai = candidato_a_pai;
                candidato_a_pai->dir = atual;
                break;
            // Caso a precedência do pai seja maior
            } else {
                // Caso o pai seja raiz
                if(candidato_a_pai == *raiz) {
                    atual->esq = candidato_a_pai;
                    candidato_a_pai->pai = atual;
                    *raiz = atual;
                    break;
                } else {
                    // Caso a precedência do pai seja maior mas a precedência do avô seja menor
                    if(getPrecedencia(atual->valor) > getPrecedencia(candidato_a_pai->pai->valor)) {
                        atual->pai = candidato_a_pai->pai;
                        candidato_a_pai->pai->dir = atual;
                        atual->esq = candidato_a_pai;
                        candidato_a_pai->pai = atual;
                        break;
                    // Caso o pai e o avô tenham precedência menor
                    } else {
                        candidato_a_pai = candidato_a_pai->pai;
                    }
                }
            }
        }
    }

    leValor(raiz, &atual, expressao, indice + 1);
}

int Expressao::getPrecedencia(char valor) {
    if(valor == '(') return 0;
    else if(valor == '|') return 1;
    else if(valor == '&') return 2;
    else if(std::isdigit(valor)) return 3;
    else if(valor == ')') return 4;
    else return 5;
}

// bool Expressao::lePosfixa(std::string expressao) {
//     tipo_exp = 0;
//     bool exp_valida = posfixa.leExpressao(expressao);
//     if(exp_valida) str_expressao = expressao;
//     return exp_valida;
// }

// bool Expressao::leInfixa(std::string expressao) {
//     tipo_exp = 1;
//     bool exp_valida = infixa.leExpressao(expressao);
//     if(exp_valida) str_expressao = expressao;
//     return exp_valida;
// }

// bool Expressao::infParaPos() {
//     if(str_expressao.empty()) return false;
    
//     try {
//         str_expressao = posfixa.infParaPos(str_expressao);
//         tipo_exp = 0;
//         return true;
//     } catch (const std::exception& e) {
//         return false;
//     }
// }

// bool Expressao::posParaInf() {
//     if(str_expressao.empty()) return false;
//     try {
//         str_expressao = infixa.posParaInf(str_expressao);
//         tipo_exp = 1;
//         return true;
//     } catch (const std::exception& e) {
//         return false;
//     }
// }

// double Expressao::resolve() {
//     if(tipo_exp == 0) {
//         return posfixa.resolve();
//     } else if(tipo_exp == 1) {
//         return infixa.resolve();
//     }

//     throw std::domain_error("ERRO: EXP NAO EXISTE");
// }

// std::string Expressao::getExp() {
//     return str_expressao;
// }

// std::string Expressao::getTipoExp() {
//     if(tipo_exp == 0) {
//         return "POSFIXA";
//     } else {
//         return "INFIXA";
//     }
// }