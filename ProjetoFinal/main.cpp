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

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <ctime> // Para a data automática

using namespace std;

void checkoutMenu() {};
void receiptMenu() {};
int mainMenu();
inline void clearScreen() { cout << "\x1B[2J\x1B[H"; }

int choice;

struct Produto {
    char nome[20];
    float preco;
};

struct Produto produtos[2] = {
    {"Bolo", 1.5},
    {"Gomas", 0.3}
};

int main() {
    while (true) {
        mainMenu();
    }
};

int mainMenu() {
	clearScreen();
    cout << "                   - Sweet Land -\n\n";
    cout << " Produtos:\n";

	// Tens de substituir aqui esta linha pelo tal loop para escrever todos os produtos no menu
	printf("Item: %s, Preco: %.2f\n", produtos[0].nome, produtos[0].preco);

    cin >> choice;

	return 0;
};