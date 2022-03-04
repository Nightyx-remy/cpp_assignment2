#ifndef CPP_ASSIGNMENT2_MENU_H
#define CPP_ASSIGNMENT2_MENU_H

#include "transaction_list.h"

void print_count_of_transactions(const TransactionList& transactions);

void print_minimum_resource_size(TransactionList& transactions);

void print_sum_of_claims(TransactionList& transactions, int n);

/**
 * Print the option menu, ask the user to select and option and
 * process the user choice
 *
 * @param transactions the list of transactions loaded
 * @return true if the program can continue, false otherwise
 */
bool menu(TransactionList& transactions);

#endif //CPP_ASSIGNMENT2_MENU_H
