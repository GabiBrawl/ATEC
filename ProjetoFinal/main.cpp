#include <iostream>   // cout, cin
#include <iomanip>    // setprecision, setw, setfill
#include <vector>     // vector (arrays dinamicos)
#include <cstring>    // strcmp (comparar strings)
#include <ctime>      // time, localtime (data/hora)
#include <cstdlib>    // rand, srand, system

using namespace std;

// ============================== DECLARAÇÕES ==============================
int mainMenu();
void receiptMenu(int num_cliente, float dinheiro_entregue, float troco, 
                 float subtotal, float iva, float total, bool gratis = false);
void checkoutMenu();
int adicionarItem(int index);
void gerirProdutosMenu();

// ============================== GLOBAIS ==============================
inline void clearScreen() { cout << "\x1B[2J\x1B[H"; }

char choice;
int numero_talao = 1000;
int total_compras = 0;

// ============================== STRUCTS ==============================
struct Produto {
    char nome[20];
    float preco_obtencao;
    int stock;
    
    float preco_venda() const { return preco_obtencao * 1.30f; }
};

struct ItemCarrinho {
    Produto produto;
    int quantidade;
};

// ============================== DADOS ==============================
vector<Produto> produtos = {
    {"Bolo", 1.15, 50},
    {"Gomas", 0.23, 100},
    {"Chocapix", 1.54, 30},
    {"Ferrero Roche 6un", 5.24, 1000}
};

vector<ItemCarrinho> carrinho;

// ============================== MAIN ==============================

