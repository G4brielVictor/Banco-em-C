#include <stdio.h>
#include "banco.h"
#include <string.h>
#include <ctype.h>

//############################ Users #############################################//
int create_account(Conta *conta, int *totalAccounts, int *num){
    if(*totalAccounts >= MAX_ACCOUNT){
        printf("Nao é possivel criar sua conta no momento, tente mais tarde\n");
        return 0;
    } 

    Conta *c = &conta[*totalAccounts];

    printf("=============================================\n");
    printf("|            CADASTRO NOVA CONTA            |\n");
    printf("=============================================\n");
    
    printf("\tOla novo usuario! Para darmos continuidade preencha algumas informacoes.\n\n");
    int test_name;
    do{
        printf("Digite o seu nome completo: ");
        fgets(c->fullName, MAX_NAME, stdin);
        c->fullName[strcspn(c->fullName, "\n")] = '\0';
        
        test_name = validate_name(c->fullName);
        if(test_name != 1){
            printf("Nome invalido, tente novamente\n");
        }
    }while(test_name != 1);

    
    int test_CPF;
    do{
        printf("Digite o seu CPF: ");
        while(getchar() != '\n');
        fgets(c->cpf, MAX_CPF, stdin);
        c->cpf[strcspn(c->cpf, "\n")] = '\0';

        test_CPF = validate_cpf(c->cpf);
        if(test_CPF != 1){
            printf("CPF invalido, tente novamente\n");
            
        }

    }while(test_CPF != 1);

    int test_passwd;
    do{
        printf("Digite a nova senha desejada: ");
        fgets(c->passwd, MAX_PASSWD, stdin);
        c->passwd[strcspn(c->passwd, "\n")] = '\0';

        test_passwd = validate_passwd(c->passwd);
        if(test_passwd != 1){
            printf("Senha invalida, tente novamente\n");
        }
    }while(test_passwd != 1);

    c->numero = *num;
    (*num)++;
    
    c->saldo = 0.0;   
    c->ativo = 1; 

    (*totalAccounts)++;
    return 1;
}

int login_account(Conta *conta, int *totalAccounts){
    Conta *c = &conta[*totalAccounts];

    char search_CPF[MAX_CPF];
    char search_passwd[MAX_PASSWD]; 

    printf("=============================================\n");
    printf("|                LOGIN CONTA                |\n");
    printf("=============================================\n");

    int test_CPF;
    do {
        printf("Digite o CPF do titular: ");
        fgets(search_CPF, MAX_CPF, stdin);
        search_CPF[strcspn(search_CPF, "\n")] = '\0';

        test_CPF = validate_cpf(search_CPF);
        if(test_CPF != 1){
            printf("CPF invalido, tente novamente\n");
        }
    }while(test_CPF != 1);

    int test_passwd;
    do {
        printf("Digite a senha do titular: ");
        fgets(search_passwd, MAX_PASSWD, stdin);
        search_passwd[strcspn(search_passwd, "\n")] = '\0';

    }

}

int find_account_by_cpf(Conta *contas, int *totalAccounts, char *search){
    
}

int validate_name(char *name){
    //Verifica se a String n esta vazia. O strlen conta qnts caracteres existem, se 0 nao tem nenhum.
    if(name == NULL || strlen(name) == 0){
        return 0;
    }

    if(name[0] == ' ') return 0;

    for(int i = 0; name[i] != '\0'; i++){
        if(!isalpha(name[i]) && !isspace(name[i])){
            return 0;
        }
    }   

    return 1;
}

int validate_cpf(char *cpf){
    int tam = strlen(cpf);
    //Verifica se a String n esta vazia. O strlen conta qnts caracteres existem, se 0 nao tem nenhum.
    if(cpf == NULL || tam == 0){
        return 0;
    }

    if(tam != 14){
        return 0;
    }

    if(cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-'){
        printf("Formato invalido. EX 999.999.999-99\n");
        return 0;
    }

    for(int i = 0; cpf[i] != '\0'; i++){
        if(i == 3 || i == 7 || i == 11) continue;

        if(!isdigit(cpf[i])){
            return 0;
        }
    }
    return 1;
}

int validate_passwd(char *pass){
    
    if(pass == NULL || strlen(pass[0]) == '\0'){
        return 0;
    }

    int lenght = strlen(pass);

    if(lenght < 8){
        printf("Senha minima: 8 digitos!\n");
        return 0;
    }

    int hasUpper = 0;
    int hasNumber = 0;
    int hasSymbol = 0;

    for(int i = 0; pass[i] != '\0'; i++){
        if(isdigit(pass[i])){
            hasNumber = 1;
        }

        if(isupper(pass[i])){
            hasUpper = 1;   
        }

        if(ispunct(pass[i])){
            hasSymbol = 1;
        }
    }

    if(!hasNumber){
        printf("A senha deve conter no minimo 1 numero\n");
        return 0;
    }

    if(!hasUpper){
        printf("A senha deve conter no minimo 1 caracter maiusculo\n");
        return 0;
    }

    if(!hasSymbol){
        printf("A senha deve conter no minimo 1 simbolo\n");
        return 0;
    }

    return 1;
}

