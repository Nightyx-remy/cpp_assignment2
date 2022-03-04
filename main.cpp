#include <iostream>
#include "menu.h"

int main() {
    // Request a file name
    std::cout << "Enter the file name you want to read: ";
    std::string file_name;
    std::cin >> file_name;

    TransactionList transactions {};

    // Load the transactions
    if (!transactions.load_from_file(file_name)) {
        return -1;
    }

    while (menu(transactions));

    return 0;
}
