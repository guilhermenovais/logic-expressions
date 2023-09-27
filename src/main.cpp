#include "../include/expressao.hpp"
#include <exception>
#include <iomanip>
#include <istream>
#include <sstream>
#include <string>

using namespace std;

string trim(std::string& s);

int main() {
    string line, comando, tipo_exp, exp;
    Expressao expressao;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> comando;
        if(comando == "LER") {
            ss >> tipo_exp;
            getline(ss >> ws, exp);
            exp = trim(exp);
            if(tipo_exp == "POSFIXA") {
                if(expressao.lePosfixa(exp)) {
                    cout << "EXPRESSAO OK: " << expressao.getExp() << "\n";
                } else {
                    cout << "ERRO: EXP NAO VALIDA\n";
                }
            } else if(tipo_exp == "INFIXA") {
                if(expressao.leInfixa(exp)) {
                    cout << "EXPRESSAO OK: " << expressao.getExp() << "\n";
                } else {
                    cout << "ERRO: EXP NAO VALIDA\n";
                }
            }
        } else if(comando == "INFIXA") {
            if(expressao.posParaInf()) {
                cout << "INFIXA: " << expressao.getExp() << "\n";
            } else {
                cout << "ERRO: EXP NAO EXISTE" << "\n";
            }
        } else if(comando == "POSFIXA") {
            if(expressao.infParaPos()) {
                cout << "POSFIXA: " << expressao.getExp() << "\n";
            } else {
                cout << "ERRO: EXP NAO EXISTE" << "\n";
            }
        } else if(comando == "RESOLVE") {
            try {
                double resultado = expressao.resolve();
                cout.precision(6);
                cout << "VAL: " << fixed << resultado << '\n';
            } catch (const std::exception& e) {
                cout << e.what() << "\n";
            }
        }
    }

    return 0;
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