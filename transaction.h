#ifndef CPP_ASSIGNMENT2_TRANSACTION_H
#define CPP_ASSIGNMENT2_TRANSACTION_H

#include <string>

struct Transaction {
    std::string id {"Unknown"};
    int value {0};

    /**
     * Create a copy of the current transaction
     *
     * @return the copy created
     */
    Transaction clone();
};

#endif //CPP_ASSIGNMENT2_TRANSACTION_H
