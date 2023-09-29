#include "../include/expressao.hpp"
#include <exception>
#include <iomanip>
#include <istream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

string trim(std::string& s);

int main(int argc, char *argv[]) {
    std::string tipo = argv[1];
    std::string str_expressao = argv[2];
    std::string valores = argv[3];
    Expressao expressao = Expressao(str_expressao, valores, tipo);
}

string trim(std::string& str) {
    const string whitespace = " \n";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}