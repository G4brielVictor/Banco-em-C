#include <stdio.h>
#include "banco.h"
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

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

    int index = find_account_by_cpf(search_CPF, conta, totalAccounts);

    if(index == -1){
        printf("Conta nao encontrada!\n");
        return -1;
    }

    printf("Conta encontrada!\n| %s |", conta[index].fullName);

    int test_passwd;
    do {
        int tentativas = 3;
        printf("Digite a senha para o acesso: ");
        fgets(search_passwd, MAX_PASSWD, stdin);
        search_passwd[strcspn(search_passwd, "\n")] = '\0';

        test_passwd = strcmp(c[index].passwd, search_passwd);

        if(test_passwd != 0){
            tentativas--;
            
            if(tentativas > 0){
                printf("Senha incorreta, %d tentativas restantes!\n", tentativas);
            }
            else{
                printf("Numero maximo de tentativas alcançado, encerrando tela de login.\n");
                return -1;
            }
        }
    }while(test_passwd != 0);

    printf("\tLOGIN REALIZADO COM SUCESSO!\n");

    return index;

}

int find_account_by_cpf(char *search, Conta *contas, int *totalAccounts){
    if(search[0] == NULL|| search[0] == '\0'){
        return -1;
    }

    for(int i = 0; i < totalAccounts; i++){
        if(strcmp(contas[i].cpf, search) == 0){
            return i;
        }
    } 
    return -1;
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

void menu_deposit(Conta *user) {
    float value;
    
    while(1) {
        printf("Valor do deposito: ");

        if(scanf("%f", &value) != 1){
            printf("Valor invalido, tente novamente\n");
            while(getchar() != '\n');
            continue;
        }

        if(value <= 0){
            printf("Valor deve ser maior que zero\n");
            continue;
        }

        break;
    }

    int result = deposit(user, value);
    if(result == 1){
        printf("Deposito realizado com sucesso!!\n");
    }
    else {
        printf("Erro no deposito.\n");
    }
    
}
int deposit(Conta *user, float value){
    if(user == NULL) return -1;

    if(value <= 0) return -2;
    
    user->saldo += value;
    
    return 1;
}

void menu_withdrawal(Conta *user){
    float value;

    while(1){
        printf("Valor do saque: ");

        if(scanf("%f", &value) != 1){
            printf("Valor invalido, tente novamente\n");
            while(getchar() != '\n');
            continue;
        }

        if(value <= 0){
            printf("Valor deve ser maior que zero\n");
            continue;
        }

        break;
    }

    int result = withdrawal(user, value);

    if(result == 1){
        printf("SAQUE REALIZADO COM SUCESSO\n");
    }
    else if(result == -3){
        printf("Saldo acima do desejado\nValor para retirada: %f\nSeu saldo atual: %f", value, user->saldo);
    }
    else {
        printf("Erro no saque!\n");
    }
}
int withdrawal(Conta *user, float value){
    if(user == NULL) return -1;

    if(value <= 0) return -2;

    if(value > user->saldo) return -3;

    user->saldo -= value;

    return 1;
}

void menu_transfer(Conta *user, int *totalAccounts){
    Conta *u = &user[*totalAccounts];

    char search_CPF[MAX_CPF];
    int test_cpf;
    do{
        printf("Digite o CPF de quem ira receber\nDigite: ");
        fgets(search_CPF, MAX_CPF, stdin);
        search_CPF[strcspn(search_CPF, "\n")] = '\0';

        test_cpf = validate_cpf(search_CPF);
        if(test_cpf != 1){
            printf("CPF invalido, tente novamente\n");
        }
    }while(test_cpf != 1);  

    float value;
    while(1){
        printf("Digite o valor da transferencia\nDigite: ");

        if(scanf("%f", &value) != 1){
            printf("Valor invalido, tente novamente\n");
            while(getchar() != '\n');
            continue;
        }

        if(value <= 0){
            printf("Valor deve ser maior que zero\n");
            continue;
        }

        break;
    }




}
int transfer(Conta *user, float value){
    
}   

//Others functions
const char bank_time(){
    time_t agora = THIStime(NULL);
    struct tm *t = localtime(&agora);

    int hour = t->tm_hour;

    if(hour >= 6 && hour < 12){
        printf("Bom dia!");
    }
    else if(hour >= 12 && hour < 18){
        printf("Boa tarde!");
    }
    else if(hour >= 18 && hour < 24){
        printf("Boa noite!");
    }
    else {
        printf("Boa madrugada!");
    }
}