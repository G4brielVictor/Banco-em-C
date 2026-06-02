#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "banco.h"
#include "admin.h"
#include "user.h"

int main(){
    Conta contas[MAX_ACCOUNT];  
    int allAccounts = 0, numAccounts = 0;
        
    initialize_admin(contas, &allAccounts);

    printf("=============================================\n");
    printf("|                    BANK                   |\n");
    printf("=============================================\n");

    int user;

    printf("Ola! Precisamos de algumas informacoes para darmos continuidade!\n\n");
    do{
        printf("Novo usuario? 1 - Sim | 2 - Nao\n");
        while(scanf(" %d", &user) != 1){
            printf("Opcao invalida, digite novamente: ");
            while(getchar() != '\n');
        }

        if(user != 1 && user != 2) printf("Opcao invalida, digite novamente\n");
    }while(user != 1 && user != 2);
    system("cls");

    while(getchar() != '\n');
    if(user == 2){
        int index = login_account(contas, &allAccounts);

        if(index < 0){
            return 0;
        }

        Conta *userC = &contas[index];

        if(userC->type == ADMIN){  
            admin_user(contas, &allAccounts, index);
        }
        else {
            login_menu(userC, contas, &allAccounts, index);
        }
    }   
    else {
        register_menu(contas, &allAccounts, &numAccounts);
    }


    return 0;
}