#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <ctime> // Para a data automática
#include <iomanip>
#include <cstring>
#include <cstdlib> // Para rand() e srand()


using namespace std;

int mainMenu();
int receiptMenu(int num_cliente, float dinheiro_entregue, float troco, float subtotal, float iva, float total, bool gratis = false);
int checkoutMenu();
int adicionarItem(int index);
int gerirProdutosMenu();

inline void clearScreen() { cout << "\x1B[2J\x1B[H"; }

char choice;
int numero_talao = 1000;
int total_compras = 0; // Contador de compras

struct Produto {
    char nome[20];
    float preco_obtencao;
    int stock;
    
    // Calculate selling price automatically (30% profit)
    float preco_venda() const {
        return preco_obtencao * 1.30f;
    }
};

vector<Produto> produtos = {
    {"Bolo", 1.15, 50},
    {"Gomas", 0.23, 100},
    {"Chocapix", 1.54, 30},
	{"Ferrero Roche 6un", 5.24, 1000}
};

struct ItemCarrinho {
    Produto produto;
    int quantidade;
};

vector<ItemCarrinho> carrinho;

int main() {
	// Initialize random seed
	srand(time(0));
	
    while (true) {
        choice = mainMenu();
	
		switch (choice) {
			case 'a':
				carrinho.clear();
				cout << "Carrinho limpo!";
				break;
			case 'b':
				if (!carrinho.empty()) {
					checkoutMenu();
				} else {
					cout << "Carrinho vazio! Adicione produtos primeiro.";
				}
				break;
			case 'z':
				gerirProdutosMenu();
				break;
			default:
				// Check if it's a digit and valid product number
				if (isdigit(choice)) {
					int index = choice - '1';
					if (index >= 0 && index < produtos.size()) {
						adicionarItem(index);
					} else {
						cout << "Opcao invalida";
					}
				} else {
					cout << "Opcao invalida";
				}
				break;
		}
		
		cout << "\nPressione Enter para continuar...";
		cin.ignore();
		cin.get();
    }
};

int adicionarItem(int index) {
	// Show product and ask for quantity
	clearScreen();
	cout << "\n  Produto selecionado: " << produtos[index].nome;
	cout << "\n  Preco unitario: " << fixed << setprecision(2) << produtos[index].preco_venda() << " EUR\n";
	cout << "\n  Stock disponivel: " << produtos[index].stock << "\n";
	cout << "\n  Quantos deseja adicionar? (numero negativo para remover) > ";
	
	int qtd;
	cin >> qtd;
	
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\n  Quantidade invalida!";
		return -1;
	}
	
	if (qtd == 0) {
		cout << "\n  Nenhuma alteracao feita.";
		return 0;
	}
	
	if (qtd > 0) {
		// Check stock
		if (qtd > produtos[index].stock) {
			cout << "\n  Stock insuficiente! Apenas " << produtos[index].stock << " disponiveis.";
			return -1;
		}
		
		// Add to cart
		bool found = false;
		for (int i = 0; i < carrinho.size(); i++) {
			if (strcmp(carrinho[i].produto.nome, produtos[index].nome) == 0) {
				carrinho[i].quantidade += qtd;
				found = true;
				break;
			}
		}
		if (!found) {
			ItemCarrinho item;
			item.produto = produtos[index];
			item.quantidade = qtd;
			carrinho.push_back(item);
		}
		produtos[index].stock -= qtd; // Decrease stock
		cout << "\n  " << qtd << "x " << produtos[index].nome << " adicionado ao carrinho!";
	} else {
		// Remove from cart (qtd is negative)
		int qtd_remover = -qtd;
		bool found = false;
		for (int i = 0; i < carrinho.size(); i++) {
			if (strcmp(carrinho[i].produto.nome, produtos[index].nome) == 0) {
				found = true;
				if (carrinho[i].quantidade <= qtd_remover) {
					cout << "\n  " << produtos[index].nome << " removido completamente do carrinho!";
					carrinho.erase(carrinho.begin() + i);
				} else {
					carrinho[i].quantidade -= qtd_remover;
					cout << "\n  " << qtd_remover << "x " << produtos[index].nome << " removido do carrinho!";
				}
				break;
			}
		}
		if (!found) {
			cout << "\n  Produto nao esta no carrinho!";
		}
	}
	
	return 0;
}

