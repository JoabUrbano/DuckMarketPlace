#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "DuckMarketPlace.h"

// Cores ANSI para melhor visualização
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Função para limpar a tela
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para verificar se um usuário existe
bool user_exists(DuckMarketPlace__IDUSUARIO userId) {
    bool can_remove;
    DuckMarketPlace__preRemoveUser(userId, &can_remove);
    return can_remove;
}

// Função para verificar se um produto existe  
bool product_exists(DuckMarketPlace__IDPRODUTO productId) {
    bool can_remove;
    DuckMarketPlace__preRemoveProduct(productId, &can_remove);
    return can_remove;
}

// Função para pausar e aguardar entrada do usuário
void pause_screen() {
    printf("\n" YELLOW "Pressione ENTER para continuar..." RESET);
    while (getchar() != '\n');
    getchar();
}

// Função para exibir cabeçalho
void print_header() {
    clear_screen();
    printf(CYAN BOLD "╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    DuckMarketPlace - TUI                     ║\n");
    printf("║                   Sistema de Marketplace                     ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n" RESET);
    printf("\n");
}

// Função para exibir informações do usuário
void print_user_info(DuckMarketPlace__IDUSUARIO userId) {
    // Verificar se o usuário realmente existe
    if (!user_exists(userId)) {
        printf(RED "┌─ Usuário ID: %d ─────────────────────────────┐\n", userId);
        printf("│ USUÁRIO NÃO EXISTE                          │\n");
        printf("└─────────────────────────────────────────────────┘" RESET "\n");
        return;
    }
    
    DuckMarketPlace__NOMEUSUARIO userName;
    int32_t userCredit;
    int32_t cartValue;
    int32_t userDebt;
    
    DuckMarketPlace__showUserName(userId, &userName);
    DuckMarketPlace__showUserCredit(userId, &userCredit);
    DuckMarketPlace__showUserCartValue(userId, &cartValue);
    DuckMarketPlace__showUserDebt(userId, &userDebt);
    
    printf(GREEN "┌─ Usuário ID: %d ─────────────────────────────┐\n", userId);
    printf("│ Nome: %-10d                              │\n", userName);
    printf("│ Crédito: %-10d                          │\n", userCredit);
    printf("│ Valor do Carrinho: %-10d                │\n", cartValue);
    if (userDebt > 0) {
        printf("│ " RED "Dívida: %-10d" GREEN "                         │\n", userDebt);
    } else {
        printf("│ Dívida: %-10d                           │\n", userDebt);
    }
    printf("└─────────────────────────────────────────────────┘" RESET "\n");
}

// Função para exibir informações do produto
void print_product_info(DuckMarketPlace__IDPRODUTO productId) {
    // Verificar se o produto realmente existe
    if (!product_exists(productId)) {
        printf(RED "┌─ Produto ID: %d ─────────────────────────────┐\n", productId);
        printf("│ PRODUTO NÃO EXISTE                          │\n");
        printf("└─────────────────────────────────────────────────┘" RESET "\n");
        return;
    }
    
    DuckMarketPlace__NOMEPRODUTO productName;
    int32_t productStock;
    int32_t productPrice;
    
    DuckMarketPlace__showProductName(productId, &productName);
    DuckMarketPlace__showProductStock(productId, &productStock);
    DuckMarketPlace__showProductPrice(productId, &productPrice);
    
    printf(BLUE "┌─ Produto ID: %d ─────────────────────────────┐\n", productId);
    printf("│ Nome: %-10d                              │\n", productName);
    printf("│ Estoque: %-10d                          │\n", productStock);
    printf("│ Preço: %-10d                            │\n", productPrice);
    printf("└─────────────────────────────────────────────────┘" RESET "\n");
}

// Função para obter entrada do usuário
int get_int_input(const char* prompt) {
    int value;
    printf(YELLOW "%s" RESET, prompt);
    while (scanf("%d", &value) != 1) {
        printf(RED "Entrada inválida! Digite um número: " RESET);
        while (getchar() != '\n'); // Limpar buffer
    }
    while (getchar() != '\n'); // Limpar buffer
    return value;
}

// Função para mostrar mensagem de sucesso
void show_success(const char* message) {
    printf(GREEN BOLD "✓ %s" RESET "\n", message);
}

// Função para mostrar mensagem de erro
void show_error(const char* message) {
    printf(RED BOLD "✗ %s" RESET "\n", message);
}

