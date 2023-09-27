#ifndef PILHA_HPP
#define PILHA_HPP

#include <string>
#include <iostream>
#include <stack>
#include <cmath>
#include <cstring>

class Pilha {
	public:
		Pilha();
		int getTamanho();
		bool vazia();
		void empilha(std::string item);
		std::string desempilha();
		void limpa();
		std::string getTopo();
	private:
		int topo;
		static const int MAXTAM = 1000;
		std::string itens[MAXTAM];
		int tamanho;
};

#endif // PILHA_HPP