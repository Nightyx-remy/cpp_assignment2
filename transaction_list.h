#ifndef CPP_ASSIGNMENT2_TRANSACTION_LIST_H
#define CPP_ASSIGNMENT2_TRANSACTION_LIST_H

#include "transaction.h"

struct TransactionList {
    static const int MAX_TRANSACTION {100};
    Transaction transactions[MAX_TRANSACTION];
    int size {0};

    /**
     * Add a transaction to the list of transaction
     *
     * @param transaction
     */
    void add_transaction(Transaction transaction);

    /**
     * Load the list of transaction from a file.
     *
     * @param file_name the name of the file being loaded
     * @return true if the list of transaction as been loaded correctly, false otherwise
     */
    bool load_from_file(const std::string& file_name);

    /**
     * Calculate the minimum resource size needed.
     *
     * @return the calculated value
     */
    int minimum_resource_size();

    /**
     * Print all the transaction in the list of transaction
     */
    void print_transactions();

    /**
     * Print all the transactions with a matching id
     *
     * @param id the id of the transaction being printed
     */
    void print_transaction_with_id(const std::string& id);

    /**
     * Calculate the resource at the end of the first n transactions
     *
     * @param n the number of transaction calculated
     * @return the calculated value
     */
    int sum_of_claims(int n);

    /**
     * Print all the unique identifiers
     */
    void list_identifiers();

    /**
     * Check if the list of transaction is correct (if no process become negative).
     *
     * @return true if the list is correct, false otherwise
     */
    bool validate();

    /**
     * Print the the resource and identifier of the process taking the most
     * resource in the list and at the end of the list.
     */
    void maxima();

    /**
     * Check if the pool is big enough, if not, print the transaction to remove
     * in order to make it big enough
     *
     * @param pool_size
     */
    void check_pool_size(int pool_size);
};

#endif //CPP_ASSIGNMENT2_TRANSACTION_LIST_H