// ======================== OPERAÇÕES DE USUÁRIO ========================

void add_user_operation() {
    print_header();
    printf(BOLD "═══ ADICIONAR USUÁRIO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    int user_name = get_int_input("Digite o nome do usuário (número): ");
    int credit = get_int_input("Digite o crédito inicial: ");
    
    bool can_add;
    DuckMarketPlace__preAddUser(user_id, user_name, credit, &can_add);
    
    if (can_add) {
        DuckMarketPlace__addUser(user_id, user_name, credit);
        show_success("Usuário adicionado com sucesso!");
        printf("\n");
        print_user_info(user_id);
    } else {
        show_error("Não foi possível adicionar o usuário!");
        printf(YELLOW "Verifique se o ID não está em uso e os valores são válidos.\n" RESET);
    }
    
    pause_screen();
}

void list_users_operation() {
    print_header();
    printf(BOLD "═══ LISTA DE USUÁRIOS ═══\n" RESET);
    
    bool found_users = false;
    
    for (int i = 1; i <= 10; i++) {
        if (user_exists(i)) {
            print_user_info(i);
            printf("\n");
            found_users = true;
        }
    }
    
    if (!found_users) {
        printf(YELLOW "Nenhum usuário encontrado.\n" RESET);
    }
    
    pause_screen();
}

void alter_user_name_operation() {
    print_header();
    printf(BOLD "═══ ALTERAR NOME DE USUÁRIO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    int new_name = get_int_input("Digite o novo nome (número): ");
    
    bool can_alter;
    DuckMarketPlace__preAltNameUser(user_id, new_name, &can_alter);
    
    if (can_alter) {
        DuckMarketPlace__altNameUser(user_id, new_name);
        show_success("Nome alterado com sucesso!");
        printf("\n");
        print_user_info(user_id);
    } else {
        show_error("Não foi possível alterar o nome!");
    }
    
    pause_screen();
}

void add_credit_operation() {
    print_header();
    printf(BOLD "═══ ADICIONAR CRÉDITO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    
    printf("\nEstado atual:\n");
    print_user_info(user_id);
    
    int credit = get_int_input("\nDigite o valor do crédito a adicionar: ");
    
    bool can_add;
    DuckMarketPlace__preAddCredit(user_id, credit, &can_add);
    
    if (can_add) {
        DuckMarketPlace__addCredit(user_id, credit);
        show_success("Crédito adicionado com sucesso!");
        printf("\nEstado após adicionar crédito:\n");
        print_user_info(user_id);
    } else {
        show_error("Não foi possível adicionar crédito!");
    }
    
    pause_screen();
}

void withdraw_credit_operation() {
    print_header();
    printf(BOLD "═══ RETIRAR CRÉDITO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    
    printf("\nEstado atual:\n");
    print_user_info(user_id);
    
    int credit = get_int_input("\nDigite o valor do crédito a retirar: ");
    
    bool can_withdraw;
    DuckMarketPlace__preWithdrawCredit(user_id, credit, &can_withdraw);
    
    if (can_withdraw) {
        DuckMarketPlace__withdrawCredit(user_id, credit);
        show_success("Crédito retirado com sucesso!");
        printf("\nEstado após retirar crédito:\n");
        print_user_info(user_id);
    } else {
        show_error("Não foi possível retirar crédito!");
    }
    
    pause_screen();
}

void remove_user_operation() {
    print_header();
    printf(BOLD "═══ REMOVER USUÁRIO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário a remover: ");
    
    printf("\nUsuário atual:\n");
    print_user_info(user_id);
    
    printf(RED "\nATENÇÃO: Esta operação não pode ser desfeita!\n" RESET);
    printf("Digite 1 para confirmar ou 0 para cancelar: ");
    int confirm;
    scanf("%d", &confirm);
    while (getchar() != '\n');
    
    if (confirm != 1) {
        printf(YELLOW "Operação cancelada.\n" RESET);
        pause_screen();
        return;
    }
    
    bool can_remove;
    DuckMarketPlace__preRemoveUser(user_id, &can_remove);
    
    if (can_remove) {
        DuckMarketPlace__removeUser(user_id);
        show_success("Usuário removido com sucesso!");
    } else {
        show_error("Não foi possível remover o usuário!");
    }
    
    pause_screen();
}

void pay_debt_operation() {
    print_header();
    printf(BOLD "═══ PAGAR DÍVIDA ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    
    printf("\nEstado atual:\n");
    print_user_info(user_id);
    
    // Mostrar dívida atual
    int32_t user_debt;
    DuckMarketPlace__showUserDebt(user_id, &user_debt);
    printf("\n" YELLOW "Dívida atual: %d\n" RESET, user_debt);
    
    if (user_debt <= 0) {
        printf(GREEN "✓ Usuário não possui dívidas!\n" RESET);
        pause_screen();
        return;
    }
    
    printf(RED "\nATENÇÃO: Esta operação irá pagar toda a dívida do usuário.\n" RESET);
    printf("Digite 1 para confirmar ou 0 para cancelar: ");
    int confirm;
    scanf("%d", &confirm);
    while (getchar() != '\n');
    
    if (confirm != 1) {
        printf(YELLOW "Operação cancelada.\n" RESET);
        pause_screen();
        return;
    }
    
    bool can_pay;
    DuckMarketPlace__prePayDebt(user_id, &can_pay);
    
    if (can_pay) {
        DuckMarketPlace__payDebt(user_id);
        show_success("Dívida paga com sucesso!");
        printf("\nEstado após pagamento:\n");
        print_user_info(user_id);
        
        // Mostrar nova dívida
        DuckMarketPlace__showUserDebt(user_id, &user_debt);
        printf("\n" GREEN "Nova dívida: %d\n" RESET, user_debt);
    } else {
        show_error("Não foi possível pagar a dívida!");
        printf(YELLOW "Verifique se o usuário existe e possui dívidas.\n" RESET);
    }
    
    pause_screen();
}

// ======================== OPERAÇÕES DE PRODUTO ========================

void add_product_operation() {
    print_header();
    printf(BOLD "═══ ADICIONAR PRODUTO ═══\n" RESET);
    
    int product_id = get_int_input("Digite o ID do produto: ");
    int product_name = get_int_input("Digite o nome do produto (número): ");
    int seller_id = get_int_input("Digite o ID do vendedor: ");
    int stock = get_int_input("Digite o estoque inicial: ");
    int price = get_int_input("Digite o preço: ");
    
    bool can_add;
    DuckMarketPlace__preAddProduct(product_id, product_name, seller_id, stock, price, &can_add);
    
    if (can_add) {
        DuckMarketPlace__addProduct(product_id, product_name, seller_id, stock, price);
        show_success("Produto adicionado com sucesso!");
        printf("\n");
        print_product_info(product_id);
    } else {
        show_error("Não foi possível adicionar o produto!");
        printf(YELLOW "Verifique se o vendedor existe e os valores são válidos.\n" RESET);
    }
    
    pause_screen();
}

void list_products_operation() {
    print_header();
    printf(BOLD "═══ LISTA DE PRODUTOS ═══\n" RESET);
    
    bool found_products = false;
    
    for (int i = 1; i <= 10; i++) {
        if (product_exists(i)) {
            print_product_info(i);
            printf("\n");
            found_products = true;
        }
    }
    
    if (!found_products) {
        printf(YELLOW "Nenhum produto encontrado.\n" RESET);
    }
    
    pause_screen();
}

void alter_product_stock_operation() {
    print_header();
    printf(BOLD "═══ ALTERAR ESTOQUE DO PRODUTO ═══\n" RESET);
    
    int product_id = get_int_input("Digite o ID do produto: ");
    
    printf("\nEstado atual:\n");
    print_product_info(product_id);
    
    int new_stock = get_int_input("\nDigite o novo estoque: ");
    
    bool can_alter;
    DuckMarketPlace__preAltProductStock(product_id, new_stock, &can_alter);
    
    if (can_alter) {
        DuckMarketPlace__altProductStock(product_id, new_stock);
        show_success("Estoque alterado com sucesso!");
        printf("\nEstado após alteração:\n");
        print_product_info(product_id);
    } else {
        show_error("Não foi possível alterar o estoque!");
    }
    
    pause_screen();
}

void alter_product_price_operation() {
    print_header();
    printf(BOLD "═══ ALTERAR PREÇO DO PRODUTO ═══\n" RESET);
    
    int product_id = get_int_input("Digite o ID do produto: ");
    
    printf("\nEstado atual:\n");
    print_product_info(product_id);
    
    int new_price = get_int_input("\nDigite o novo preço: ");
    
    bool can_alter;
    DuckMarketPlace__preAltProductPrice(product_id, new_price, &can_alter);
    
    if (can_alter) {
        DuckMarketPlace__altProductPrice(product_id, new_price);
        show_success("Preço alterado com sucesso!");
        printf("\nEstado após alteração:\n");
        print_product_info(product_id);
    } else {
        show_error("Não foi possível alterar o preço!");
    }
    
    pause_screen();
}

// ======================== OPERAÇÕES DE TRANSAÇÃO ========================

void buy_product_operation() {
    print_header();
    printf(BOLD "═══ COMPRAR PRODUTO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    int product_id = get_int_input("Digite o ID do produto: ");
    int quantity = get_int_input("Digite a quantidade: ");
    
    printf("\nEstado antes da compra:\n");
    printf("Usuário:\n");
    print_user_info(user_id);
    printf("\nProduto:\n");
    print_product_info(product_id);
    
    bool can_buy;
    DuckMarketPlace__preBuyProduct(user_id, product_id, quantity, &can_buy);
    
    if (can_buy) {
        DuckMarketPlace__buyProduct(user_id, product_id, quantity);
        show_success("Compra realizada com sucesso!");
        printf("\nEstado após a compra:\n");
        printf("Usuário:\n");
        print_user_info(user_id);
        printf("\nProduto:\n");
        print_product_info(product_id);
    } else {
        show_error("Não foi possível realizar a compra!");
        printf(YELLOW "Verifique crédito, estoque e se não é o próprio vendedor.\n" RESET);
    }
    
    pause_screen();
}

void return_product_operation() {
    print_header();
    printf(BOLD "═══ DEVOLVER PRODUTO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    int product_id = get_int_input("Digite o ID do produto: ");
    int product_price = get_int_input("Digite o preço do produto: ");
    int product_quant = get_int_input("Digite a quantidade do produto: ");
    
    printf("\nEstado antes da devolução:\n");
    print_user_info(user_id);
    
    bool can_return;
    DuckMarketPlace__preReturnProduct(
        user_id,
        product_id,
        product_price,
        product_quant,
        &can_return);
    
    if (can_return) {
        DuckMarketPlace__returnProduct(
        user_id,
        product_id,
        product_price,
        product_quant);

        show_success("Produto devolvido com sucesso!");
        printf("\nEstado após devolver:\n");
        print_user_info(user_id);
    } else {
        show_error("Não foi possível devolver o produto!");
        printf(YELLOW "Verifique se há produtos comprados com as informações especificadas.\n" RESET);
    }
    
    pause_screen();
}

void add_to_cart_operation() {
    print_header();
    printf(BOLD "═══ ADICIONAR AO CARRINHO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    int product_id = get_int_input("Digite o ID do produto: ");
    int quantity = get_int_input("Digite a quantidade: ");
    
    printf("\nEstado antes:\n");
    print_user_info(user_id);
    
    bool can_add;
    DuckMarketPlace__preAddProductToCart(user_id, product_id, quantity, &can_add);
    
    if (can_add) {
        DuckMarketPlace__addProductToCart(user_id, product_id, quantity);
        show_success("Produto adicionado ao carrinho!");
        printf("\nEstado após adicionar:\n");
        print_user_info(user_id);
    } else {
        show_error("Não foi possível adicionar ao carrinho!");
    }
    
    pause_screen();
}

void remove_from_cart_operation() {
    print_header();
    printf(BOLD "═══ REMOVER PRODUTO DO CARRINHO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    int product_id = get_int_input("Digite o ID do produto: ");
    int product_price = get_int_input("Digite o preço do produto: ");
    int product_quant = get_int_input("Digite a quantidade do produto: ");
    
    printf("\nEstado antes de remover o produto:\n");
    print_user_info(user_id);
    
    bool can_remove;
    DuckMarketPlace__preRemoveProductFromCart(
        user_id,
        product_id,
        product_price,
        product_quant,
        &can_remove);
    
    if (can_remove) {
        DuckMarketPlace__removeProductFromCart(
        user_id,
        product_id,
        product_price,
        product_quant);

        show_success("Produto removido do carrinho com sucesso!");
        printf("\nEstado após a remoção:\n");
        print_user_info(user_id);
    } else {
        show_error("Não foi possível remover o produto do carrinho!");
        printf(YELLOW "Verifique se há produtos no carrinho com as informações especificadas.\n" RESET);
    }
    
    pause_screen();
}

void buy_cart_operation() {
    print_header();
    printf(BOLD "═══ COMPRAR CARRINHO ═══\n" RESET);
    
    int user_id = get_int_input("Digite o ID do usuário: ");
    
    printf("\nEstado antes da compra:\n");
    print_user_info(user_id);
    
    bool can_buy;
    DuckMarketPlace__preBuyProductsFromCart(user_id, &can_buy);
    
    if (can_buy) {
        DuckMarketPlace__buyProductsFromCart(user_id);
        show_success("Carrinho comprado com sucesso!");
        printf("\nEstado após a compra:\n");
        print_user_info(user_id);
    } else {
        show_error("Não foi possível comprar o carrinho!");
        printf(YELLOW "Verifique se há produtos no carrinho e crédito suficiente.\n" RESET);
    }
    
    pause_screen();
}

// ======================== MENUS ========================

void user_menu() {
    int choice;
    do {
        print_header();
        printf(BOLD "═══ GERENCIAMENTO DE USUÁRIOS ═══\n" RESET);
        printf("1. Adicionar Usuário\n");
        printf("2. Listar Usuários\n");
        printf("3. Alterar Nome de Usuário\n");
        printf("4. Adicionar Crédito\n");
        printf("5. Retirar Crédito\n");
        printf("6. Pagar Dívida\n");
        printf("7. Remover Usuário\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("\nEscolha uma opção: ");
        
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice) {
            case 1: add_user_operation(); break;
            case 2: list_users_operation(); break;
            case 3: alter_user_name_operation(); break;
            case 4: add_credit_operation(); break;
            case 5: withdraw_credit_operation(); break;
            case 6: pay_debt_operation(); break;
            case 7: remove_user_operation(); break;
            case 0: break;
            default: 
                show_error("Opção inválida!");
                pause_screen();
        }
    } while (choice != 0);
}

void product_menu() {
    int choice;
    do {
        print_header();
        printf(BOLD "═══ GERENCIAMENTO DE PRODUTOS ═══\n" RESET);
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Alterar Estoque\n");
        printf("4. Alterar Preço\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("\nEscolha uma opção: ");
        
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice) {
            case 1: add_product_operation(); break;
            case 2: list_products_operation(); break;
            case 3: alter_product_stock_operation(); break;
            case 4: alter_product_price_operation(); break;
            case 0: break;
            default: 
                show_error("Opção inválida!");
                pause_screen();
        }
    } while (choice != 0);
}

void transaction_menu() {
    int choice;
    do {
        print_header();
        printf(BOLD "═══ TRANSAÇÕES ═══\n" RESET);
        printf("1. Comprar Produto\n");
        printf("2. Devolver Produto\n");
        printf("3. Adicionar ao Carrinho\n");
        printf("4. Remover produto do carrinho Carrinho\n");
        printf("5. Comprar Carrinho\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("\nEscolha uma opção: ");
        
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice) {
            case 1: buy_product_operation(); break;
            case 2: return_product_operation(); break;
            case 3: add_to_cart_operation(); break;
            case 4: remove_from_cart_operation(); break;
            case 5: buy_cart_operation(); break;
            case 0: break;
            default: 
                show_error("Opção inválida!");
                pause_screen();
        }
    } while (choice != 0);
}

void main_menu() {
    int choice;
    do {
        print_header();
        printf(BOLD "═══ MENU PRINCIPAL ═══\n" RESET);
        printf("1. Gerenciar Usuários\n");
        printf("2. Gerenciar Produtos\n");
        printf("3. Transações\n");
        printf("4. Sair\n");
        printf("\nEscolha uma opção: ");
        
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice) {
            case 1: user_menu(); break;
            case 2: product_menu(); break;
            case 3: transaction_menu(); break;
            case 4: 
                clear_screen();
                printf(GREEN BOLD "Obrigado por usar o DuckMarketPlace!\n" RESET);
                break;
            default: 
                show_error("Opção inválida!");
                pause_screen();
        }
    } while (choice != 4);
}

int main() {
    // Inicializar o sistema DuckMarketPlace
    DuckMarketPlace__INITIALISATION();
    
    // Mostrar tela de boas-vindas
    print_header();
    printf(GREEN BOLD "Sistema DuckMarketPlace inicializado com sucesso!\n" RESET);
    printf(YELLOW "Bem-vindo ao Terminal de Testes do DuckMarketPlace.\n" RESET);
    pause_screen();
    
    // Executar menu principal
    main_menu();
    
    return 0;
}
