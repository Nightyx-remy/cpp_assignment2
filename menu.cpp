#include "menu.h"

#include <iostream>

void print_count_of_transactions(const TransactionList& transactions) {
    std::cout << "There are " << transactions.size << " transaction(s)." << std::endl;
}

void print_minimum_resource_size(TransactionList& transactions) {
    std::cout << "The minimum resource size is " << transactions.minimum_resource_size() << "." << std::endl;
}

void print_sum_of_claims(TransactionList& transactions, int n) {
    std::cout << "The sum of claims until " << n << " transactions is " << transactions.sum_of_claims(n) << std::endl;
}

void print_menu() {
    std::cout << "Select option: " << std::endl;
    std::cout << "1. \tCount of transactions" << std::endl;
    std::cout << "2. \tMinimum resource size" << std::endl;
    std::cout << "3. \tAll transactions" << std::endl;
    std::cout << "4. \tTransactions of id" << std::endl;
    std::cout << "5. \tSum of claims until n" << std::endl;
    std::cout << "6. \tList identifiers" << std::endl;
    std::cout << "7. \tValidate" << std::endl;
    std::cout << "8. \tMaxima" << std::endl;
    std::cout << "9. \tCheck pool size" << std::endl;
    std::cout << "10.\tQuit" << std::endl;
}

bool menu(TransactionList& transactions) {
    // Print the option menu
    print_menu();

    // Request the user an option
    int choice;
    std::cout << "> ";
    std::cin >> choice;

    std::cout << std::endl;

    // Needed variables (for some reasons not possible to declare them locally in the switch statement)
    std::string id;
    int count;

    // Process the chosen option
    switch (choice) {
        case 1:
            print_count_of_transactions(transactions);
            break;
        case 2:
            print_minimum_resource_size(transactions);
            break;
        case 3:
            transactions.print_transactions();
            break;
        case 4:
            std::cout << "ID:";
            std::cin >> id;
            transactions.print_transaction_with_id(id);
            break;
        case 5:
            std::cout << "Until when:";
            std::cin >> count;
            print_sum_of_claims(transactions, count);
            break;
        case 6:
            transactions.list_identifiers();
            break;
        case 7:
            if (transactions.validate()) {
                std::cout << "The list is valid." << std::endl;
            } else {
                std::cout << "The list isn't valid." << std::endl;
            }
            break;
        case 8:
            transactions.maxima();
            break;
        case 9:
            std::cout << "Enter pool size:";
            std::cin >> count;
            transactions.check_pool_size(count);
            break;
        case 10:
            std::cout << "Bye!" << std::endl;
            return false;
        default:
            std::cout << "Incorrect option, try again." << std::endl;
            break;
    }
    std::cout << std::endl;
    return true;
}