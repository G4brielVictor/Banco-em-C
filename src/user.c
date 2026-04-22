#include "user.h"
#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include "banco.h"

void menu_user(Conta *contas, int *totalAccounts, int *num){

    int user;

    printf("Ola! Precisamos de algumas informacoes para darmos continuidade!\n\n");
    do{
        printf("Novo usuario? 1 - Sim | 2 - Nao\n");
        while(scanf("%d", &user) != 1){
            printf("Opcao invalida, digite novamente: ");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');

        if(user != 1 && user != 2) printf("Opcao invalida, digite novamente\n");
    }while(user != 1 && user != 2);

    if(user == 1) {
        register_menu(contas, totalAccounts, num);
    }
    else {
        login_menu(contas, totalAccounts);
    }  
}

void register_menu(Conta *contas, int *allAccounts, int *num){
    system("cls");
    printf("============= CADASTRO NOVA CONTA ===============\n");

    int validar = create_account(contas, allAccounts, num);
    if(validar == 1){
        printf("\n\tCADASTRO REALIZADO!!\n");
        login_menu(contas, allAccounts);
    }
    else{
        printf("\n\tCADASTRO NAO REALIZADO.\n");
    }
}

void login_menu(Conta *contas, int *allAccounts){
    system("cls");
    printf("================ LOGIN CONTA =================\n");

    int index = login_account(contas, allAccounts);

    if(index == -1){
        printf("Falha no login\n");
        return;
    }
    Conta *user = &contas[index];
    int op;
    
    do {
        system("cls");

        printf("%s, %s. Bem vindo!\n", bank_time(), user->fullName);

        printf("Escolha uma das opcoes abaixo: ");
        printf("==========================================\n");
        printf("| 1 - Deposito            |\n");
        printf("| 2 - Saque               |\n");
        printf("| 3 - Transferencia       |\n");
        printf("| 4 - Mostrar dados conta |\n");
        printf("| 5 - Remover conta       |\n");
        printf("| 0 - Sair                |\n");

        while(scanf("%d", &op) != 1){
            printf("Escolha invalida, tente novamente.\n");
            while(getchar() != '\n');
        }

        while(getchar() != '\n');

        while(op != 0){
            switch(op) {
                case 1: 
                    menu_deposit(user);
                    break;
                case 2: 
                    menu_withdrawal(user);
                    break;
                case 3:

            }
        }

        
    }while(op != 0);
    
}