#include <stdbool.h>

#ifndef BANCO_H
#define BANCO_H

//Definitions of variables.
#define MAX_ACCOUNT 100
#define MAX_NAME 50
#define MAX_CPF 15
#define MAX_PASSWD 20

//Struct of the account
typedef enum {
    ADMIN,
    USER
} TypeUser;

typedef struct {
    int numero; 
    char fullName[MAX_ACCOUNT];
    char cpf[MAX_CPF];
    char passwd[MAX_PASSWD];
    float saldo;
    int ativo;
    TypeUser type;
} Conta;

//User logon/login
int create_account(Conta *conta, int *totalAccounts, int *num);
int login_account(Conta *conta, int *totalAccounts);

//Validations
int validate_name(char *name);
int validate_cpf(char *cpf);
int validate_passwd(char *pass);

//Search user
int find_account_by_cpf(char *search, Conta *contas, int *totalAccounts);

//User functions
void menu_deposit(Conta *user);
int deposit(Conta *user, float value);

void menu_withdrawal(Conta *user);
int withdrawal(Conta *user, float value);

void menu_transfer(Conta *user, Conta *accounts, int *totalAccounts);
int transfer(Conta *sender, Conta *accounts, char *cpf, float value, int *totalAccounts);

void menu_date_account(Conta *user);

void menu_disable_account(Conta *user);
int disable_account(Conta *user);  

//admin user
//Listar contas X, buscar contas X, Reativar conta X , Remover contas, ajustar saldo, estatisticas, resetar senha;
void list_accounts(Conta *acc, int *allAccounts);

int search_account(Conta *acc, int *allAccounts);
int search_id(Conta *acc, int *allAccounts, int idAcc);
int search_Cpf(Conta *acc, int *allAccounts, const char *cpfAcc);

void reactivate_account(Conta *acc, int *allAccounts);

void remove_account(Conta *acc, int *allAccounts);

void update_balance(Conta *acc, int *allAccounts);

//others functions
const char bank_time();

#endif