// -------------------------------------- MENU INICIAL ---------------------------------------
int mainMenu() {
	clearScreen();
    cout << "                   - Sweet Land -";
    cout << "\n\n  Produtos:\n";

    for (int i = 0; i < produtos.size(); ++i) {
        printf("   %d) %s, Preco: %.3f EUR (Stock: %d)\n", i + 1, produtos[i].nome, produtos[i].preco_venda(), produtos[i].stock);
    }

    cout << "\n\n  Carrinho:\n";
    if (carrinho.empty()) {
        cout << "   (vazio)\n";
    } else {
        float total = 0;
        for (int i = 0; i < carrinho.size(); i++) {
            float subtotal = carrinho[i].produto.preco_venda() * carrinho[i].quantidade;
            printf("   %s x%d - %.2f EUR\n", 
                   carrinho[i].produto.nome, 
                   carrinho[i].quantidade, 
                   subtotal);
            total += subtotal;
        }
        printf("   Total: %.2f EUR\n", total);
    }

    cout << "\n\n  Outras opcoes:\n";
	cout << "   a) Limpar carrinho\n";
	cout << "   b) Checkout\n";
	cout << "\n   z) Editar produtos disponíveis\n";

	cout << "\n\n Insira uma opção > ";
    cin >> choice;
	
	return choice;
};

// -------------------------------------- CHECKOUT ---------------------------------------
int checkoutMenu() {
	clearScreen();
	
	if (carrinho.empty()) {
		cout << "\nCarrinho vazio!\n";
		return -1;
	}
	
	// Calculate totals
	float subtotal = 0;
	for (int i = 0; i < carrinho.size(); i++) {
		subtotal += carrinho[i].produto.preco_venda() * carrinho[i].quantidade;
	}
	float iva = subtotal * 0.23;
	float total = subtotal + iva;
	
	cout << "\n========== CHECKOUT ==========\n";
	cout << "\nProdutos no carrinho:\n";
	cout << "----------------------------------------\n";
	
	// Show cart items
	for (int i = 0; i < carrinho.size(); i++) {
		float item_total = carrinho[i].produto.preco_venda() * carrinho[i].quantidade;
		printf("%-20s   %2dx    %6.2f EUR\n", 
		       carrinho[i].produto.nome, 
		       carrinho[i].quantidade, 
		       item_total);
	}
	
	cout << "----------------------------------------\n";
	cout << "\nTotal a pagar: " << fixed << setprecision(2) << total << " EUR\n";
	
	// Get customer number
	int num_cliente;
	cout << "\nNumero do cliente: ";
	cin >> num_cliente;
	
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nNumero invalido!\n";
		return -1;
	}
	
	// Get payment
	float dinheiro_entregue;
	cout << "Dinheiro entregue: ";
	cin >> dinheiro_entregue;
	
	if (cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nValor invalido!\n";
		return -1;
	}
	
	if (dinheiro_entregue < total) {
		cout << "\nDinheiro insuficiente! Faltam " << fixed << setprecision(2) 
		     << (total - dinheiro_entregue) << " EUR\n";
		return -1;
	}
	
	float troco = dinheiro_entregue - total;
	
	// Check for free receipt (60% chance on even receipt numbers)
	bool gratis = false;
	if (numero_talao % 2 == 0) {
		// Generate random number between 0-99
		int chance = rand() % 100;
		if (chance < 60) { // 60% chance
			gratis = true;
			troco = dinheiro_entregue; // Return all money
		}
	}
	
	// Show receipt
	receiptMenu(num_cliente, dinheiro_entregue, troco, subtotal, iva, total, gratis);
	
	// Increment purchase counter
	total_compras++;
	
	// Rickroll on 3rd purchase
	if (total_compras == 2) {
		system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ &");
	}
	
	// Clear cart and increment receipt number
	carrinho.clear();
	numero_talao++;
	
	return 0;
};

// -------------------------------------- RECIBO ---------------------------------------
int receiptMenu(int num_cliente, float dinheiro_entregue, float troco, float subtotal, float iva, float total, bool gratis) {
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
	cout << "Talao N: " << numero_talao << "\n";
	cout << "Cliente N: " << num_cliente;
	
	// Easter egg for special customer
	if (num_cliente == 890) {
		cout << " - JORGEEEEE";
	}
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
	
	// Show cart items
	for (int i = 0; i < carrinho.size(); i++) {
		float item_total = carrinho[i].produto.preco_venda() * carrinho[i].quantidade;
		printf("%-20s   %2dx    %6.2f\n", 
		       carrinho[i].produto.nome, 
		       carrinho[i].quantidade, 
		       item_total);
	}
	
	cout << "----------------------------------------\n";
	printf("Subtotal (sem IVA):            %6.2f\n", subtotal);
	printf("IVA (23%%):                     %6.2f\n", iva);
	cout << "----------------------------------------\n";
	
	if (gratis) {
		cout << "\n";
		cout << "*** PARABENS! TALAO GRATIS! ***\n";
		cout << "   Voce teve sorte hoje!\n";
		cout << "\n";
		printf("TOTAL:                         %6.2f EUR\n", 0.0f);
		cout << "========================================\n";
		printf("Dinheiro entregue:             %6.2f EUR\n", dinheiro_entregue);
		printf("Troco:                         %6.2f EUR\n", dinheiro_entregue);
	} else {
		printf("TOTAL:                         %6.2f EUR\n", total);
		cout << "========================================\n";
		printf("Dinheiro entregue:             %6.2f EUR\n", dinheiro_entregue);
		printf("Troco:                         %6.2f EUR\n", troco);
	}
	
	cout << "========================================\n";
	cout << "\n";
	cout << "   Obrigado pela sua compra!\n";
	cout << "   Volte sempre!\n";
	cout << "\n";
	cout << "========================================\n";
	cout << "\nPressione Enter para continuar...";
	cin.ignore();
	cin.get();
	
	return 0;
};

