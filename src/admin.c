#include "admin.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

void initialize_admin(Conta *conta, int *totalAccounts){
    conta[0].numero = 0;
    strcpy(conta[0].fullName, "Admin");
    strcpy(conta[0].cpf, "000.000.000-00");
    strcpy(conta[0].passwd, "rootAdmin0$");
    conta[0].saldo = 0.0;
    conta[0].ativo = 1;
    conta[0].type = ADMIN;

    *totalAccounts = 1;
}

void admin_user(Conta *contas, int *totalAccounts, const int position){
    printf("================ ADMIN ACCOUNT =================\n");

    if(contas == NULL){
        printf("Falha no login do administrador!\n");
        return;
    }

    if(contas[position].type != ADMIN){
        printf("Falha no login do administrador!\n");
        return;
    }

    int op;

    do{
        printf("Bem vindo - %s", contas[position].fullName);

        printf("Selecione uma das opcoes abaixo\n");
        printf("==============================\n");
        printf("| 1 - Listar contas            |\n");
        printf("| 2 - Buscar conta             |\n");
        printf("| 3 - Ativar/Desativar conta   |\n");
        printf("| 4 - Remover conta            |\n");
        printf("| 5 - Ver saldo de conta       |\n");
        printf("| 0 - Sair                     |\n");
        
        printf("Escolha: "); 
        while(scanf("%d", &op) != 1){
            printf("Escolha invalida, tente novamente.\n");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');

        switch(op){
            case 1:
                list_accounts(contas, totalAccounts); 
                break;
            case 2:
                search_account(contas, totalAccounts);
                break;
            case 3:
                reactivate_account(contas, totalAccounts);
                break;
            case 4:
                remove_account(contas, totalAccounts);
                break;
            case 5:
                update_balance(contas, totalAccounts);
                break;
        }
    } while(op != 0);
}
