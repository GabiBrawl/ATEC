/*

                    - Sweet Land -
Produtos:
	1) Gomas .......... 3.50
	2) Doces .......... 0.87
	3) Mais gomas ..... 0.15
	4) Um bolo ........ 11.6
	5) Pato

Carrinho:
	Gomas * 15
	Doces * 6

	Total: 12.3

Outras Opcoes:
	a) limpar carrinho
	b) checkout

	z) Adicionar produtos disponíveis

Insira uma opção >  

*/

#include <vector>
#include <string>
#include <iostream>
#include <ctime> // Para a data automática

int choice;

void main() {
    while (true) {
        mainMenu();
    }
};

void mainMenu() {
    cout << "                   - Sweet Land -\n\n";
    cout << " Produtos:\n";

    cin >> choice;
};

void checkoutMenu() {};

void receiptMenu() {};