int main() {
    srand(time(0));
    
    while (true) {
        choice = mainMenu();
        
        switch (choice) {
            case 'a':
                carrinho.clear();
                cout << "Carrinho limpo!";
                break;
            case 'b':
                if (!carrinho.empty()) checkoutMenu();
                else cout << "Carrinho vazio! Adicione produtos primeiro.";
                break;
            case 'z':
                gerirProdutosMenu();
                break;
            default:
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
        
        cout << "\n\nPressione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
}

// ============================== ADICIONAR ITEM ==============================

int adicionarItem(int index) {
    clearScreen();
    cout << "\n  Produto: " << produtos[index].nome;
    cout << "\n  Preco: " << fixed << setprecision(2) << produtos[index].preco_venda() << " EUR";
    cout << "\n  Stock: " << produtos[index].stock << "\n";
    cout << "\n  Quantidade (negativo para remover) > ";
    
    int qtd;
    cin >> qtd;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n  Quantidade invalida!";
        return -1;
    }
    
    if (qtd == 0) {
        cout << "\n  Nenhuma alteracao.";
        return 0;
    }
    
    if (qtd > 0) {
        if (qtd > produtos[index].stock) {
            cout << "\n  Stock insuficiente! (Disponivel: " << produtos[index].stock << ")";
            return -1;
        }
        
        bool found = false;
        for (auto &item : carrinho) {
            if (strcmp(item.produto.nome, produtos[index].nome) == 0) {
                item.quantidade += qtd;
                found = true;
                break;
            }
        }
        
        if (!found) {
            carrinho.push_back({produtos[index], qtd});
        }
        
        produtos[index].stock -= qtd;
        cout << "\n  " << qtd << "x " << produtos[index].nome << " adicionado!";
    } else {
        int qtd_remover = -qtd;
        bool found = false;
        
        for (int i = 0; i < carrinho.size(); i++) {
            if (strcmp(carrinho[i].produto.nome, produtos[index].nome) == 0) {
                found = true;
                if (carrinho[i].quantidade <= qtd_remover) {
                    cout << "\n  " << produtos[index].nome << " removido completamente!";
                    carrinho.erase(carrinho.begin() + i);
                } else {
                    carrinho[i].quantidade -= qtd_remover;
                    cout << "\n  " << qtd_remover << "x removido!";
                }
                break;
            }
        }
        
        if (!found) cout << "\n  Produto nao esta no carrinho!";
    }
    
    return 0;
}

// ============================== MENU INICIAL ==============================
int mainMenu() {
    clearScreen();
    cout << "\n                - Sweet Land -\n";
    cout << "\n  Produtos:\n";

    for (size_t i = 0; i < produtos.size(); ++i) {
        printf("   %zu) %-20s %.2f EUR (Stock: %d)\n", 
               i + 1, produtos[i].nome, produtos[i].preco_venda(), produtos[i].stock);
    }

    cout << "\n  Carrinho:\n";
    if (carrinho.empty()) {
        cout << "   (vazio)\n";
    } else {
        float total = 0;
        for (const auto &item : carrinho) {
            float subtotal = item.produto.preco_venda() * item.quantidade;
            printf("   %-20s x%-2d  %.2f EUR\n", item.produto.nome, item.quantidade, subtotal);
            total += subtotal;
        }
        printf("\n   Total: %.2f EUR\n", total);
    }

    cout << "\n  Opcoes:\n";
    cout << "   a) Limpar carrinho\n";
    cout << "   b) Checkout\n";
    cout << "   z) Gerir produtos\n";
    cout << "\n  > ";
    cin >> choice;
    
    return choice;
}

// ============================== CHECKOUT ==============================
void checkoutMenu() {
    clearScreen();
    
    if (carrinho.empty()) {
        cout << "\n  Carrinho vazio!\n\n  ";
        cin.ignore();
        cin.get();
        return;
    }

    float subtotal = 0;
    for (const auto &item : carrinho) {
        subtotal += item.produto.preco_venda() * item.quantidade;
    }
    
    float iva = subtotal * 0.23f;
    float total = subtotal + iva;

    cout << "\n  Subtotal: " << subtotal << " EUR\n";
    cout << "  IVA (23%): " << iva << " EUR\n";
    printf("  Total: %.2f EUR\n\n", total);

    int numeroCliente;
    cout << "  Numero de cliente: ";
    cin >> numeroCliente;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n  Numero invalido!\n\n  ";
        cin.get();
        return;
    }

    float dinheiroEntregue;
    cout << "  Dinheiro entregue: ";
    cin >> dinheiroEntregue;

    if (cin.fail() || dinheiroEntregue < total) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n  " << (dinheiroEntregue < total ? "Dinheiro insuficiente!" : "Valor invalido!") << "\n\n  ";
        cin.get();
        return;
    }

    // Lottery: 60% chance on even receipts
    bool gratis = false;
    if (numero_talao % 2 == 0) {
        int chance = rand() % 100;
        gratis = (chance < 60);
    }

    float troco = gratis ? dinheiroEntregue : (dinheiroEntregue - total);
    
    receiptMenu(numeroCliente, dinheiroEntregue, troco, subtotal, iva, total, gratis);

    carrinho.clear();
    numero_talao++;
    total_compras++;

    if (total_compras == 2) {
        system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ &");
    }
}

