#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DuckMarketPlace.h"

void print_user_info(DuckMarketPlace__IDUSUARIO userId) {
    DuckMarketPlace__NOMEUSUARIO userName;
    int32_t userCredit;
    int32_t cartValue;
    
    printf("\n--- Informações do Usuário %d ---\n", userId);
    
    // Mostra nome do usuário
    DuckMarketPlace__showUserName(userId, &userName);
    printf("Nome: %d\n", userName);
    
    // Mostra crédito do usuário
    DuckMarketPlace__showUserCredit(userId, &userCredit);
    printf("Crédito: %d\n", userCredit);
    
    // Mostra valor do carrinho
    DuckMarketPlace__showUserCartValue(userId, &cartValue);
    printf("Valor do carrinho: %d\n", cartValue);
}

void print_product_info(DuckMarketPlace__IDPRODUTO productId) {
    DuckMarketPlace__NOMEPRODUTO productName;
    int32_t productStock;
    int32_t productPrice;
    
    printf("\n--- Informações do Produto %d ---\n", productId);
    
    // Mostra nome do produto
    DuckMarketPlace__showProductName(productId, &productName);
    printf("Nome: %d\n", productName);
    
    // Mostra estoque do produto
    DuckMarketPlace__showProductStock(productId, &productStock);
    printf("Estoque: %d\n", productStock);
    
    // Mostra preço do produto
    DuckMarketPlace__showProductPrice(productId, &productPrice);
    printf("Preço: %d\n", productPrice);
}

