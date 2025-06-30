#include <stdio.h>
#include <stdbool.h>
#include "DuckMarketPlace.h"

int main(void) {
    // Inicialização da implementação
    DuckMarketPlace__INITIALISATION();

    // Definição dos dados do novo usuário
    DuckMarketPlace__IDUSUARIO uu = 1;
    DuckMarketPlace__NOMEUSUARIO nn = 5;
    int32_t cc = 100;
    bool canAdd = false;

    // Verifica se é possível adicionar o usuário
    DuckMarketPlace__preAddUser(uu, nn, cc, &canAdd);

    if (canAdd) {
        DuckMarketPlace__addUser(uu, nn, cc);
        printf("Usuário %d adicionado com nome %d e crédito %d\n", uu, nn, cc);
    } else {
        printf("Erro: não foi possível adicionar o usuário %d (pré-condição falhou).\n", uu);
    }

    // Verifica se tentar adicionar o mesmo usuário novamente falha
    DuckMarketPlace__preAddUser(uu, nn, cc, &canAdd);

    if (canAdd) {
        printf("Erro: pré-condição permitiu adicionar novamente o usuário %d, mas não deveria.\n", uu);
    }

    // Consulta o nome do usuário
    DuckMarketPlace__NOMEUSUARIO nomeConsulta;
    DuckMarketPlace__showUserName(uu, &nomeConsulta);

    if (nomeConsulta != nn) {
        printf("Erro: nome consultado do usuário %d incorreto. Esperado: %d, Obtido: %d\n", uu, nn, nomeConsulta);
    } else {
        printf("Nome do usuário %d consultado: %d\n", uu, nomeConsulta);
    }

    // Consulta o crédito do usuário
    int32_t creditoConsulta;
    DuckMarketPlace__showUserCredit(uu, &creditoConsulta);

    if (creditoConsulta != cc) {
        printf("Erro: crédito consultado do usuário %d incorreto. Esperado: %d, Obtido: %d\n", uu, cc, creditoConsulta);
    } else {
        printf("Crédito do usuário %d consultado: %d\n", uu, creditoConsulta);
    }

    return 0;
}
