#include "banco.h"

#ifndef USER_H
#define USER_H

//Menu user
int register_menu(Conta *contas, int *allAccounts, int *num);
void login_menu(Conta *user, Conta *contas, int *allAccounts, int position);

#endif