#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

class ArgumentosInvalidos : public std::exception {
    public:
        const char* what () {
            const char* mensagem = "Argumentos inválidos. O programa deve receber exatamente 3 argumentos (tipo, expressão e valores).";
            return mensagem;
        }
};

class TipoInvalido : public std::exception {
    public:
        const char* what () {
            const char* mensagem = "Argumento 'tipo' inválido. O tipo deve ser '-a' (avaliação de expressões) ou '-s' (satisfabilidade).";
            return mensagem;
        }
};

class ExpressaoInvalida : public std::exception {
    public:
        const char* what () {
            const char* mensagem = "Argumento 'expressão' inválido. A expressão fornecida possui caracteres inválidos.";
            return mensagem;
        }
};

class ValoresInvalidos : public std::exception {
    public:
        const char* what () {
            const char* mensagem = "Argumento 'valores' inválido. O argumento 'valores' deve ser composto apenas por 0's, 1's, a's e e's.";
            return mensagem;
        }
};

#endif //EXCEPTIONS_HPP