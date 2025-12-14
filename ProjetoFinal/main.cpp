#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <ctime> // Para a data automática
#include <iomanip>

using namespace std;

int mainMenu();
int receiptMenu();

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
	receiptMenu();

    while (true) {
        mainMenu();
    }
};

// -------------------------------------- MENU INICIAL ---------------------------------------


int mainMenu() {
	clearScreen();
    cout << "                   - Sweet Land -";
    cout << "\n\n  Produtos:\n";

    for (int i = 0; i < 2; ++i) {
        printf("   %d) %s, Preco: %.2f\n", i + 1, produtos[i].nome, produtos[i].preco);
    }

    cout << "\n\n  Carrinho:\n";


    cout << "\n\n  Outras opcoes:\n";
	cout << "   a) Limpar carrinho\n";
	cout << "   b) Checkout\n";
	cout << "\n   z) Adicionar aos produtos disponíveis\n";

	cout << "\n\n Insira uma opção > ";
    cin >> choice;
	return choice;
};

// -------------------------------------- CHECKOUT ---------------------------------------


int checkoutMenu() {
	return 0;
};

// -------------------------------------- RECIBO ---------------------------------------

int receiptMenu() {
	clearScreen();
	
	// Get current date/time
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	cout << "\n";
	cout << "========================================\n";
	cout << "            SWEET LAND                  \n";
	cout << "        Rua dos Doces, 123              \n";
	cout << "        Tel: 123-456-789                \n";
	cout << "========================================\n";
	cout << "\n";
	cout << "Data: " << setfill('0') << setw(2) << ltm->tm_mday << "/"
	     << setw(2) << 1 + ltm->tm_mon << "/"
	     << 1900 + ltm->tm_year << "\n";
	cout << "Hora: " << setw(2) << ltm->tm_hour << ":"
	     << setw(2) << ltm->tm_min << ":"
	     << setw(2) << ltm->tm_sec << "\n";
	cout << "\n";
	cout << "----------------------------------------\n";
	cout << "ITEM                   QTD    PRECO EUR\n";
	cout << "----------------------------------------\n";
	
	// Sample items
	cout << "Bolo                    2x     3.00\n";
	cout << "Gomas                   5x     1.50\n";
	cout << "Chocolate               1x     2.50\n";
	
	cout << "----------------------------------------\n";
	cout << "Subtotal:                      7.00\n";
	cout << "IVA (23%):                     1.61\n";
	cout << "----------------------------------------\n";
	cout << "TOTAL:                         8.61 EUR\n";
	cout << "========================================\n";
	cout << "\n";
	cout << "   Obrigado pela sua compra!\n";
	cout << "   Volte sempre!\n";
	cout << "\n";
	cout << "========================================\n";
	cout << "\nPressione Enter para continuar...";
	cin.get();
	
	return 0;
};