// ============================== RECEIPT ==============================
void receiptMenu(int num_cliente, float dinheiro_entregue, float troco, float subtotal, float iva, float total, bool gratis) {
    clearScreen();
    
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    cout << "\n========================================\n";
    cout << "            SWEET LAND                  \n";
    cout << "        Rua dos Doces, 123              \n";
    cout << "        Tel: 123-456-789                \n";
    cout << "========================================\n\n";
    
    cout << "Talao N: " << numero_talao << "\n";
    cout << "Cliente N: " << num_cliente;
    if (num_cliente == 890) cout << " - JORGEEEEE";
    cout << "\n";
    
    cout << "Data: " << setfill('0') << setw(2) << ltm->tm_mday << "/"
         << setw(2) << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << "\n";
    cout << "Hora: " << setw(2) << ltm->tm_hour << ":"
         << setw(2) << ltm->tm_min << ":" << setw(2) << ltm->tm_sec << "\n\n";
    
    cout << "----------------------------------------\n";
    cout << "ITEM                   QTD    PRECO EUR\n";
    cout << "----------------------------------------\n";
    
    for (const auto &item : carrinho) {
        float item_total = item.produto.preco_venda() * item.quantidade;
        printf("%-20s   %2dx    %6.2f\n", item.produto.nome, item.quantidade, item_total);
    }
    
    cout << "----------------------------------------\n";
    printf("Subtotal (sem IVA):            %6.2f\n", subtotal);
    printf("IVA (23%%):                     %6.2f\n", iva);
    cout << "----------------------------------------\n";
    
    if (gratis) {
        cout << "\n*** PARABENS! TALAO GRATIS! ***\n";
        cout << "   Voce teve sorte hoje!\n\n";
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
    
    cout << "========================================\n\n";
    cout << "   Obrigado pela sua compra!\n";
    cout << "   Volte sempre!\n\n";
    cout << "========================================\n\n";
    
    cin.ignore();
    cin.get();
}

// ============================== GERIR PRODUTOS ==============================
void gerirProdutosMenu() {
    while (true) {
        clearScreen();
        cout << "\n  Produtos:\n";
        cout << "  ----------------------------------------\n";
        printf("  %-3s %-20s %8s %8s %8s\n", "ID", "Nome", "P.Obt.", "P.Venda", "Stock");
        cout << "  ----------------------------------------\n";
        
        for (size_t i = 0; i < produtos.size(); i++) {
            printf("  %2zu) %-20s %7.2f€ %7.2f€ %6d\n", 
                   i + 1, produtos[i].nome, produtos[i].preco_obtencao,
                   produtos[i].preco_venda(), produtos[i].stock);
        }
        
        cout << "\n  Nota: Preco venda = Preco obtencao + 30%\n";
        cout << "\n  Opcoes:\n";
        cout << "   a) Adicionar produto\n";
        cout << "   d) Apagar produto\n";
        cout << "   e) Editar stock\n";
        cout << "   v) Voltar\n";
        cout << "\n  > ";
        
        char opcao;
        cin >> opcao;
        
        if (opcao == 'v') break;
        
        if (opcao == 'a') {
            clearScreen();
            Produto novo;
            
            cout << "\n  Nome: ";
            cin.ignore();
            cin.getline(novo.nome, 20);
            
            cout << "  Preco obtencao (EUR): ";
            cin >> novo.preco_obtencao;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n  Preco invalido!\n\n  ";
                cin.get();
                continue;
            }
            
            cout << "  Stock: ";
            cin >> novo.stock;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n  Quantidade invalida!\n\n  ";
                cin.get();
                continue;
            }
            
            produtos.push_back(novo);
            printf("\n  Adicionado! Preco venda: %.2f EUR\n\n  ", novo.preco_venda());
            cin.ignore();
            cin.get();
            
        } else if (opcao == 'd') {
            cout << "\n  Produto a apagar (0 = cancelar): ";
            int num;
            cin >> num;
            
            if (cin.fail() || num < 0 || num > produtos.size()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n  Invalido!\n\n  ";
                cin.get();
                continue;
            }
            
            if (num == 0) continue;
            
            cout << "\n  Apagar '" << produtos[num-1].nome << "'? (s/n): ";
            char confirma;
            cin >> confirma;
            
            if (confirma == 's' || confirma == 'S') {
                produtos.erase(produtos.begin() + (num - 1));
                cout << "\n  Apagado!\n\n  ";
            } else {
                cout << "\n  Cancelado.\n\n  ";
            }
            
            cin.ignore();
            cin.get();
            
        } else if (opcao == 'e') {
            cout << "\n  Produto (0 = cancelar): ";
            int num;
            cin >> num;
            
            if (cin.fail() || num < 0 || num > produtos.size()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n  Invalido!\n\n  ";
                cin.get();
                continue;
            }
            
            if (num == 0) continue;
            
            cout << "\n  Produto: " << produtos[num-1].nome;
            cout << "\n  Stock atual: " << produtos[num-1].stock;
            cout << "\n  Novo stock: ";
            int novo_stock;
            cin >> novo_stock;
            
            if (cin.fail() || novo_stock < 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n  Invalido!\n\n  ";
                cin.get();
                continue;
            }
            
            produtos[num-1].stock = novo_stock;
            cout << "\n  Atualizado!\n\n  ";
            cin.ignore();
            cin.get();
        }
    }
}