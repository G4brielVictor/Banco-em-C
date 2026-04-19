#include "user.h"
#include <stdio.h>
#include <ctype.h>

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
        login_menu()
    }  
}

void register_menu(Conta *contas, int *allAccounts, int *num){
    int op;
    printf("============= CADASTRO NOVA CONTA ===============\n");

    int validar = create_account(contas, allAccounts, num);
    if(validar == 1){
        printf("\n\tCADASTRO REALIZADO!!\n");
    }
    else{
        printf("\n\tCADASTRO NAO REALIZADO.\n");
    }
}

void login_menu(Conta *contas, int *allAccounts){
    printf("================ LOGIN CONTA =================\n");

    printf("");
    printf("| 1 - Deposito            |\n");
    printf("| 2 - Saque               |\n");
    printf("| 3 - Transferencia       |\n");
    printf("| 4 - Mostrar dados conta |\n");
    printf("| 7 - Remover conta       |\n");
    printf("| 0 - Sair                |\n");

}