#include "user.h"
#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include "banco.h"


int register_menu(Conta *contas, int *allAccounts, int *num){
    system("cls");

    int validar = create_account(contas, allAccounts, num);
    if(validar == 1){
        printf("\n\tCADASTRO REALIZADO!!\n");
        return validar;
    }
    else{
        printf("\n\tCADASTRO NAO REALIZADO.\n");
    }
    return 0;
}

void login_menu(Conta *user, Conta *contas, int *allAccounts, int position){
    system("cls");
    printf("================ LOGIN CONTA =================\n");

    if(user == NULL){
        printf("Falha no login\n");
        return;
    }

    if(position < 0){
        printf("Falha no login\n");
        return;
    }

    if(user->ativo == 0){
        printf("Conta inativa\n"); 
        return;
    }

    int op;
    
    do {
        system("cls");

        printf("%s, %s. Bem vindo!\n", bank_time(), user->fullName);

        printf("Escolha uma das opcoes abaixo\n");
        printf("==============================\n");
        printf("| 1 - Deposito            |\n");
        printf("| 2 - Saque               |\n");
        printf("| 3 - Transferencia       |\n");
        printf("| 4 - Mostrar dados conta |\n");
        printf("| 5 - Desabilitar conta   |\n");
        printf("| 0 - Sair                |\n");

        while(scanf("%d", &op) != 1){
            printf("Escolha invalida, tente novamente.\n");
            while(getchar() != '\n');
        }

        while(getchar() != '\n');

        switch(op) {
            case 1: 
                menu_deposit(user);
                break;
            case 2: 
                menu_withdrawal(user);
                break;
            case 3:
                menu_transfer(user, contas, allAccounts);
                break;
            case 4: 
                menu_date_account(user);
                break;
            case 5: 
                menu_disable_account(user);
                break;
            case 0:
                printf("Retornando ao inicio...");
                break;
            default:
                printf("Erro, tente novamente!\n");
        }
    }while(op != 0);
    
}