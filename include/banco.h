#include <stdbool.h>

#ifndef BANCO_H
#define BANCO_H

#define MAX_ACCOUNT 100
#define MAX_NAME 50
#define MAX_CPF 15
#define MAX_PASSWD 20

typedef struct {
    int numero; 
    char fullName[MAX_ACCOUNT];
    char cpf[MAX_CPF];
    char passwd[MAX_PASSWD];
    float saldo;
    int ativo;
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

void menu_transfer(Conta *user);
int transfer(Conta *user, float value);

//others functions
const char bank_time();

#endif