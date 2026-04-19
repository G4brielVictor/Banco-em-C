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

//User
int create_account(Conta *conta, int *totalAccounts, int *num);
int login_account(Conta *conta, int *totalAccounts);

int validate_name(char *name);
int validate_cpf(char *cpf);
int validate_passwd(char *pass);




#endif