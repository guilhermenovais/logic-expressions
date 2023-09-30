#include "../include/expressao.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>

Expressao::Expressao(std::string str_expressao, std::string str_valores, std::string str_tipo) {
    constroiArvore(str_expressao);
    if(str_tipo == "-a") tipo = "avaliador";
    else tipo =  "satisfabilidade";
    for(int i = 0; i < str_valores.length(); i++) {
        if(str_valores[i] == '0') valores[i] = 0;
        else if(str_valores[i] == '1') valores[i] = 1;
        else if(str_valores[i] == 'e') valores[i] = EXISTENCIAL;
        else if(str_valores[i] == 'a') valores[i] = UNIVERSAL;
    }
}

void Expressao::constroiArvore(std::string expressao) {
    TipoNo* raiz = nullptr;
    leValor(&raiz, &raiz, expressao, 0);
    arvore_expressao = ArvoreBinaria();
    arvore_expressao.defineRaiz(raiz);
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

    std::string elemento = "";
    while(1) {
        elemento.push_back(expressao[indice]);
        if(indice + 1 < expressao.length()) {
            if(expressao[indice + 1] != ' ') {
                indice++;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    TipoNo* atual = new TipoNo(elemento);

    if(*raiz == nullptr) *raiz = atual;
    else if(atual->valor == "(") {
        atual->pai = *anterior;
        (*anterior)->dir = atual;
    } else if(atual->valor == ")") {
        TipoNo* candidato_a_filho = *anterior;
        while(1) {
            if(candidato_a_filho->valor == "(") {
                if(candidato_a_filho->pai == nullptr) {
                    *raiz = atual;
                    candidato_a_filho->pai = atual;
                    atual->esq = candidato_a_filho;
                    break;
                } else {
                    atual->pai = candidato_a_filho->pai;
                    candidato_a_filho->pai->dir = atual;
                    atual->esq = candidato_a_filho;
                    candidato_a_filho->pai = atual;
                    break;
                }
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

int Expressao::getPrecedencia(std::string valor) {
    if(valor == "(") return 0;
    else if(valor == "|") return 1;
    else if(valor == "&") return 2;
    else if(valor == "~") return 3;
    else if(valor == ")") return 5;
    // Operando
    else return 4;
}

void Expressao::calculaExpressao() {
    if(tipo == "avaliador") {
        avaliaValores();
    } else {
        avaliaSatisfabilidade();
    }
}

void Expressao::avaliaValores() {
    arvore_expressao.calculaResultados(valores);
    std::cout << arvore_expressao.raiz->resultado;
}

void Expressao::avaliaSatisfabilidade() {
    std::cout << tipo;
}