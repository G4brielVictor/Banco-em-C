#include <stdio.h>
#include "banco.h"
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

//############################ Users #############################################
int create_account(Conta *conta, int *totalAccounts, int *num){
    if(*totalAccounts >= MAX_ACCOUNT){
        printf("Nao é possivel criar sua conta no momento, tente mais tarde\n");
        return 0;
    } 

    Conta *c = &conta[*totalAccounts];

    printf("=============================================\n");
    printf("|            CADASTRO NOVA CONTA            |\n");
    printf("=============================================\n");
    
    printf("Ola novo usuario! Para darmos continuidade preencha algumas informacoes.\n\n");
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
        fgets(c->cpf, MAX_CPF, stdin);
        c->cpf[strcspn(c->cpf, "\n")] = '\0';

        test_CPF = validate_cpf(c->cpf);
        if(test_CPF != 1){
            printf("\nCPF invalido, tente novamente\n");
            
        }

    }while(test_CPF != 1);

    int test_passwd;
    do{
        printf("Digite a nova senha desejada: ");
        fgets(c->passwd, MAX_PASSWD, stdin);
        c->passwd[strcspn(c->passwd, "\n")] = '\0';

        test_passwd = validate_passwd(c->passwd);
        if(test_passwd != 1){
            printf("\nSenha invalida, tente novamente\n");
        }
    }while(test_passwd != 1);

    c->numero = *num;
    (*num)++;
    
    c->saldo = 0.0;   
    c->ativo = 1; 
    c->type = USER;

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
            printf("\nCPF invalido, tente novamente\n");
        }
    }while(test_CPF != 1);
    

    int index = find_account_by_cpf(search_CPF, conta, totalAccounts);

    if(index == -1){
        printf("\nCONTA NAO ENCONTRADA!\n");
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
    if(search == NULL|| search[0] == '\0'){
        return -1;
    }

    for(int i = 0; i < *totalAccounts; i++){
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
    
    if(pass == NULL || strlen(pass) == '\0'){
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

    if(user->ativo != 1) return -3;

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

    if(user->ativo != 1) return 4;

    if(value <= 0) return -2;

    if(value > user->saldo) return -3;

    user->saldo -= value;

    return 1;
}

void menu_transfer(Conta *user, Conta *accounts, int *totalAccounts){
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

    int result = transfer(user, accounts, search_CPF, value, totalAccounts);

    char op;
    printf("%s | Confirma a transferencia?\n", user->fullName);
    printf("S - Sim | N - Nao: ");
    
    while(1){
        if(scanf("%c", &op) != 1){
            printf("Valor invalido, tente novamente.\n");
            continue;
        }
        op = toupper(op);

        if(op == 'N'){
            printf("Retornando ao inicio\n");
            return;
        }
    }

    if(result > 0 || op == 'S'){
        printf("TRANSFERENCIA REALIZADA COM SUCESSO\n");
    }
    else if(result == -2){
        printf("Conta nao encontrada\n");
    }   
    else if(result == -3){
        printf("Erro na transferencia\n");
    }
    else if(result == -4){
        printf("Saldo acima do desejado\nValor para transferencia: %.2f\nSeu saldo atual: %.2f", value, user->saldo);
    }
    else if(result == -5){
        printf("Voce nao pode transferir para sua conta atual.\n");
    }
}
int transfer(Conta *sender, Conta *accounts, char *cpf, float value, int *totalAccounts){
    if(sender == NULL) return -1;

    int index = find_account_by_cpf(cpf, accounts, totalAccounts);
    if(index == -1) return -2;

    Conta *recipient = &accounts[index];

    if(sender->ativo != 1 || recipient->ativo != 1) return -6;

    if(sender == recipient) return -5;

    if(value <= 0) return -3;

    if(value > sender->saldo) return -4;

    sender->saldo -= value;
    recipient->saldo += value;

    return index;
}   

void menu_date_account(Conta *user){  
    printf("============ DADOS DA CONTA ============\n");

    if (user->ativo == 1) {
        printf("Nome: %s | CPF: %s | Numero da conta %d | Conta ativa", user->fullName, user->cpf, user->numero);
    } else {
        printf("Nome: %s | CPF: %s | Numero da conta %d | Conta inativa", user->fullName, user->cpf, user->numero);
    }
}

void menu_disable_account(Conta *user){
    printf("Deseja desabilitar a conta? S - Sim | C - Cancelar\nDigite: ");
    char op;

    while(1){
        if(scanf(" %c", &op) != 1){
            printf("Entrada invalida, tente novamente: ");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');

        op = toupper(op);

        if(op == 'C'){
            printf("Retornando as opcoes...\n");
            return;
        }  

        if(op == 'S') break;

        printf("Entrada invalida, tente novamente");
    }

    char search_passwd[MAX_PASSWD];
    int tentativas = 0;

    while(tentativas < 3){
        printf("Digite a senha para confirmar: ");
        fgets(search_passwd, MAX_PASSWD, stdin);
        search_passwd[strcspn(search_passwd, "\n")] = '\0';

        if(strcmp(user->passwd, search_passwd) == 0){
            printf("Conta desabilitada com sucesso!\n");
            disable_account(user);
            return;
        }

        tentativas ++;

        if(tentativas < 3){
            printf("Senha incorreta. %d tentativas restantes\n", 3 - tentativas);
        }
        else {
            printf("Numero maximo de tentativas alcancado, retornando ao menu\n");
            return;
        }
    }
}  
int disable_account(Conta *user){
    if(user == NULL) return -1; 

    user->ativo = 0;

    return 0;
}


//############################ Admin #############################################
void list_accounts(Conta *acc, int *allAccounts){
    if(*allAccounts == 0){
        printf("Sem contas no sistema\n");
        return;
    }

    printf("====================================================================\n");
    printf("|                       LISTA DE CONTAS                             |\n");
    printf("====================================================================\n");
    printf("| %-2s | %-20s | %-13s | %-20s |\n", "ID", "NOME", "CPF", "ATIVO");
    printf("---------------------------------------------------------------------\n");

    for(int i = 0; i < *allAccounts; i++){    
        if(acc[i].ativo == 1){  
            printf("| %-2d | %-20s | %-13s | Conta ativa |\n\n", 
            acc[i].numero, acc[i].fullName, acc[i].cpf);
            printf("SALDO -> %.2f\n", acc[i].saldo);
        }
        else {
            printf("| %-2d | %-20s | %-13s | Conta Desativada |\n\n", 
            acc[i].numero, acc[i].fullName, acc[i].cpf);
            printf("SALDO -> %.2f\n", acc[i].saldo);
        }
    }
    printf("====================================================================\n\n");
}

int search_account(Conta *acc, int *allAccounts){
    if(*allAccounts == 0){
        printf("Sem contas para encontrar no momento.\n");
        return 0;
    }

    int choice, pos;
    printf("========================== BUSCA CONTA ==============================\n");
    
    printf("1 - Busca por ID | 2 - Busca por CPF | 0 - Sair\nEscolha: ");
    do {
        while(scanf("%d", &choice) != 1){
            printf("Opcao invalida, digite novamente: ");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');       

        if(choice == 1){
            int id;

            printf("Digite o id do cliente: ");
            while(scanf("%d", &id) != 1){
                printf("Opcao invalida, digite novamente: ");
                while(getchar() != '\n');
            }

            pos = search_id(acc, allAccounts, id);
            if(pos > 0){
                printf("| CONTA ENCONTRADA             |\n");
                printf("| %-2s | %-20s | %-13s | %-20s |\n", "ID", "NOME", "CPF", "ATIVO");
                
                if(acc[pos].ativo == 1){
                    printf("| %-2d | %-20s | %-13s | Conta ativa |\n\n", 
                    acc[pos].numero, acc[pos].fullName, acc[pos].cpf);

                    printf("SALDO -> %.2f\n", acc[pos].saldo);
                }

                else {
                    printf("| CONTA ENCONTRADA             |\n");
                    printf("| %-2d | %-20s | %-13s | Conta Desativada |\n\n", 
                    acc[pos].numero, acc[pos].fullName, acc[pos].cpf);

                    printf("SALDO -> %.2f\n", acc[pos].saldo);
                }
                return pos;
            }
            else {
                printf("CONTA NAO ENCONTRADA\n\n");
            }
        }
        else if(choice == 2){
            char cpf[MAX_CPF];
            
            printf("Digite o cpf do cliente: ");
            fgets(cpf, MAX_CPF, stdin);
            cpf[strcspn(cpf, "\n")] = '\0';
            
            pos = search_Cpf(acc, allAccounts, cpf);
            if(pos > 0){
                printf("| CONTA ENCONTRADA             |\n");
                printf("| %-2s | %-20s | %-13s | %-20s |\n", "ID", "NOME", "CPF", "ATIVO");
                
                if(acc[pos].ativo == 1){
                    printf("| %-2d | %-20s | %-13s | Conta ativa |\n\n", 
                    acc[pos].numero, acc[pos].fullName, acc[pos].cpf);

                    printf("SALDO -> %.2f\n", acc[pos].saldo);
                }

                else {
                    printf("| %-2d | %-20s | %-13s | Conta Desativada |\n\n", 
                    acc[pos].numero, acc[pos].fullName, acc[pos].cpf);

                    printf("SALDO -> %.2f\n", acc[pos].saldo);
                }
                return pos;
            }
            else {
                printf("CONTA NAO ENCONTRADA\n\n");
            }
        }
        else {
            printf("Numero incorreto, tente novamente.\n");
        }
    }while(choice != 1 && choice != 2);
    
    return -1;
}
int search_id(Conta *acc, int *allAccounts, const int idAcc){
    if(idAcc <= 0){
        printf("Acesso invalido.\n");
        return -1;
    }
    
    for(int i = 0; i < *allAccounts; i++){
        if(acc[i].numero == idAcc){
            return i;
        }
    }

    return -1;
}
int search_Cpf(Conta *acc, int *allAccounts, const char *cpfAcc){
    if(cpfAcc[0] == '\0'){
        printf("Acesso invalido.\n");
        return -1;
    }
    for(int i = 0; i < *allAccounts; i++){
        if(strcmp(acc[i].cpf, cpfAcc) == 0){
            return i;
        }
    }

    return -1;
}

void reactivate_account(Conta *acc, int *allAccounts){
    char search_pass[MAX_PASSWD];
    printf("========================== REATIVACAO DE CONTA ==============================\n");

    int try = 0;
    while(1) {
        printf("Para reativacao da conta, confirme a senha do admin\nDigite: ");
        fgets(search_pass, MAX_PASSWD, stdin);
        search_pass[strcspn(search_pass, "\n")] = '\0';

        if(strcmp(search_pass, acc->passwd) != 0){
            printf("Senha incorreta, tente novamente.\n");
            try++;
        }
        else {
            printf("Senha correta!\n");
            break;
        }

        if(try >= 3){
            printf("Numero maximo de tentativas alcançadas.\n");
            return;
        }
    } 
    
    acc->ativo = 1;
    printf("Conta ativada com sucesso!!!\n");

    printf("|====================================|\n");
    printf("| %-2d | %-20s | %-13s | Conta ativa |\n\n", 
            acc->numero, acc->fullName, acc->cpf);
    printf("|====================================|\n");

}

void remove_account(Conta *acc, int *allAccounts){
    if(*allAccounts == 0){
        printf("Sem contas para remover no momento\n");
        return;
    }
    
    printf("========================== REMOVER CONTA ==============================\n");

    int pos = search_account(acc, allAccounts);

    if(acc[pos].type == ADMIN){
        printf("Não é possivel remover a conta do administrador!!!!\n");
        return;
    }

    if(pos == -1){
        printf("Erro, retornando ao inicio.\n");
        return;
    }

    int remove;
    while(1){
        printf("Deseja remover a conta? 1 - Sim | 2 - Não\nDigite: ");

        while(scanf("%d", &remove) != 1){
            printf("Invalido, tente novamente\n");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');

        if(remove != 1 && remove != 2){
            printf("Numero invalido, tente novamente.");
            continue;
        }
        break;
    }

    if(remove == 2){
        printf("Retornando ao sistema.\n");
        return;
    }
    
    for(int i = pos; i < *allAccounts; i++){
        acc[i] = acc[i + 1];
    }

    (*allAccounts)--;
    printf("Conta removida com sucesso!\n");
}

void update_balance(Conta *acc, int *allAccounts){
    if(*allAccounts == 0){
        printf("Sem contas para ajustar.\n");
        return;
    }

    printf("========================== AJUSTAR SALDO ==============================\n");



}

void reset_passwd(Conta *acc, int *allAccounts, char *newPass){
    
}
//Others functions
const char bank_time(){ 
    time_t agora = time(NULL);
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