// -------------------------------------- GERIR PRODUTOS ---------------------------------------
int gerirProdutosMenu() {
	while (true) {
		clearScreen();
		cout << "\n========== GERIR PRODUTOS ==========\n";
		cout << "\nProdutos disponiveis:\n";
		cout << "----------------------------------------\n";
		printf("%-3s %-20s %8s %8s %8s\n", "ID", "Nome", "P.Obt.", "P.Venda", "Stock");
		cout << "----------------------------------------\n";
		
		for (int i = 0; i < produtos.size(); i++) {
			printf("%2d) %-20s %7.2f€ %7.2f€ %6d\n", 
			       i + 1, 
			       produtos[i].nome, 
			       produtos[i].preco_obtencao,
			       produtos[i].preco_venda(),
			       produtos[i].stock);
		}
		
		cout << "\n----------------------------------------\n";
		cout << "Nota: Preco de venda = Preco obtencao + 30% lucro\n";
		cout << "\n  Opcoes:\n";
		cout << "   a) Adicionar novo produto\n";
		cout << "   d) Apagar produto\n";
		cout << "   e) Editar stock\n";
		cout << "   v) Voltar ao menu principal\n";
		
		char opcao;
		cout << "\n Escolha uma opcao > ";
		cin >> opcao;
		
		if (opcao == 'v') {
			break;
		} else if (opcao == 'a') {
			// Add new product
			clearScreen();
			cout << "\n===== ADICIONAR PRODUTO =====\n";
			
			Produto novo;
			cout << "\nNome do produto: ";
			cin.ignore();
			cin.getline(novo.nome, 20);
			
			cout << "Preco de obtencao (EUR): ";
			cin >> novo.preco_obtencao;
			
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nPreco invalido!\n";
				cout << "\nPressione Enter...";
				cin.get();
				continue;
			}
			
			cout << "Quantidade em stock: ";
			cin >> novo.stock;
			
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nQuantidade invalida!\n";
				cout << "\nPressione Enter...";
				cin.get();
				continue;
			}
			
			produtos.push_back(novo);
			cout << "\nProduto adicionado com sucesso!";
			cout << "\nPreco de venda calculado: " << fixed << setprecision(2) << novo.preco_venda() << " EUR";
			cout << "\n\nPressione Enter...";
			cin.ignore();
			cin.get();
			
		} else if (opcao == 'd') {
			// Delete product
			cout << "\nNumero do produto a apagar (0 para cancelar): ";
			int num;
			cin >> num;
			
			if (cin.fail() || num < 0 || num > produtos.size()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nOpcao invalida!\n";
				cout << "\nPressione Enter...";
				cin.get();
				continue;
			}
			
			if (num == 0) continue;
			
			cout << "\nTem certeza que deseja apagar '" << produtos[num-1].nome << "'? (s/n): ";
			char confirma;
			cin >> confirma;
			
			if (confirma == 's' || confirma == 'S') {
				produtos.erase(produtos.begin() + (num - 1));
				cout << "\nProduto apagado!";
			} else {
				cout << "\nOperacao cancelada.";
			}
			
			cout << "\n\nPressione Enter...";
			cin.ignore();
			cin.get();
			
		} else if (opcao == 'e') {
			// Edit stock
			cout << "\nNumero do produto (0 para cancelar): ";
			int num;
			cin >> num;
			
			if (cin.fail() || num < 0 || num > produtos.size()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nOpcao invalida!\n";
				cout << "\nPressione Enter...";
				cin.get();
				continue;
			}
			
			if (num == 0) continue;
			
			cout << "\nProduto: " << produtos[num-1].nome;
			cout << "\nStock atual: " << produtos[num-1].stock;
			cout << "\nNovo stock: ";
			int novo_stock;
			cin >> novo_stock;
			
			if (cin.fail() || novo_stock < 0) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "\nQuantidade invalida!\n";
				cout << "\nPressione Enter...";
				cin.get();
				continue;
			}
			
			produtos[num-1].stock = novo_stock;
			cout << "\nStock atualizado!";
			cout << "\n\nPressione Enter...";
			cin.ignore();
			cin.get();
		}
	}
	
	return 0;
}