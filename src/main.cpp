#include "../include/expressao.hpp"
#include "../include/excecoes.hpp"
#include <string>
#include <iostream>

bool caracteresExpValidos(std::string expressao);
bool valoresValidos(std::string valores);

int main(int argc, char *argv[]) {
    try {
        // Verifica se o programa recebeu os 3 argumentos
        if(argc != 4) throw ArgumentosInvalidos();

        // Verifica se o tipo recebido é válido
        std::string tipo = argv[1];
        if(tipo != "-a" && tipo != "-s") throw TipoInvalido();

        // Verifica se a expressão recebida é válida
        std::string str_expressao = argv[2];
        if(!caracteresExpValidos(str_expressao)) throw ExpressaoInvalida();

        // Verifica se os valores recebidos são válidos
        std::string valores = argv[3];
        if(!valoresValidos(valores)) throw ValoresInvalidos();

        Expressao expressao = Expressao(str_expressao, valores, tipo);
        expressao.calculaExpressao();
    } catch(ArgumentosInvalidos e) {
        std::cout << "\n" << e.what() << "\n\n";
    } catch(TipoInvalido e) {
        std::cout << "\n" << e.what() << "\n\n";
    } catch(ExpressaoInvalida e) {
        std::cout << "\n" << e.what() << "\n\n";
    } catch(ValoresInvalidos e) {
        std::cout << "\n" << e.what() << "\n\n";
    }
}

// Função para verificar se os caracteres da expressão recebida são válidos
bool caracteresExpValidos(std::string expressao) {
    for(int i = 0; i < expressao.length(); i++) {
        switch(expressao[i]) {
            case '(':
            case ')':
            case ' ':
            case '|':
            case '&':
            case '~':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                break;
            default:
                return false;
        }
    }
    return true;
}

bool valoresValidos(std::string valores) {
    for(int i = 0; i < valores.length(); i++) {
        switch(valores[i]) {
            case '0':
            case '1':
            case 'a':
            case 'e':
                break;
            default:
                return false;
        }
    }
    return true;
}