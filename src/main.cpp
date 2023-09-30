#include "../include/expressao.hpp"
#include <exception>
#include <iomanip>
#include <istream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    std::string tipo = argv[1];
    std::string str_expressao = argv[2];
    std::string valores = argv[3];
    Expressao expressao = Expressao(str_expressao, valores, tipo);
    expressao.calculaExpressao();
}