int main() {
    printf("=== DuckMarketPlace - Sistema de Marketplace ===\n");
    printf("Inicializando o sistema...\n");
    
    // Inicializa o sistema
    DuckMarketPlace__INITIALISATION();
    printf("Sistema inicializado com sucesso!\n\n");
    
    // Testa a operação addUser
    printf("=== Testando operação addUser ===\n");
    
    // Parâmetros para adicionar usuário
    DuckMarketPlace__IDUSUARIO userId1 = 1;
    DuckMarketPlace__NOMEUSUARIO userName1 = 101;
    int32_t userCredit1 = 1000;
    
    DuckMarketPlace__IDUSUARIO userId2 = 2;
    DuckMarketPlace__NOMEUSUARIO userName2 = 102;
    int32_t userCredit2 = 500;
    
    // Teste 1: adicionar primeiro usuário
    printf("\n1. Tentando adicionar usuário %d com nome %d e crédito %d\n", 
           userId1, userName1, userCredit1);
    
    bool canAddUser1 = false;
    DuckMarketPlace__preAddUser(userId1, userName1, userCredit1, &canAddUser1);
    
    if (canAddUser1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addUser(userId1, userName1, userCredit1);
        printf("   Usuário adicionado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: adicionar segundo usuário
    printf("\n2. Tentando adicionar usuário %d com nome %d e crédito %d\n", 
           userId2, userName2, userCredit2);
    
    bool canAddUser2 = false;
    DuckMarketPlace__preAddUser(userId2, userName2, userCredit2, &canAddUser2);
    
    if (canAddUser2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addUser(userId2, userName2, userCredit2);
        printf("   Usuário adicionado com sucesso!\n");
        print_user_info(userId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 3: tentar adicionar usuário com ID duplicado (deve falhar)
    printf("\n3. Tentando adicionar usuário com ID duplicado (%d)\n", userId1);
    
    DuckMarketPlace__NOMEUSUARIO userName3 = 103;
    int32_t userCredit3 = 750;
    
    bool canAddUser3 = false;
    DuckMarketPlace__preAddUser(userId1, userName3, userCredit3, &canAddUser3);
    
    if (canAddUser3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addUser(userId1, userName3, userCredit3);
        printf("   Usuário adicionado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID duplicado)\n");
    }
    
    // Teste 4: tentar adicionar usuário com nome dummy (deve falhar)
    printf("\n4. Tentando adicionar usuário com nome dummy (deve falhar)\n");
    
    DuckMarketPlace__IDUSUARIO userId4 = 3;
    DuckMarketPlace__NOMEUSUARIO userNameDummy = DuckMarketPlace__userDummy;
    int32_t userCredit4 = 300;
    
    bool canAddUser4 = false;
    DuckMarketPlace__preAddUser(userId4, userNameDummy, userCredit4, &canAddUser4);
    
    if (canAddUser4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addUser(userId4, userNameDummy, userCredit4);
        printf("   Usuário adicionado com sucesso!\n");
        print_user_info(userId4);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - nome dummy)\n");
    }
    
    // Teste 5: tentar adicionar usuário com ID dummy (deve falhar)
    printf("\n5. Tentando adicionar usuário com ID dummy (deve falhar)\n");
    
    DuckMarketPlace__IDUSUARIO userIdDummy = DuckMarketPlace__userIdDummy;
    DuckMarketPlace__NOMEUSUARIO userName5 = 105;
    int32_t userCredit5 = 200;
    
    bool canAddUser5 = false;
    DuckMarketPlace__preAddUser(userIdDummy, userName5, userCredit5, &canAddUser5);
    
    if (canAddUser5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addUser(userIdDummy, userName5, userCredit5);
        printf("   Usuário adicionado com sucesso!\n");
        print_user_info(userIdDummy);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID dummy)\n");
    }
    
    // Testa a operação altNameUser
    printf("\n=== Testando operação altNameUser ===\n");
    
    // Teste 1: alterar nome de usuário existente (deve funcionar)
    printf("\n1. Tentando alterar nome do usuário %d de %d para 201\n", userId1, userName1);
    
    DuckMarketPlace__NOMEUSUARIO newUserName1 = 201;
    bool canAltName1 = false;
    DuckMarketPlace__preAltNameUser(userId1, newUserName1, &canAltName1);
    
    if (canAltName1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altNameUser(userId1, newUserName1);
        printf("   Nome alterado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: alterar nome do segundo usuário (deve funcionar)
    printf("\n2. Tentando alterar nome do usuário %d de %d para 202\n", userId2, userName2);
    
    DuckMarketPlace__NOMEUSUARIO newUserName2 = 202;
    bool canAltName2 = false;
    DuckMarketPlace__preAltNameUser(userId2, newUserName2, &canAltName2);
    
    if (canAltName2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altNameUser(userId2, newUserName2);
        printf("   Nome alterado com sucesso!\n");
        print_user_info(userId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 3: tentar alterar nome para dummy (deve falhar)
    printf("\n3. Tentando alterar nome do usuário %d para nome dummy (deve falhar)\n", userId1);
    
    DuckMarketPlace__NOMEUSUARIO dummyName = DuckMarketPlace__userDummy;
    bool canAltName3 = false;
    DuckMarketPlace__preAltNameUser(userId1, dummyName, &canAltName3);
    
    if (canAltName3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altNameUser(userId1, dummyName);
        printf("   Nome alterado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - nome dummy)\n");
    }
    
    // Teste 4: tentar alterar nome de usuário inexistente (deve falhar)
    printf("\n4. Tentando alterar nome de usuário inexistente (ID 9)\n");
    
    DuckMarketPlace__IDUSUARIO inexistentUser = 9;
    DuckMarketPlace__NOMEUSUARIO newName = 299;
    bool canAltName4 = false;
    DuckMarketPlace__preAltNameUser(inexistentUser, newName, &canAltName4);
    
    if (canAltName4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altNameUser(inexistentUser, newName);
        printf("   Nome alterado com sucesso!\n");
        print_user_info(inexistentUser);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário não existe)\n");
    }
    
    // Testa a operação addCredit
    printf("\n=== Testando operação addCredit ===\n");
    
    // Teste 1: adicionar crédito ao usuário 1 (deve funcionar)
    printf("\n1. Tentando adicionar 500 de crédito ao usuário %d\n", userId1);
    
    int32_t creditToAdd1 = 500;
    bool canAddCredit1 = false;
    DuckMarketPlace__preAddCredit(userId1, creditToAdd1, &canAddCredit1);
    
    printf("   Crédito atual antes: ");
    int32_t creditBefore1;
    DuckMarketPlace__showUserCredit(userId1, &creditBefore1);
    printf("%d\n", creditBefore1);
    
    if (canAddCredit1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addCredit(userId1, creditToAdd1);
        printf("   Crédito adicionado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: adicionar crédito ao usuário 2 (deve funcionar)
    printf("\n2. Tentando adicionar 250 de crédito ao usuário %d\n", userId2);
    
    int32_t creditToAdd2 = 250;
    bool canAddCredit2 = false;
    DuckMarketPlace__preAddCredit(userId2, creditToAdd2, &canAddCredit2);
    
    printf("   Crédito atual antes: ");
    int32_t creditBefore2;
    DuckMarketPlace__showUserCredit(userId2, &creditBefore2);
    printf("%d\n", creditBefore2);
    
    if (canAddCredit2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addCredit(userId2, creditToAdd2);
        printf("   Crédito adicionado com sucesso!\n");
        print_user_info(userId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 3: tentar adicionar crédito zero (deve falhar)
    printf("\n3. Tentando adicionar 0 de crédito ao usuário %d (deve falhar)\n", userId1);
    
    int32_t zeroCreditToAdd = 0;
    bool canAddCredit3 = false;
    DuckMarketPlace__preAddCredit(userId1, zeroCreditToAdd, &canAddCredit3);
    
    if (canAddCredit3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addCredit(userId1, zeroCreditToAdd);
        printf("   Crédito adicionado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - crédito zero)\n");
    }
    
    // Teste 4: tentar adicionar crédito negativo (deve falhar)
    printf("\n4. Tentando adicionar -100 de crédito ao usuário %d (deve falhar)\n", userId1);
    
    int32_t negativeCreditToAdd = -100;
    bool canAddCredit4 = false;
    DuckMarketPlace__preAddCredit(userId1, negativeCreditToAdd, &canAddCredit4);
    
    if (canAddCredit4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addCredit(userId1, negativeCreditToAdd);
        printf("   Crédito adicionado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - crédito negativo)\n");
    }
    
    // Teste 5: tentar adicionar crédito a usuário inexistente (deve falhar)
    printf("\n5. Tentando adicionar 100 de crédito a usuário inexistente (ID 8)\n");
    
    DuckMarketPlace__IDUSUARIO inexistentUserId = 8;
    int32_t creditToAdd5 = 100;
    bool canAddCredit5 = false;
    DuckMarketPlace__preAddCredit(inexistentUserId, creditToAdd5, &canAddCredit5);
    
    if (canAddCredit5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addCredit(inexistentUserId, creditToAdd5);
        printf("   Crédito adicionado com sucesso!\n");
        print_user_info(inexistentUserId);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário não existe)\n");
    }
    
    // Testa a operação withdrawCredit
    printf("\n=== Testando operação withdrawCredit ===\n");
    
    // Teste 1: retirar crédito do usuário 1 (deve funcionar)
    printf("\n1. Tentando retirar 200 de crédito do usuário %d\n", userId1);
    
    int32_t creditToWithdraw1 = 200;
    bool canWithdrawCredit1 = false;
    DuckMarketPlace__preWithdrawCredit(userId1, creditToWithdraw1, &canWithdrawCredit1);
    
    printf("   Crédito atual antes: ");
    int32_t creditBeforeWithdraw1;
    DuckMarketPlace__showUserCredit(userId1, &creditBeforeWithdraw1);
    printf("%d\n", creditBeforeWithdraw1);
    
    if (canWithdrawCredit1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__withdrawCredit(userId1, creditToWithdraw1);
        printf("   Crédito retirado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: retirar crédito do usuário 2 (deve funcionar)
    printf("\n2. Tentando retirar 100 de crédito do usuário %d\n", userId2);
    
    int32_t creditToWithdraw2 = 100;
    bool canWithdrawCredit2 = false;
    DuckMarketPlace__preWithdrawCredit(userId2, creditToWithdraw2, &canWithdrawCredit2);
    
    printf("   Crédito atual antes: ");
    int32_t creditBeforeWithdraw2;
    DuckMarketPlace__showUserCredit(userId2, &creditBeforeWithdraw2);
    printf("%d\n", creditBeforeWithdraw2);
    
    if (canWithdrawCredit2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__withdrawCredit(userId2, creditToWithdraw2);
        printf("   Crédito retirado com sucesso!\n");
        print_user_info(userId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 3: tentar retirar mais crédito do que disponível (deve falhar)
    printf("\n3. Tentando retirar mais crédito do que disponível do usuário %d\n", userId1);
    
    int32_t excessiveCreditToWithdraw = 9999;
    bool canWithdrawCredit3 = false;
    DuckMarketPlace__preWithdrawCredit(userId1, excessiveCreditToWithdraw, &canWithdrawCredit3);
    
    printf("   Crédito atual: ");
    int32_t currentCredit;
    DuckMarketPlace__showUserCredit(userId1, &currentCredit);
    printf("%d\n", currentCredit);
    printf("   Tentando retirar: %d\n", excessiveCreditToWithdraw);
    
    if (canWithdrawCredit3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__withdrawCredit(userId1, excessiveCreditToWithdraw);
        printf("   Crédito retirado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - crédito insuficiente)\n");
    }
    
    // Teste 4: tentar retirar crédito zero (deve falhar)
    printf("\n4. Tentando retirar 0 de crédito do usuário %d (deve falhar)\n", userId1);
    
    int32_t zeroCreditToWithdraw = 0;
    bool canWithdrawCredit4 = false;
    DuckMarketPlace__preWithdrawCredit(userId1, zeroCreditToWithdraw, &canWithdrawCredit4);
    
    if (canWithdrawCredit4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__withdrawCredit(userId1, zeroCreditToWithdraw);
        printf("   Crédito retirado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - crédito zero)\n");
    }
    
    // Teste 5: tentar retirar crédito negativo (deve falhar)
    printf("\n5. Tentando retirar -50 de crédito do usuário %d (deve falhar)\n", userId1);
    
    int32_t negativeCreditToWithdraw = -50;
    bool canWithdrawCredit5 = false;
    DuckMarketPlace__preWithdrawCredit(userId1, negativeCreditToWithdraw, &canWithdrawCredit5);
    
    if (canWithdrawCredit5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__withdrawCredit(userId1, negativeCreditToWithdraw);
        printf("   Crédito retirado com sucesso!\n");
        print_user_info(userId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - crédito negativo)\n");
    }
    
    // Teste 6: tentar retirar crédito de usuário inexistente (deve falhar)
    printf("\n6. Tentando retirar 50 de crédito de usuário inexistente (ID 7)\n");
    
    DuckMarketPlace__IDUSUARIO inexistentUserId2 = 7;
    int32_t creditToWithdraw6 = 50;
    bool canWithdrawCredit6 = false;
    DuckMarketPlace__preWithdrawCredit(inexistentUserId2, creditToWithdraw6, &canWithdrawCredit6);
    
    if (canWithdrawCredit6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__withdrawCredit(inexistentUserId2, creditToWithdraw6);
        printf("   Crédito retirado com sucesso!\n");
        print_user_info(inexistentUserId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário não existe)\n");
    }
    
    // Testa a operação addProduct
    printf("\n=== Testando operação addProduct ===\n");
    
    // Teste 1: adicionar primeiro produto (deve funcionar)
    printf("\n1. Tentando adicionar produto com ID 1, nome 501, vendedor %d, estoque 10, preço 50\n", userId1);
    
    DuckMarketPlace__IDPRODUTO productId1 = 1;
    DuckMarketPlace__NOMEPRODUTO productName1 = 501;
    DuckMarketPlace__IDUSUARIO sellerId1 = userId1;
    int32_t productStock1 = 10;
    int32_t productPrice1 = 50;
    
    bool canAddProduct1 = false;
    DuckMarketPlace__preAddProduct(productId1, productName1, sellerId1, productStock1, productPrice1, &canAddProduct1);
    
    if (canAddProduct1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProduct(productId1, productName1, sellerId1, productStock1, productPrice1);
        printf("   Produto adicionado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: adicionar segundo produto (deve funcionar)
    printf("\n2. Tentando adicionar produto com ID 2, nome 502, vendedor %d, estoque 5, preço 100\n", userId2);
    
    DuckMarketPlace__IDPRODUTO productId2 = 2;
    DuckMarketPlace__NOMEPRODUTO productName2 = 502;
    DuckMarketPlace__IDUSUARIO sellerId2 = userId2;
    int32_t productStock2 = 5;
    int32_t productPrice2 = 100;
    
    bool canAddProduct2 = false;
    DuckMarketPlace__preAddProduct(productId2, productName2, sellerId2, productStock2, productPrice2, &canAddProduct2);
    
    if (canAddProduct2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProduct(productId2, productName2, sellerId2, productStock2, productPrice2);
        printf("   Produto adicionado com sucesso!\n");
        print_product_info(productId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 3: tentar adicionar produto com ID duplicado (deve falhar)
    printf("\n3. Tentando adicionar produto com ID duplicado (%d)\n", productId1);
    
    DuckMarketPlace__NOMEPRODUTO productName3 = 503;
    DuckMarketPlace__IDUSUARIO sellerId3 = userId1;
    int32_t productStock3 = 8;
    int32_t productPrice3 = 75;
    
    bool canAddProduct3 = false;
    DuckMarketPlace__preAddProduct(productId1, productName3, sellerId3, productStock3, productPrice3, &canAddProduct3);
    
    if (canAddProduct3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProduct(productId1, productName3, sellerId3, productStock3, productPrice3);
        printf("   Produto adicionado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID duplicado)\n");
    }
    
    // Teste 4: tentar adicionar produto com nome dummy (deve falhar)
    printf("\n4. Tentando adicionar produto com nome dummy (deve falhar)\n");
    
    DuckMarketPlace__IDPRODUTO productId4 = 3;
    DuckMarketPlace__NOMEPRODUTO productNameDummy = DuckMarketPlace__productDummy;
    DuckMarketPlace__IDUSUARIO sellerId4 = userId1;
    int32_t productStock4 = 15;
    int32_t productPrice4 = 30;
    
    bool canAddProduct4 = false;
    DuckMarketPlace__preAddProduct(productId4, productNameDummy, sellerId4, productStock4, productPrice4, &canAddProduct4);
    
    if (canAddProduct4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProduct(productId4, productNameDummy, sellerId4, productStock4, productPrice4);
        printf("   Produto adicionado com sucesso!\n");
        print_product_info(productId4);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - nome dummy)\n");
    }
    
    // Teste 5: tentar adicionar produto com ID dummy (deve falhar)
    printf("\n5. Tentando adicionar produto com ID dummy (deve falhar)\n");
    
    DuckMarketPlace__IDPRODUTO productIdDummy = DuckMarketPlace__productIdDummy;
    DuckMarketPlace__NOMEPRODUTO productName5 = 505;
    DuckMarketPlace__IDUSUARIO sellerId5 = userId2;
    int32_t productStock5 = 20;
    int32_t productPrice5 = 25;
    
    bool canAddProduct5 = false;
    DuckMarketPlace__preAddProduct(productIdDummy, productName5, sellerId5, productStock5, productPrice5, &canAddProduct5);
    
    if (canAddProduct5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProduct(productIdDummy, productName5, sellerId5, productStock5, productPrice5);
        printf("   Produto adicionado com sucesso!\n");
        print_product_info(productIdDummy);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID dummy)\n");
    }
    
    // Teste 6: tentar adicionar produto com vendedor inexistente (deve falhar)
    printf("\n6. Tentando adicionar produto com vendedor inexistente (ID 9)\n");
    
    DuckMarketPlace__IDPRODUTO productId6 = 4;
    DuckMarketPlace__NOMEPRODUTO productName6 = 506;
    DuckMarketPlace__IDUSUARIO inexistentSeller = 9;
    int32_t productStock6 = 12;
    int32_t productPrice6 = 40;
    
    bool canAddProduct6 = false;
    DuckMarketPlace__preAddProduct(productId6, productName6, inexistentSeller, productStock6, productPrice6, &canAddProduct6);
    
    if (canAddProduct6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProduct(productId6, productName6, inexistentSeller, productStock6, productPrice6);
        printf("   Produto adicionado com sucesso!\n");
        print_product_info(productId6);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - vendedor não existe)\n");
    }
    
    // Testa a operação removeProduct
    printf("\n=== Testando operação removeProduct ===\n");
    
    // Teste 1: remover produto existente (produto 2 - deve funcionar)
    printf("\n1. Tentando remover produto %d (deve funcionar)\n", productId2);
    
    bool canRemoveProduct1 = false;
    DuckMarketPlace__preRemoveProduct(productId2, &canRemoveProduct1);
    
    if (canRemoveProduct1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProduct(productId2);
        printf("   Produto removido com sucesso!\n");
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: tentar remover produto que já foi removido (deve falhar)
    printf("\n2. Tentando remover produto %d novamente (deve falhar)\n", productId2);
    
    bool canRemoveProduct2 = false;
    DuckMarketPlace__preRemoveProduct(productId2, &canRemoveProduct2);
    
    if (canRemoveProduct2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProduct(productId2);
        printf("   Produto removido com sucesso!\n");
        print_product_info(productId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não existe)\n");
    }
    
    // Teste 3: tentar remover produto inexistente (deve falhar)
    printf("\n3. Tentando remover produto inexistente (ID 99)\n");
    
    DuckMarketPlace__IDPRODUTO inexistentProductId = 99;
    bool canRemoveProduct3 = false;
    DuckMarketPlace__preRemoveProduct(inexistentProductId, &canRemoveProduct3);
    
    if (canRemoveProduct3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProduct(inexistentProductId);
        printf("   Produto removido com sucesso!\n");
        print_product_info(inexistentProductId);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não existe)\n");
    }
    
    // Teste 4: tentar remover produto com ID dummy (deve falhar)
    printf("\n4. Tentando remover produto com ID dummy (deve falhar)\n");
    
    DuckMarketPlace__IDPRODUTO dummyProductId = DuckMarketPlace__productIdDummy;
    bool canRemoveProduct4 = false;
    DuckMarketPlace__preRemoveProduct(dummyProductId, &canRemoveProduct4);
    
    if (canRemoveProduct4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProduct(dummyProductId);
        printf("   Produto removido com sucesso!\n");
        print_product_info(dummyProductId);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID dummy)\n");
    }
    
    // Testa a operação altProductName
    printf("\n=== Testando operação altProductName ===\n");
    
    // Teste 1: alterar nome de produto existente (produto 1 - deve funcionar)
    printf("\n1. Tentando alterar nome do produto %d de 501 para 601\n", productId1);
    
    printf("   Produto antes da alteração:\n");
    print_product_info(productId1);
    
    DuckMarketPlace__NOMEPRODUTO newProductName1 = 601;
    bool canAltProductName1 = false;
    DuckMarketPlace__preAltProductName(productId1, newProductName1, &canAltProductName1);
    
    if (canAltProductName1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductName(productId1, newProductName1);
        printf("   Nome do produto alterado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 3: tentar alterar nome para nome dummy (deve falhar)
    printf("\n3. Tentando alterar nome do produto %d para nome dummy (deve falhar)\n", productId1);
    
    DuckMarketPlace__NOMEPRODUTO dummyProductName = DuckMarketPlace__productDummy;
    bool canAltProductName3 = false;
    DuckMarketPlace__preAltProductName(productId1, dummyProductName, &canAltProductName3);
    
    if (canAltProductName3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductName(productId1, dummyProductName);
        printf("   Nome do produto alterado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - nome dummy)\n");
    }
    
    // Teste 4: tentar alterar nome de produto inexistente (deve falhar)
    printf("\n4. Tentando alterar nome de produto inexistente (ID 88)\n");
    
    DuckMarketPlace__IDPRODUTO inexistentProductId2 = 88;
    DuckMarketPlace__NOMEPRODUTO newProductName4 = 688;
    bool canAltProductName4 = false;
    DuckMarketPlace__preAltProductName(inexistentProductId2, newProductName4, &canAltProductName4);
    
    if (canAltProductName4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductName(inexistentProductId2, newProductName4);
        printf("   Nome do produto alterado com sucesso!\n");
        print_product_info(inexistentProductId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não existe)\n");
    }
    
    // Teste 5: tentar alterar nome de produto que foi removido (deve falhar)
    printf("\n5. Tentando alterar nome do produto %d que foi removido (deve falhar)\n", productId2);
    
    DuckMarketPlace__NOMEPRODUTO newProductName5 = 602;
    bool canAltProductName5 = false;
    DuckMarketPlace__preAltProductName(productId2, newProductName5, &canAltProductName5);
    
    if (canAltProductName5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductName(productId2, newProductName5);
        printf("   Nome do produto alterado com sucesso!\n");
        print_product_info(productId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto removido)\n");
    }
    
    // Teste 6: tentar alterar nome usando ID dummy (deve falhar)
    printf("\n6. Tentando alterar nome de produto com ID dummy (deve falhar)\n");
    
    DuckMarketPlace__IDPRODUTO dummyProductId2 = DuckMarketPlace__productIdDummy;
    DuckMarketPlace__NOMEPRODUTO newProductName6 = 600;
    bool canAltProductName6 = false;
    DuckMarketPlace__preAltProductName(dummyProductId2, newProductName6, &canAltProductName6);
    
    if (canAltProductName6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductName(dummyProductId2, newProductName6);
        printf("   Nome do produto alterado com sucesso!\n");
        print_product_info(dummyProductId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID dummy)\n");
    }
    
    // Testa a operação altProductStock
    printf("\n=== Testando operação altProductStock ===\n");
    
    // Teste 1: alterar estoque de produto existente (produto 1 - deve funcionar)
    printf("\n1. Tentando alterar estoque do produto %d de 10 para 25\n", productId1);
    
    printf("   Produto antes da alteração:\n");
    print_product_info(productId1);
    
    int32_t newStock1 = 25;
    bool canAltProductStock1 = false;
    DuckMarketPlace__preAltProductStock(productId1, newStock1, &canAltProductStock1);
    
    if (canAltProductStock1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductStock(productId1, newStock1);
        printf("   Estoque do produto alterado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: alterar estoque para zero (deve falhar)
    printf("\n2. Tentando alterar estoque do produto %d para 0 (deve falhar)\n", productId1);
    
    int32_t zeroStock = 0;
    bool canAltProductStock2 = false;
    DuckMarketPlace__preAltProductStock(productId1, zeroStock, &canAltProductStock2);
    
    if (canAltProductStock2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductStock(productId1, zeroStock);
        printf("   Estoque do produto alterado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - estoque zero não é permitido)\n");
    }
    
    // Teste 3: tentar alterar estoque negativo (deve falhar)
    printf("\n3. Tentando alterar estoque do produto %d para -5 (deve falhar)\n", productId1);
    
    int32_t negativeStock = -5;
    bool canAltProductStock3 = false;
    DuckMarketPlace__preAltProductStock(productId1, negativeStock, &canAltProductStock3);
    
    if (canAltProductStock3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductStock(productId1, negativeStock);
        printf("   Estoque do produto alterado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - estoque negativo)\n");
    }
    
    // Teste 4: tentar alterar estoque de produto inexistente (deve falhar)
    printf("\n4. Tentando alterar estoque de produto inexistente (ID 77)\n");
    
    DuckMarketPlace__IDPRODUTO inexistentProductId3 = 77;
    int32_t newStock4 = 15;
    bool canAltProductStock4 = false;
    DuckMarketPlace__preAltProductStock(inexistentProductId3, newStock4, &canAltProductStock4);
    
    if (canAltProductStock4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductStock(inexistentProductId3, newStock4);
        printf("   Estoque do produto alterado com sucesso!\n");
        print_product_info(inexistentProductId3);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não existe)\n");
    }
    
    // Teste 5: tentar alterar estoque de produto que foi removido (deve falhar)
    printf("\n5. Tentando alterar estoque do produto %d que foi removido (deve falhar)\n", productId2);
    
    int32_t newStock5 = 20;
    bool canAltProductStock5 = false;
    DuckMarketPlace__preAltProductStock(productId2, newStock5, &canAltProductStock5);
    
    if (canAltProductStock5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductStock(productId2, newStock5);
        printf("   Estoque do produto alterado com sucesso!\n");
        print_product_info(productId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto removido)\n");
    }
    
    // Teste 6: tentar alterar estoque usando ID dummy (deve falhar)
    printf("\n6. Tentando alterar estoque de produto com ID dummy (deve falhar)\n");
    
    DuckMarketPlace__IDPRODUTO dummyProductId3 = DuckMarketPlace__productIdDummy;
    int32_t newStock6 = 30;
    bool canAltProductStock6 = false;
    DuckMarketPlace__preAltProductStock(dummyProductId3, newStock6, &canAltProductStock6);
    
    if (canAltProductStock6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductStock(dummyProductId3, newStock6);
        printf("   Estoque do produto alterado com sucesso!\n");
        print_product_info(dummyProductId3);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID dummy)\n");
    }
    
    // Testa a operação altProductPrice
    printf("\n=== Testando operação altProductPrice ===\n");
    
    // Teste 1: alterar preço de produto existente (produto 1 - deve funcionar)
    printf("\n1. Tentando alterar preço do produto %d de 50 para 75\n", productId1);
    
    printf("   Produto antes da alteração:\n");
    print_product_info(productId1);
    
    int32_t newPrice1 = 75;
    bool canAltProductPrice1 = false;
    DuckMarketPlace__preAltProductPrice(productId1, newPrice1, &canAltProductPrice1);
    
    if (canAltProductPrice1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductPrice(productId1, newPrice1);
        printf("   Preço do produto alterado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: alterar preço para zero (deve falhar)
    printf("\n2. Tentando alterar preço do produto %d para 0\n", productId1);
    
    int32_t zeroPrice = 0;
    bool canAltProductPrice2 = false;
    DuckMarketPlace__preAltProductPrice(productId1, zeroPrice, &canAltProductPrice2);
    
    if (canAltProductPrice2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductPrice(productId1, zeroPrice);
        printf("   Preço do produto alterado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - preço não pode ser alterado para zero)\n");
    }
    
    // Teste 3: tentar alterar preço negativo (deve falhar)
    printf("\n3. Tentando alterar preço do produto %d para -10 (deve falhar)\n", productId1);
    
    int32_t negativePrice = -10;
    bool canAltProductPrice3 = false;
    DuckMarketPlace__preAltProductPrice(productId1, negativePrice, &canAltProductPrice3);
    
    if (canAltProductPrice3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductPrice(productId1, negativePrice);
        printf("   Preço do produto alterado com sucesso!\n");
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - preço negativo)\n");
    }
    
    // Teste 4: tentar alterar preço de produto inexistente (deve falhar)
    printf("\n4. Tentando alterar preço de produto inexistente (ID 66)\n");
    
    DuckMarketPlace__IDPRODUTO inexistentProductId4 = 66;
    int32_t newPrice4 = 200;
    bool canAltProductPrice4 = false;
    DuckMarketPlace__preAltProductPrice(inexistentProductId4, newPrice4, &canAltProductPrice4);
    
    if (canAltProductPrice4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductPrice(inexistentProductId4, newPrice4);
        printf("   Preço do produto alterado com sucesso!\n");
        print_product_info(inexistentProductId4);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não existe)\n");
    }
    
    // Teste 5: tentar alterar preço de produto que foi removido (deve falhar)
    printf("\n5. Tentando alterar preço do produto %d que foi removido (deve falhar)\n", productId2);
    
    int32_t newPrice5 = 150;
    bool canAltProductPrice5 = false;
    DuckMarketPlace__preAltProductPrice(productId2, newPrice5, &canAltProductPrice5);
    
    if (canAltProductPrice5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductPrice(productId2, newPrice5);
        printf("   Preço do produto alterado com sucesso!\n");
        print_product_info(productId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto removido)\n");
    }
    
    // Teste 6: tentar alterar preço usando ID dummy (deve falhar)
    printf("\n6. Tentando alterar preço de produto com ID dummy (deve falhar)\n");
    
    DuckMarketPlace__IDPRODUTO dummyProductId4 = DuckMarketPlace__productIdDummy;
    int32_t newPrice6 = 99;
    bool canAltProductPrice6 = false;
    DuckMarketPlace__preAltProductPrice(dummyProductId4, newPrice6, &canAltProductPrice6);
    
    if (canAltProductPrice6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__altProductPrice(dummyProductId4, newPrice6);
        printf("   Preço do produto alterado com sucesso!\n");
        print_product_info(dummyProductId4);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID dummy)\n");
    }
    
    // Testa a operação buyProduct
    printf("\n=== Testando operação buyProduct ===\n");
    
    // Teste 1: comprar produto existente com quantidade válida (deve funcionar)
    printf("\n1. Tentando comprar 3 unidades do produto %d pelo usuário %d\n", productId1, userId2);
    
    printf("   Estado antes da compra:\n");
    print_user_info(userId2);
    print_product_info(productId1);
    
    int32_t quantityToBuy1 = 3;
    bool canBuyProduct1 = false;
    DuckMarketPlace__preBuyProduct(userId2, productId1, quantityToBuy1, &canBuyProduct1);
    
    if (canBuyProduct1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(userId2, productId1, quantityToBuy1);
        printf("   Produto comprado com sucesso!\n");
        
        printf("   Estado após a compra:\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: comprar produto com quantidade zero (deve falhar)
    printf("\n2. Tentando comprar 0 unidades do produto %d pelo usuário %d (deve falhar)\n", productId1, userId2);
    
    int32_t zeroQuantity = 0;
    bool canBuyProduct2 = false;
    DuckMarketPlace__preBuyProduct(userId2, productId1, zeroQuantity, &canBuyProduct2);
    
    if (canBuyProduct2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(userId2, productId1, zeroQuantity);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade zero)\n");
    }
    
    // Teste 3: comprar produto com quantidade negativa (deve falhar)
    printf("\n3. Tentando comprar -2 unidades do produto %d pelo usuário %d (deve falhar)\n", productId1, userId2);
    
    int32_t negativeQuantity = -2;
    bool canBuyProduct3 = false;
    DuckMarketPlace__preBuyProduct(userId2, productId1, negativeQuantity, &canBuyProduct3);
    
    if (canBuyProduct3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(userId2, productId1, negativeQuantity);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade negativa)\n");
    }
    
    // Teste 4: comprar mais do que o estoque disponível (deve falhar)
    printf("\n4. Tentando comprar mais unidades do que o estoque disponível\n");
    
    // Primeiro vamos ver o estoque atual
    int32_t currentStock;
    DuckMarketPlace__showProductStock(productId1, &currentStock);
    printf("   Estoque atual do produto %d: %d\n", productId1, currentStock);
    
    int32_t excessiveQuantity = currentStock + 10;
    printf("   Tentando comprar %d unidades\n", excessiveQuantity);
    
    bool canBuyProduct4 = false;
    DuckMarketPlace__preBuyProduct(userId2, productId1, excessiveQuantity, &canBuyProduct4);
    
    if (canBuyProduct4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(userId2, productId1, excessiveQuantity);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade maior que estoque)\n");
    }
    
    // Teste 5: comprar produto sem crédito suficiente (deve falhar)
    printf("\n5. Tentando comprar produto sem crédito suficiente\n");
    
    // Primeiro vamos ver o crédito e preço
    int32_t userCredit;
    DuckMarketPlace__showUserCredit(userId2, &userCredit);
    printf("   Crédito atual do usuário %d: %d\n", userId2, userCredit);
    
    int32_t productPrice;
    DuckMarketPlace__showProductPrice(productId1, &productPrice);
    printf("   Preço do produto %d: %d\n", productId1, productPrice);
    
    // Calcular quantidade que excede o crédito
    int32_t quantityExceedsCredit = (userCredit / productPrice) + 5;
    printf("   Tentando comprar %d unidades (custo total: %d)\n", 
           quantityExceedsCredit, quantityExceedsCredit * productPrice);
    
    bool canBuyProduct5 = false;
    DuckMarketPlace__preBuyProduct(userId2, productId1, quantityExceedsCredit, &canBuyProduct5);
    
    if (canBuyProduct5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(userId2, productId1, quantityExceedsCredit);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - crédito insuficiente)\n");
    }
    
    // Teste 6: tentar comprar produto inexistente (deve falhar)
    printf("\n6. Tentando comprar produto inexistente (ID 55)\n");
    
    DuckMarketPlace__IDPRODUTO inexistentProductId5 = 55;
    int32_t quantityToBuy6 = 2;
    bool canBuyProduct6 = false;
    DuckMarketPlace__preBuyProduct(userId2, inexistentProductId5, quantityToBuy6, &canBuyProduct6);
    
    if (canBuyProduct6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(userId2, inexistentProductId5, quantityToBuy6);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(userId2);
        print_product_info(inexistentProductId5);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não existe)\n");
    }
    
    // Teste 7: tentar comprar produto removido (deve falhar)
    printf("\n7. Tentando comprar produto %d que foi removido (deve falhar)\n", productId2);
    
    int32_t quantityToBuy7 = 1;
    bool canBuyProduct7 = false;
    DuckMarketPlace__preBuyProduct(userId1, productId2, quantityToBuy7, &canBuyProduct7);
    
    if (canBuyProduct7) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(userId1, productId2, quantityToBuy7);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(userId1);
        print_product_info(productId2);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto removido)\n");
    }
    
    // Teste 8: usuário inexistente tentando comprar (deve falhar)
    printf("\n8. Usuário inexistente (ID 44) tentando comprar produto\n");
    
    DuckMarketPlace__IDUSUARIO inexistentUserId3 = 44;
    int32_t quantityToBuy8 = 1;
    bool canBuyProduct8 = false;
    DuckMarketPlace__preBuyProduct(inexistentUserId3, productId1, quantityToBuy8, &canBuyProduct8);
    
    if (canBuyProduct8) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(inexistentUserId3, productId1, quantityToBuy8);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(inexistentUserId3);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário não existe)\n");
    }
    
    // Teste 9: tentar comprar usando IDs dummy (deve falhar)
    printf("\n9. Tentando comprar usando IDs dummy (deve falhar)\n");
    
    DuckMarketPlace__IDUSUARIO dummyUserId = DuckMarketPlace__userIdDummy;
    DuckMarketPlace__IDPRODUTO dummyProductId5 = DuckMarketPlace__productIdDummy;
    int32_t quantityToBuy9 = 1;
    
    bool canBuyProduct9 = false;
    DuckMarketPlace__preBuyProduct(dummyUserId, dummyProductId5, quantityToBuy9, &canBuyProduct9);
    
    if (canBuyProduct9) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(dummyUserId, dummyProductId5, quantityToBuy9);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(dummyUserId);
        print_product_info(dummyProductId5);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - IDs dummy)\n");
    }
    
    // Teste 10: vendedor tentando comprar próprio produto (deve falhar)
    printf("\n10. Vendedor (usuário %d) tentando comprar próprio produto %d (deve falhar)\n", userId1, productId1);
    
    int32_t quantityToBuy10 = 2;
    bool canBuyProduct10 = false;
    DuckMarketPlace__preBuyProduct(userId1, productId1, quantityToBuy10, &canBuyProduct10);
    
    if (canBuyProduct10) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProduct(userId1, productId1, quantityToBuy10);
        printf("   Produto comprado com sucesso!\n");
        print_user_info(userId1);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - vendedor não pode comprar próprio produto)\n");
    }
    
    // Testa a operação returnProduct
    printf("\n=== Testando operação returnProduct ===\n");
    
    // Teste 1: devolver produto comprado anteriormente (deve funcionar)
    printf("\n1. Tentando devolver 1 unidade do produto %d comprado pelo usuário %d\n", productId1, userId2);
    
    printf("   Estado antes da devolução:\n");
    print_user_info(userId2);
    print_product_info(productId1);
    
    int32_t priceAtPurchase1 = 75; // Preço quando o produto foi comprado
    int32_t quantityToReturn1 = 1;
    bool canReturnProduct1 = false;
    DuckMarketPlace__preReturnProduct(userId2, productId1, priceAtPurchase1, quantityToReturn1, &canReturnProduct1);
    
    if (canReturnProduct1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__returnProduct(userId2, productId1, priceAtPurchase1, quantityToReturn1);
        printf("   Produto devolvido com sucesso!\n");
        
        printf("   Estado após a devolução:\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: tentar devolver mais do que foi comprado (deve falhar)
    printf("\n2. Tentando devolver mais unidades do que foi comprado\n");
    
    int32_t priceAtPurchase2 = 75;
    int32_t excessiveReturnQuantity = 10; // Mais do que restou da compra original
    bool canReturnProduct2 = false;
    DuckMarketPlace__preReturnProduct(userId2, productId1, priceAtPurchase2, excessiveReturnQuantity, &canReturnProduct2);
    
    if (canReturnProduct2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__returnProduct(userId2, productId1, priceAtPurchase2, excessiveReturnQuantity);
        printf("   Produto devolvido com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade maior que compra)\n");
    }
    
    // Teste 3: tentar devolver com preço incorreto (deve falhar)
    printf("\n3. Tentando devolver com preço incorreto\n");
    
    int32_t wrongPrice = 50; // Preço diferente do que foi pago na compra
    int32_t quantityToReturn3 = 1;
    bool canReturnProduct3 = false;
    DuckMarketPlace__preReturnProduct(userId2, productId1, wrongPrice, quantityToReturn3, &canReturnProduct3);
    
    if (canReturnProduct3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__returnProduct(userId2, productId1, wrongPrice, quantityToReturn3);
        printf("   Produto devolvido com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - preço incorreto)\n");
    }
    
    // Teste 4: tentar devolver quantidade zero (deve falhar)
    printf("\n4. Tentando devolver 0 unidades (deve falhar)\n");
    
    int32_t priceAtPurchase4 = 75;
    int32_t zeroQuantityReturn = 0;
    bool canReturnProduct4 = false;
    DuckMarketPlace__preReturnProduct(userId2, productId1, priceAtPurchase4, zeroQuantityReturn, &canReturnProduct4);
    
    if (canReturnProduct4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__returnProduct(userId2, productId1, priceAtPurchase4, zeroQuantityReturn);
        printf("   Produto devolvido com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade zero)\n");
    }
    
    // Teste 5: tentar devolver quantidade negativa (deve falhar)
    printf("\n5. Tentando devolver -1 unidades (deve falhar)\n");
    
    int32_t priceAtPurchase5 = 75;
    int32_t negativeReturnQuantity = -1;
    bool canReturnProduct5 = false;
    DuckMarketPlace__preReturnProduct(userId2, productId1, priceAtPurchase5, negativeReturnQuantity, &canReturnProduct5);
    
    if (canReturnProduct5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__returnProduct(userId2, productId1, priceAtPurchase5, negativeReturnQuantity);
        printf("   Produto devolvido com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade negativa)\n");
    }
    
    // Teste 6: usuário sem compras tentando devolver (deve falhar)
    printf("\n6. Usuário %d (sem compras) tentando devolver produto\n", userId1);
    
    int32_t priceAtPurchase6 = 75;
    int32_t quantityToReturn6 = 1;
    bool canReturnProduct6 = false;
    DuckMarketPlace__preReturnProduct(userId1, productId1, priceAtPurchase6, quantityToReturn6, &canReturnProduct6);
    
    if (canReturnProduct6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__returnProduct(userId1, productId1, priceAtPurchase6, quantityToReturn6);
        printf("   Produto devolvido com sucesso!\n");
        print_user_info(userId1);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário não comprou este produto)\n");
    }
    
    // Teste 7: tentar devolver produto inexistente (deve falhar)
    printf("\n7. Tentando devolver produto inexistente (ID 33)\n");
    
    DuckMarketPlace__IDPRODUTO inexistentProductId6 = 33;
    int32_t priceAtPurchase7 = 100;
    int32_t quantityToReturn7 = 1;
    bool canReturnProduct7 = false;
    DuckMarketPlace__preReturnProduct(userId2, inexistentProductId6, priceAtPurchase7, quantityToReturn7, &canReturnProduct7);
    
    if (canReturnProduct7) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__returnProduct(userId2, inexistentProductId6, priceAtPurchase7, quantityToReturn7);
        printf("   Produto devolvido com sucesso!\n");
        print_user_info(userId2);
        print_product_info(inexistentProductId6);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não existe na compra)\n");
    }
    
    // Teste 8: usuário inexistente tentando devolver (deve falhar)
    printf("\n8. Usuário inexistente (ID 22) tentando devolver produto\n");
    
    DuckMarketPlace__IDUSUARIO inexistentUserId4 = 22;
    int32_t priceAtPurchase8 = 75;
    int32_t quantityToReturn8 = 1;
    bool canReturnProduct8 = false;
    DuckMarketPlace__preReturnProduct(inexistentUserId4, productId1, priceAtPurchase8, quantityToReturn8, &canReturnProduct8);
    
    if (canReturnProduct8) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__returnProduct(inexistentUserId4, productId1, priceAtPurchase8, quantityToReturn8);
        printf("   Produto devolvido com sucesso!\n");
        print_user_info(inexistentUserId4);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário inexistente)\n");
    }
    
    // Testa a operação addProductToCart
    printf("\n=== Testando operação addProductToCart ===\n");
    
    // Teste 1: adicionar produto ao carrinho (deve funcionar)
    printf("\n1. Tentando adicionar 2 unidades do produto %d ao carrinho do usuário %d\n", productId1, userId2);
    
    printf("   Estado antes de adicionar ao carrinho:\n");
    print_user_info(userId2);
    print_product_info(productId1);
    
    int32_t quantityToAddCart1 = 2;
    bool canAddToCart1 = false;
    DuckMarketPlace__preAddProductToCart(userId2, productId1, quantityToAddCart1, &canAddToCart1);
    
    if (canAddToCart1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(userId2, productId1, quantityToAddCart1);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        
        printf("   Estado após adicionar ao carrinho:\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: adicionar mais do mesmo produto ao carrinho (deve funcionar)
    printf("\n2. Tentando adicionar mais 1 unidade do produto %d ao carrinho do usuário %d\n", productId1, userId2);
    
    int32_t quantityToAddCart2 = 1;
    bool canAddToCart2 = false;
    DuckMarketPlace__preAddProductToCart(userId2, productId1, quantityToAddCart2, &canAddToCart2);
    
    if (canAddToCart2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(userId2, productId1, quantityToAddCart2);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        
        printf("   Estado após adicionar mais ao carrinho:\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 3: tentar adicionar quantidade zero (deve falhar)
    printf("\n3. Tentando adicionar 0 unidades do produto %d ao carrinho (deve falhar)\n", productId1);
    
    int32_t zeroQuantityCart = 0;
    bool canAddToCart3 = false;
    DuckMarketPlace__preAddProductToCart(userId2, productId1, zeroQuantityCart, &canAddToCart3);
    
    if (canAddToCart3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(userId2, productId1, zeroQuantityCart);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade zero)\n");
    }
    
    // Teste 4: tentar adicionar quantidade negativa (deve falhar)
    printf("\n4. Tentando adicionar -3 unidades do produto %d ao carrinho (deve falhar)\n", productId1);
    
    int32_t negativeQuantityCart = -3;
    bool canAddToCart4 = false;
    DuckMarketPlace__preAddProductToCart(userId2, productId1, negativeQuantityCart, &canAddToCart4);
    
    if (canAddToCart4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(userId2, productId1, negativeQuantityCart);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade negativa)\n");
    }
    
    // Teste 5: tentar adicionar mais do que o estoque disponível (deve falhar)
    printf("\n5. Tentando adicionar mais unidades do que o estoque disponível\n");
    
    // Verificar estoque atual
    int32_t currentStockCart;
    DuckMarketPlace__showProductStock(productId1, &currentStockCart);
    printf("   Estoque atual do produto %d: %d\n", productId1, currentStockCart);
    
    int32_t excessiveCartQuantity = currentStockCart + 5;
    printf("   Tentando adicionar %d unidades ao carrinho\n", excessiveCartQuantity);
    
    bool canAddToCart5 = false;
    DuckMarketPlace__preAddProductToCart(userId2, productId1, excessiveCartQuantity, &canAddToCart5);
    
    if (canAddToCart5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(userId2, productId1, excessiveCartQuantity);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade maior que estoque)\n");
    }
    
    // Teste 6: tentar adicionar produto inexistente (deve falhar)
    printf("\n6. Tentando adicionar produto inexistente (ID 44) ao carrinho\n");
    
    DuckMarketPlace__IDPRODUTO inexistentProductCart = 44;
    int32_t quantityToAddCart6 = 1;
    bool canAddToCart6 = false;
    DuckMarketPlace__preAddProductToCart(userId2, inexistentProductCart, quantityToAddCart6, &canAddToCart6);
    
    if (canAddToCart6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(userId2, inexistentProductCart, quantityToAddCart6);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(inexistentProductCart);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não existe)\n");
    }
    
    // Teste 7: usuário inexistente tentando adicionar ao carrinho (deve falhar)
    printf("\n7. Usuário inexistente (ID 33) tentando adicionar produto ao carrinho\n");
    
    DuckMarketPlace__IDUSUARIO inexistentUserCart = 33;
    int32_t quantityToAddCart7 = 1;
    bool canAddToCart7 = false;
    DuckMarketPlace__preAddProductToCart(inexistentUserCart, productId1, quantityToAddCart7, &canAddToCart7);
    
    if (canAddToCart7) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(inexistentUserCart, productId1, quantityToAddCart7);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        print_user_info(inexistentUserCart);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário não existe)\n");
    }
    
    // Teste 8: vendedor tentando adicionar próprio produto ao carrinho (deve falhar)
    printf("\n8. Vendedor (usuário %d) tentando adicionar próprio produto %d ao carrinho (deve falhar)\n", userId1, productId1);
    
    int32_t quantityToAddCart8 = 1;
    bool canAddToCart8 = false;
    DuckMarketPlace__preAddProductToCart(userId1, productId1, quantityToAddCart8, &canAddToCart8);
    
    if (canAddToCart8) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(userId1, productId1, quantityToAddCart8);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        print_user_info(userId1);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - vendedor não pode adicionar próprio produto)\n");
    }
    
    // Teste 9: tentar adicionar usando IDs dummy (deve falhar)
    printf("\n9. Tentando adicionar produto usando IDs dummy (deve falhar)\n");
    
    DuckMarketPlace__IDUSUARIO dummyUserIdCart = DuckMarketPlace__userIdDummy;
    DuckMarketPlace__IDPRODUTO dummyProductIdCart = DuckMarketPlace__productIdDummy;
    int32_t quantityToAddCart9 = 1;
    
    bool canAddToCart9 = false;
    DuckMarketPlace__preAddProductToCart(dummyUserIdCart, dummyProductIdCart, quantityToAddCart9, &canAddToCart9);
    
    if (canAddToCart9) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__addProductToCart(dummyUserIdCart, dummyProductIdCart, quantityToAddCart9);
        printf("   Produto adicionado ao carrinho com sucesso!\n");
        print_user_info(dummyUserIdCart);
        print_product_info(dummyProductIdCart);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - IDs dummy)\n");
    }
    
    // Testa a operação removeProductFromCart
    printf("\n=== Testando operação removeProductFromCart ===\n");
    
    // Teste 1: remover parte dos produtos do carrinho (deve funcionar)
    printf("\n1. Tentando remover 1 unidade do produto %d do carrinho do usuário %d\n", productId1, userId2);
    
    printf("   Estado antes de remover do carrinho:\n");
    print_user_info(userId2);
    print_product_info(productId1);
    
    int32_t priceInCart1 = 75; // Preço do produto no carrinho
    int32_t quantityToRemove1 = 1;
    bool canRemoveFromCart1 = false;
    DuckMarketPlace__preRemoveProductFromCart(userId2, productId1, priceInCart1, quantityToRemove1, &canRemoveFromCart1);
    
    if (canRemoveFromCart1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(userId2, productId1, priceInCart1, quantityToRemove1);
        printf("   Produto removido do carrinho com sucesso!\n");
        
        printf("   Estado após remover do carrinho:\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: remover o restante dos produtos do carrinho (deve funcionar)
    printf("\n2. Tentando remover as 2 unidades restantes do produto %d do carrinho do usuário %d\n", productId1, userId2);
    
    int32_t priceInCart2 = 75;
    int32_t quantityToRemove2 = 2;
    bool canRemoveFromCart2 = false;
    DuckMarketPlace__preRemoveProductFromCart(userId2, productId1, priceInCart2, quantityToRemove2, &canRemoveFromCart2);
    
    if (canRemoveFromCart2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(userId2, productId1, priceInCart2, quantityToRemove2);
        printf("   Produto removido do carrinho com sucesso!\n");
        
        printf("   Estado após remover resto do carrinho:\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 3: tentar remover de carrinho vazio (deve falhar)
    printf("\n3. Tentando remover produto de carrinho vazio (deve falhar)\n");
    
    int32_t priceInCart3 = 75;
    int32_t quantityToRemove3 = 1;
    bool canRemoveFromCart3 = false;
    DuckMarketPlace__preRemoveProductFromCart(userId2, productId1, priceInCart3, quantityToRemove3, &canRemoveFromCart3);
    
    if (canRemoveFromCart3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(userId2, productId1, priceInCart3, quantityToRemove3);
        printf("   Produto removido do carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - carrinho vazio)\n");
    }
    
    // Adicionar novamente ao carrinho para próximos testes
    printf("\n   Adicionando 2 unidades novamente ao carrinho para próximos testes...\n");
    DuckMarketPlace__addProductToCart(userId2, productId1, 2);
    print_user_info(userId2);
    
    // Teste 4: tentar remover quantidade zero (deve falhar)
    printf("\n4. Tentando remover 0 unidades do carrinho (deve falhar)\n");
    
    int32_t priceInCart4 = 75;
    int32_t zeroQuantityRemove = 0;
    bool canRemoveFromCart4 = false;
    DuckMarketPlace__preRemoveProductFromCart(userId2, productId1, priceInCart4, zeroQuantityRemove, &canRemoveFromCart4);
    
    if (canRemoveFromCart4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(userId2, productId1, priceInCart4, zeroQuantityRemove);
        printf("   Produto removido do carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade zero)\n");
    }
    
    // Teste 5: tentar remover quantidade negativa (deve falhar)
    printf("\n5. Tentando remover -2 unidades do carrinho (deve falhar)\n");
    
    int32_t priceInCart5 = 75;
    int32_t negativeQuantityRemove = -2;
    bool canRemoveFromCart5 = false;
    DuckMarketPlace__preRemoveProductFromCart(userId2, productId1, priceInCart5, negativeQuantityRemove, &canRemoveFromCart5);
    
    if (canRemoveFromCart5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(userId2, productId1, priceInCart5, negativeQuantityRemove);
        printf("   Produto removido do carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade negativa)\n");
    }
    
    // Teste 6: tentar remover mais do que está no carrinho (deve falhar)
    printf("\n6. Tentando remover mais unidades do que está no carrinho\n");
    
    int32_t priceInCart6 = 75;
    int32_t excessiveRemoveQuantity = 5; // Mais do que as 2 no carrinho
    bool canRemoveFromCart6 = false;
    DuckMarketPlace__preRemoveProductFromCart(userId2, productId1, priceInCart6, excessiveRemoveQuantity, &canRemoveFromCart6);
    
    if (canRemoveFromCart6) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(userId2, productId1, priceInCart6, excessiveRemoveQuantity);
        printf("   Produto removido do carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - quantidade maior que no carrinho)\n");
    }
    
    // Teste 7: tentar remover com preço incorreto (deve falhar)
    printf("\n7. Tentando remover com preço incorreto (50 em vez de 75)\n");
    
    int32_t wrongPriceRemove = 50;
    int32_t quantityToRemove7 = 1;
    bool canRemoveFromCart7 = false;
    DuckMarketPlace__preRemoveProductFromCart(userId2, productId1, wrongPriceRemove, quantityToRemove7, &canRemoveFromCart7);
    
    if (canRemoveFromCart7) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(userId2, productId1, wrongPriceRemove, quantityToRemove7);
        printf("   Produto removido do carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - preço incorreto)\n");
    }
    
    // Teste 8: usuário inexistente tentando remover do carrinho (deve falhar)
    printf("\n8. Usuário inexistente (ID 55) tentando remover produto do carrinho\n");
    
    DuckMarketPlace__IDUSUARIO inexistentUserRemove = 55;
    int32_t priceInCart8 = 75;
    int32_t quantityToRemove8 = 1;
    bool canRemoveFromCart8 = false;
    DuckMarketPlace__preRemoveProductFromCart(inexistentUserRemove, productId1, priceInCart8, quantityToRemove8, &canRemoveFromCart8);
    
    if (canRemoveFromCart8) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(inexistentUserRemove, productId1, priceInCart8, quantityToRemove8);
        printf("   Produto removido do carrinho com sucesso!\n");
        print_user_info(inexistentUserRemove);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário inexistente)\n");
    }
    
    // Teste 9: tentar remover produto inexistente do carrinho (deve falhar)
    printf("\n9. Tentando remover produto inexistente (ID 66) do carrinho\n");
    
    DuckMarketPlace__IDPRODUTO inexistentProductRemove = 66;
    int32_t priceInCart9 = 100;
    int32_t quantityToRemove9 = 1;
    bool canRemoveFromCart9 = false;
    DuckMarketPlace__preRemoveProductFromCart(userId2, inexistentProductRemove, priceInCart9, quantityToRemove9, &canRemoveFromCart9);
    
    if (canRemoveFromCart9) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__removeProductFromCart(userId2, inexistentProductRemove, priceInCart9, quantityToRemove9);
        printf("   Produto removido do carrinho com sucesso!\n");
        print_user_info(userId2);
        print_product_info(inexistentProductRemove);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - produto não está no carrinho)\n");
    }
    
    // Testa a operação buyProductsFromCart
    printf("\n=== Testando operação buyProductsFromCart ===\n");
    
    // Primeiro, vamos limpar o carrinho e adicionar produtos novamente para ter um estado conhecido
    printf("\n   Preparando carrinho para testes...\n");
    // Remover o que sobrou do carrinho (1 unidade restante)
    DuckMarketPlace__removeProductFromCart(userId2, productId1, 75, 1);
    
    // Adicionar produtos ao carrinho para testar a compra
    DuckMarketPlace__addProductToCart(userId2, productId1, 3); // 3 × 75 = 225
    printf("   Carrinho preparado com 3 unidades do produto %d\n", productId1);
    print_user_info(userId2);
    
    // Teste 1: comprar produtos do carrinho com crédito suficiente (deve funcionar)
    printf("\n1. Tentando comprar todos os produtos do carrinho do usuário %d\n", userId2);
    
    printf("   Estado antes da compra do carrinho:\n");
    print_user_info(userId2);
    print_product_info(productId1);
    
    bool canBuyFromCart1 = false;
    DuckMarketPlace__preBuyProductsFromCart(userId2, &canBuyFromCart1);
    
    if (canBuyFromCart1) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProductsFromCart(userId2);
        printf("   Compra do carrinho realizada com sucesso!\n");
        
        printf("   Estado após a compra do carrinho:\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 2: tentar comprar de carrinho vazio (deve falhar)
    printf("\n2. Tentando comprar de carrinho vazio (deve falhar)\n");
    
    bool canBuyFromCart2 = false;
    DuckMarketPlace__preBuyProductsFromCart(userId2, &canBuyFromCart2);
    
    if (canBuyFromCart2) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProductsFromCart(userId2);
        printf("   Compra do carrinho realizada com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - carrinho vazio)\n");
    }
    
    // Teste 3: tentar comprar com crédito insuficiente (deve falhar)
    printf("\n3. Tentando comprar do carrinho sem crédito suficiente\n");
    
    // Adicionar produtos caros ao carrinho que excedem o crédito
    DuckMarketPlace__addProductToCart(userId2, productId1, 6); // 6 × 75 = 450 (usuário tem apenas ~200 crédito)
    printf("   Adicionado 6 unidades ao carrinho (custo: 450)\n");
    
    printf("   Estado antes da tentativa de compra:\n");
    print_user_info(userId2);
    
    bool canBuyFromCart3 = false;
    DuckMarketPlace__preBuyProductsFromCart(userId2, &canBuyFromCart3);
    
    if (canBuyFromCart3) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProductsFromCart(userId2);
        printf("   Compra do carrinho realizada com sucesso!\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - crédito insuficiente)\n");
    }
    
    // Limpar o carrinho para próximo teste
    DuckMarketPlace__removeProductFromCart(userId2, productId1, 75, 6);
    
    // Teste 4: usuário inexistente tentando comprar do carrinho (deve falhar)
    printf("\n4. Usuário inexistente (ID 77) tentando comprar do carrinho\n");
    
    DuckMarketPlace__IDUSUARIO inexistentUserBuy = 77;
    bool canBuyFromCart4 = false;
    DuckMarketPlace__preBuyProductsFromCart(inexistentUserBuy, &canBuyFromCart4);
    
    if (canBuyFromCart4) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProductsFromCart(inexistentUserBuy);
        printf("   Compra do carrinho realizada com sucesso!\n");
        print_user_info(inexistentUserBuy);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário inexistente)\n");
    }
    
    // Teste 5: compra bem-sucedida com múltiplos produtos no carrinho
    printf("\n5. Testando compra com carrinho contendo quantidade moderada\n");
    
    // Adicionar quantidade que o usuário pode pagar
    DuckMarketPlace__addProductToCart(userId2, productId1, 2); // 2 × 75 = 150
    printf("   Adicionado 2 unidades ao carrinho (custo: 150)\n");
    
    printf("   Estado antes da compra final:\n");
    print_user_info(userId2);
    print_product_info(productId1);
    
    bool canBuyFromCart5 = false;
    DuckMarketPlace__preBuyProductsFromCart(userId2, &canBuyFromCart5);
    
    if (canBuyFromCart5) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProductsFromCart(userId2);
        printf("   Compra final do carrinho realizada com sucesso!\n");
        
        printf("   Estado após a compra final:\n");
        print_user_info(userId2);
        print_product_info(productId1);
    } else {
        printf("   ERRO: Pré-condições não atendidas!\n");
    }
    
    // Teste 6: verificar se o vendedor recebeu o pagamento
    printf("\n6. Verificando se o vendedor (usuário %d) recebeu os pagamentos\n", userId1);
    print_user_info(userId1);
    
    // Teste 7: tentar usar ID dummy (deve falhar)
    printf("\n7. Tentando comprar do carrinho usando ID dummy (deve falhar)\n");
    
    DuckMarketPlace__IDUSUARIO dummyUserBuy = DuckMarketPlace__userIdDummy;
    bool canBuyFromCart7 = false;
    DuckMarketPlace__preBuyProductsFromCart(dummyUserBuy, &canBuyFromCart7);
    
    if (canBuyFromCart7) {
        printf("   Pré-condições verificadas: OK\n");
        DuckMarketPlace__buyProductsFromCart(dummyUserBuy);
        printf("   Compra do carrinho realizada com sucesso!\n");
        print_user_info(dummyUserBuy);
    } else {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID dummy)\n");
    }
    
    // Testa a operação withdrawInactiveCredit
    printf("\n=== Testando operação withdrawInactiveCredit ===\n");
    
    // Esta operação permite retirar crédito de usuários inativos
    // Usuários inativos são criados quando um usuário é removido mas ainda tem crédito
    
    printf("Estado inicial dos usuários ativos:\n");
    print_user_info(userId1);
    print_user_info(userId2);
    
    
    printf("\n   Criando cenário de usuário inativo...\n");
    
    // Vamos criar um terceiro usuário para torná-lo inativo
    printf("\n   Adicionando usuário 3 para teste de inativação...\n");
    
    DuckMarketPlace__IDUSUARIO userIdForInactive = 3;
    DuckMarketPlace__NOMEUSUARIO userNameForInactive = 303;
    int initialCreditForInactive = 500;
    
    bool canAddUserForInactive;
    DuckMarketPlace__preAddUser(userIdForInactive, userNameForInactive, initialCreditForInactive, &canAddUserForInactive);
    if (canAddUserForInactive) {
        DuckMarketPlace__addUser(userIdForInactive, userNameForInactive, initialCreditForInactive);
        printf("   Usuário 3 adicionado com sucesso!\n");
        print_user_info(userIdForInactive);
        
        // Agora vamos remover esse usuário para torná-lo inativo
        printf("\n   Removendo usuário 3 para torná-lo inativo...\n");
        
        bool canRemoveUserForInactive;
        DuckMarketPlace__preRemoveUser(userIdForInactive, &canRemoveUserForInactive);
        if (canRemoveUserForInactive) {
            DuckMarketPlace__removeUser(userIdForInactive);
            printf("   Usuário 3 removido com sucesso (agora inativo com crédito)!\n");
            
            // Agora vamos testar a operação withdrawInactiveCredit
            printf("\n=== Testando retirada de crédito inativo ===\n");
            
            // 1. Teste com usuário inativo válido
            printf("\n1. Tentando retirar crédito inativo do usuário %d\n", userIdForInactive);
            
            bool canWithdrawInactive;
            DuckMarketPlace__preWithdrawInactiveCredit(userIdForInactive, &canWithdrawInactive);
            if (canWithdrawInactive) {
                printf("   Pré-condições verificadas: OK\n");
                printf("   Usuário %d tem crédito inativo que pode ser retirado\n", userIdForInactive);
                DuckMarketPlace__withdrawInactiveCredit(userIdForInactive);
                printf("   Crédito inativo retirado com sucesso!\n");
                printf("   O crédito do usuário inativo foi zerado.\n");
                
                // Tentar novamente (deve falhar agora)
                printf("\n   Tentando retirar novamente (deve falhar - crédito já zerado):\n");
                DuckMarketPlace__preWithdrawInactiveCredit(userIdForInactive, &canWithdrawInactive);
                if (!canWithdrawInactive) {
                    printf("   ERRO: Pré-condições não atendidas! (Esperado - crédito inativo zerado)\n");
                } else {
                    printf("   Erro inesperado: ainda permite retirada\n");
                }
            } else {
                printf("   ERRO: Pré-condições não atendidas! (Usuário pode não estar inativo ou não ter crédito)\n");
            }
        } else {
            printf("   ERRO: Não foi possível remover o usuário 3\n");
        }
    } else {
        printf("   ERRO: Não foi possível adicionar o usuário 3\n");
    }
    
    // 2. Teste com usuário ativo (deve falhar)
    printf("\n2. Tentando retirar crédito inativo de usuário ativo (%d)\n", userId1);
    bool canWithdrawActive;
    DuckMarketPlace__preWithdrawInactiveCredit(userId1, &canWithdrawActive);
    if (!canWithdrawActive) {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário está ativo)\n");
    } else {
        printf("   Erro inesperado: pré-condições aceitas para usuário ativo\n");
    }
    
    // 3. Teste com usuário inexistente
    printf("\n3. Usuário inexistente (ID 99) tentando retirar crédito inativo\n");
    bool canWithdrawNonExistent;
    DuckMarketPlace__preWithdrawInactiveCredit(99, &canWithdrawNonExistent);
    if (!canWithdrawNonExistent) {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - usuário inexistente)\n");
    } else {
        printf("   Erro inesperado: pré-condições aceitas para usuário inexistente\n");
    }
    
    // 4. Teste com ID dummy
    printf("\n4. Tentando retirar crédito inativo usando ID dummy (deve falhar)\n");
    bool canWithdrawDummy;
    DuckMarketPlace__preWithdrawInactiveCredit(DuckMarketPlace__userIdDummy, &canWithdrawDummy);
    if (!canWithdrawDummy) {
        printf("   ERRO: Pré-condições não atendidas! (Esperado - ID dummy)\n");
    } else {
        printf("   Erro inesperado: pré-condições aceitas para ID dummy\n");
    }
    
    printf("\n   Estado final dos usuários ativos:\n");
    print_user_info(userId1);
    print_user_info(userId2);

    printf("\n=== Fim dos testes ===\n");
    printf("Programa executado com sucesso!\n");
    
    return 0;
}
