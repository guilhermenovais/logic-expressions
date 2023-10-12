#include "../include/expressao.hpp"

Expressao::Expressao(std::string str_expressao, std::string str_valores, std::string str_tipo) {
    constroiArvore(str_expressao);
    if(str_tipo == "-a") tipo = "avaliador";
    else tipo =  "satisfabilidade";
    // Grava os valores dos operandos no array de valores
    for(int i = 0; i < str_valores.length(); i++) {
        if(str_valores[i] == '0') valores[i] = 0;
        else if(str_valores[i] == '1') valores[i] = 1;
        else if(str_valores[i] == 'e') valores[i] = EXISTENCIAL;
        else if(str_valores[i] == 'a') valores[i] = UNIVERSAL;
    }
    qtd_valores = str_valores.length();
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
    // Concatena o elemento
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
    // Caso seja abertura de parêntesis, posiciona à direita do anterior
    else if(atual->valor == "(") {
        atual->pai = *anterior;
        (*anterior)->dir = atual;
    // Caso seja fechamento de parêntesis, posiciona acima da abertura de parêntesis
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
            // Caso o pai e o atual sejam NOT
            } else if(getPrecedencia(atual->valor) == getPrecedencia(candidato_a_pai->valor) && atual->valor == "~") {
                atual->dir = candidato_a_pai->dir;
                atual->pai = candidato_a_pai;
                candidato_a_pai->dir = atual;
                break;
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
        bool satisfaz = avaliaSatisfabilidade(valores);
        std::cout << satisfaz;
        if(satisfaz) {
            std::cout << ' ';
            for(int i = 0; i < qtd_valores; i++) {
                if(valores[i] == 0) {
                    std::cout << '0';
                } else if(valores[i] == 1) {
                    std::cout << '1';
                } else if(valores[i] == DONT_CARE) {
                    std::cout << 'a';
                }
            }
        }
        std::cout << '\n';
    }
}

void Expressao::avaliaValores() {
    arvore_expressao.calculaResultados(valores);
    std::cout << arvore_expressao.raiz->resultado << '\n';
}

bool Expressao::avaliaSatisfabilidade(int* variaveis) {
    for(int i = 0; i < qtd_valores; i++) {
        if(variaveis[i] == UNIVERSAL || variaveis[i] == EXISTENCIAL) {
            // Calcula o valor da expressão com a variável igual à 0
            int copia_com_0[100];
            std::copy(variaveis, variaveis + 100, copia_com_0);
            copia_com_0[i] = 0;
            bool satisfaz_com_0 = avaliaSatisfabilidade(copia_com_0);

            // Calcula o valor da expressão com a variável igual à 1
            int copia_com_1[100];
            std::copy(variaveis, variaveis + 100, copia_com_1);
            copia_com_1[i] = 1;
            bool satisfaz_com_1 = avaliaSatisfabilidade(copia_com_1);

            if(variaveis[i] == EXISTENCIAL) {
                if(satisfaz_com_0 && satisfaz_com_1) {
                    mergeVariaveis(copia_com_0, copia_com_1, variaveis);
                    variaveis[i] = DONT_CARE;
                    return true;
                } else if(satisfaz_com_0) {
                    std::copy(copia_com_0, copia_com_0 + 100, variaveis);
                    variaveis[i] = 0;
                    return true;
                } else if(satisfaz_com_1) {
                    std::copy(copia_com_1, copia_com_1 + 100, variaveis);
                    variaveis[i] = 1;
                    return true;
                } else {
                    return false;
                }
            } else {
                if(satisfaz_com_0 && satisfaz_com_1) {
                    mergeVariaveis(copia_com_0, copia_com_1, variaveis);
                    variaveis[i] = DONT_CARE;
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    arvore_expressao.calculaResultados(variaveis);
    return arvore_expressao.raiz->resultado;
}

void Expressao::mergeVariaveis(int* variaveis_1, int* variaveis_2, int* variaveis_mergeadas) {
    // Faz a mesclagem de dois arrays de variáveis
    for(int i = 0; i < qtd_valores; i++) {
        if(variaveis_1[i] == 0) {
            variaveis_mergeadas[i] = variaveis_2[i];
        } else if(variaveis_2[i] == 0) {
            variaveis_mergeadas[i] = variaveis_1[i];
        } else {
            if(variaveis_1[i] == DONT_CARE || variaveis_2[i] == DONT_CARE) {
                variaveis_mergeadas[i] = DONT_CARE;
            } else {
                variaveis_mergeadas[i] = 1;
            }
        }
    }
}