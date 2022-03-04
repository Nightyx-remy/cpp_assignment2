//
// Created by Remyf on 3/3/2022.
//

#include "transaction_list.h"
#include <iostream>
#include <fstream>
#include <vector>

void TransactionList::add_transaction(Transaction transaction) {
    // Check if the transaction list is not full
    if (this->size < MAX_TRANSACTION) {
        this->transactions[this->size++] = std::move(transaction);
    }
}

std::vector<std::string> split_at_space(const std::string& str) {
    std::vector<std::string> parts;
    std::string current_part;

    for (auto chr : str) {
        if (chr == ' ') {
            parts.push_back(current_part);
            current_part = "";
        } else {
            current_part.push_back(chr);
        }
    }

    if (current_part.length() != 0) {
        parts.push_back(current_part);
    }

    return parts;
}

bool TransactionList::load_from_file(const std::string& file_name) {
    // Open the file
    std::ifstream input {file_name};
    if (!input) {
        std::cout << "Failed to open file '" << file_name << std::endl;
        return false;
    }

    // Read the file line by line
    std::string line;
    while (std::getline(input, line)) {
        if (!line.empty() && line != "\n") {
            std::vector<std::string> parts = split_at_space(line);
            if (parts.size() == 2) {
                Transaction transaction = Transaction {
                        parts[0],
                        std::stoi(parts[1])
                };
                this->add_transaction(transaction);
            } else {
                // The file is not formatted correctly
                std::cout << line << std::endl;
                std::cout << "The file is not formatted properly!" << std::endl;
                return false;
            }
        }
    }

    return true;
}

int TransactionList::minimum_resource_size() {
    Transaction unique_transactions[MAX_TRANSACTION];   // Transactions with unique ID
    int count = 0;                                      // Number of unique transactions
    int max_resource = 0;                               // Maximum resources used in the whole file
    int resource = 0;                                   // Current resources used

    // Loop through all the transactions
    for (int i = 0; i < this->size; i++) {
        Transaction current = this->transactions[i];

        if (current.value == 0) {   // Free the process
            // Look for the current value the process that will be freed
            for (int j = 0; j < count; j++) {
                Transaction* current2 = &unique_transactions[j];
                if (current2->id == current.id) {
                    // Free the process found
                    resource -= current2->value;
                    current2->value = 0;
                    goto ctn;
                }
            }

            // Process not found, nothing to do
            goto ctn;
        } else {
            resource += this->transactions[i].value;
            max_resource = std::max(resource, max_resource);
        }

        // Update the unique transactions
        for (int j = 0; j < count; j++) {
            Transaction* current2 = &unique_transactions[j];
            if (current2->id == current.id) {
                current2->value += current.value;
                goto ctn;
            }
        }

        // New unique transactions
        unique_transactions[count++] = Transaction {
            current.id,
            current.value,
        };

        ctn:;
    }

    return max_resource;
}

void TransactionList::print_transactions() {
    Transaction unique_transactions[MAX_TRANSACTION];   // Transactions with unique ID
    int count = 0;                                      // Number of unique transaction
    int resource = 0;                                   // Current resources used

    // Loop through all the transactions
    for (int i = 0; i < this->size; i++) {
        Transaction current = this->transactions[i];

        if (current.value == 0) {   // Free the process
            // Look for the current value the process that will be freed
            for (int j = 0; j < count; j++) {
                Transaction* current2 = &unique_transactions[j];
                if (current2->id == current.id) {
                    // Free the process found
                    resource -= current2->value;
                    current2->value = 0;
                    goto ctn;
                }
            }

            // Process not found, nothing to do
            goto ctn;
        } else {
            resource += this->transactions[i].value;
        }

        // Update the unique transactions
        for (int j = 0; j < count; j++) {
            Transaction* current2 = &unique_transactions[j];
            if (current2->id == current.id) {
                current2->value += current.value;
                goto ctn;
            }
        }

        // New unique transactions
        unique_transactions[count++] = Transaction {
            current.id,
            current.value,
        };

        ctn:;

        // Print the transaction
        std::cout << i << "\t" << current.id << " " << current.value << " " << resource << std::endl;
    }
}

void TransactionList::print_transaction_with_id(const std::string &id) {
    Transaction unique_transactions[MAX_TRANSACTION];   // Transactions with unique ID
    int count = 0;                                      // Number of unique transaction
    int resource = 0;                                   // Current resources used

    // Loop through all the transactions
    for (int i = 0; i < this->size; i++) {
        Transaction current = this->transactions[i];

        if (current.value == 0) {   // Free the process
            // Look for the current value the process that will be freed
            for (int j = 0; j < count; j++) {
                Transaction* current2 = &unique_transactions[j];
                if (current2->id == current.id) {
                    // Free the process found
                    resource -= current2->value;
                    current2->value = 0;
                    goto ctn;
                }
            }

            // Process not found, nothing to do
            goto ctn;
        } else {
            resource += this->transactions[i].value;
        }

        // Update the unique transactions
        for (int j = 0; j < count; j++) {
            Transaction* current2 = &unique_transactions[j];
            if (current2->id == current.id) {
                current2->value += current.value;
                goto ctn;
            }
        }

        // New unique transactions
        unique_transactions[count++] = Transaction {
            current.id,
            current.value,
        };

        ctn:;

        // Check if the current transaction as a matching id
        if (current.id == id) {
            // Print the transaction
            std::cout << i << "\t" << current.id << " " << current.value << " " << resource << std::endl;
        }
    }
}

int TransactionList::sum_of_claims(int n) {
    Transaction unique_transactions[MAX_TRANSACTION];   // Transactions with unique ID
    int count = 0;                                      // Number of unique transaction
    int resource = 0;                                   // Current resources used

    // Loop through all the transactions
    for (int i = 0; i < std::min(this->size, n); i++) {
        Transaction current = this->transactions[i];

        if (current.value == 0) {   // Free the process
            // Look for the current value the process that will be freed
            for (int j = 0; j < count; j++) {
                Transaction* current2 = &unique_transactions[j];
                if (current2->id == current.id) {
                    // Free the process found
                    resource -= current2->value;
                    current2->value = 0;
                    goto ctn;
                }
            }

            // Process not found, nothing to do
            goto ctn;
        } else {
            resource += this->transactions[i].value;
        }

        // Update the unique transactions
        for (int j = 0; j < count; j++) {
            Transaction* current2 = &unique_transactions[j];
            if (current2->id == current.id) {
                current2->value += current.value;
                goto ctn;
            }
        }

        // New unique transactions
        unique_transactions[count++] = Transaction {
            current.id,
            current.value,
        };

        ctn:;
    }

    return resource;
}

void TransactionList::list_identifiers() {
    std::string ids[MAX_TRANSACTION];   // List of unique ids
    int id_count = 0;                   // Number of unique ids

    // Loop through all the transactions
    for (int i = 0; i < this->size; i++) {
        Transaction transaction = this->transactions[i];

        // Check if the id already exists
        for (const auto& id : ids) {
            if (transaction.id == id) {
                goto cnt;
            }
        }

        // New transaction id
        ids[id_count++] = transaction.id;
        std::cout << transaction.id << std::endl;

        cnt:;
    }
}

bool TransactionList::validate() {
    Transaction unique_transactions[MAX_TRANSACTION];   // Transactions with unique ID
    int count = 0;                                      // Number of unique transaction
    int resource = 0;                                   // Current resources used

    // Loop through all the transactions
    for (int i = 0; i < this->size; i++) {
        Transaction current = this->transactions[i];

        if (current.value == 0) {   // Free the process
            // Look for the current value the process that will be freed
            for (int j = 0; j < count; j++) {
                Transaction* current2 = &unique_transactions[j];
                if (current2->id == current.id) {
                    // Free the process found
                    resource -= current2->value;
                    current2->value = 0;
                    goto ctn;
                }
            }

            // Process not found, nothing to do
            goto ctn;
        } else {
            resource += this->transactions[i].value;
        }

        // Update the unique transactions
        for (int j = 0; j < count; j++) {
            Transaction* current2 = &unique_transactions[j];
            if (current2->id == current.id) {
                current2->value += current.value;
                if (current2->value < 0) {
                    return false;
                }
                goto ctn;
            }
        }

        // New unique transactions
        if (current.value < 0) {
            return false;
        }

        unique_transactions[count++] = Transaction {
            current.id,
            current.value,
        };

        ctn:;
    }

    return true;
}

void TransactionList::maxima() {
    Transaction unique_transactions[MAX_TRANSACTION];   // Transactions with unique ID
    int count = 0;                                      // Number of unique transaction
    int resource = 0;                                   // Current resources used
    Transaction max{};

    // Loop through all the transactions
    for (int i = 0; i < this->size; i++) {
        Transaction current = this->transactions[i];

        if (current.value == 0) {   // Free the process
            // Look for the current value the process that will be freed
            for (int j = 0; j < count; j++) {
                Transaction* current2 = &unique_transactions[j];
                if (current2->id == current.id) {
                    // Free the process found
                    resource -= current2->value;
                    current2->value = 0;
                    goto ctn;
                }
            }

            // Process not found, nothing to do
            goto ctn;
        } else {
            resource += this->transactions[i].value;
        }

        // Update the unique transactions
        for (int j = 0; j < count; j++) {
            Transaction* current2 = &unique_transactions[j];
            if (current2->id == current.id) {
                current2->value += current.value;

                // Check if the process use more resource than the current maximum
                if (current2->value > max.value) {
                    max = current2->clone();
                }

                goto ctn;
            }
        }

        // New unique transactions
        unique_transactions[count++] = Transaction {
            current.id,
            current.value,
        };

        // Check if the process use more resource than the current maximum
        if (current.value > max.value) {
            max = current.clone();
        }

        ctn:;
    }

    // Find the maximum between all the process at the end of the execution
    Transaction end_max = unique_transactions[0];
    for (int i = 1; i < count; i++) {
        Transaction current = unique_transactions[i];
        if (current.value > max.value) {
            max = unique_transactions[i];
        }
    }
    std::cout << "The maximum total claim at the end is " << end_max.value << " for '" << end_max.id << "'." << std::endl;

    // Print the maximum in the whole list
    std::cout << "The maximum total claim in the list is " << max.value << " for '" << max.id << "'." << std::endl;
}

void TransactionList::check_pool_size(int pool_size) {
    std::vector<int> to_remove_ids;                     // ID of the transactions to remove
    Transaction unique_transactions[MAX_TRANSACTION];   // Transactions with unique ID
    int transaction_count[MAX_TRANSACTION] = {0};       // Number of transactions in each unique transaction
    int count = 0;                                      // Number of unique transaction
    int maximum_load = 0;                               // Maximum resources used
    int resource = 0;                                   // Current resources used
    Transaction max{};

    // Loop through all the transactions
    for (int i = 0; i < this->size; i++) {
        Transaction current = this->transactions[i];

        if (current.value == 0) {   // Free the process
            // Look for the current value the process that will be freed
            for (int j = 0; j < count; j++) {
                Transaction* current2 = &unique_transactions[j];
                if (current2->id == current.id) {
                    // Free the process found
                    resource -= current2->value;
                    current2->value = 0;
                    transaction_count[j] = 0; // Set to 0 since it's useless to remove this transaction and the previous one
                    goto ctn;
                }
            }

            // Process not found, nothing to do
            goto ctn;
        } else {
            resource += this->transactions[i].value;
        }

        // Update the unique transactions
        for (int j = 0; j < count; j++) {
            Transaction* current2 = &unique_transactions[j];
            if (current2->id == current.id) {
                current2->value += current.value;
                transaction_count[j]++;

                // Check if the process use more resource than the current maximum
                if (current2->value > max.value) {
                    max = current2->clone();
                }

                goto ctn;
            }
        }

        // New unique transactions
        unique_transactions[count] = Transaction {
            current.id,
            current.value,
        };
        transaction_count[count++]++;

        // Check if the process use more resource than the current maximum
        if (current.value > max.value) {
            max = current.clone();
        }

        ctn:;

        while (resource > pool_size) {
            for (int j = i; j > 0; j--) {
                Transaction current2 = this->transactions[j];

                if (current2.value > 0) {
                    // Look for the number of transaction in the transaction list
                    for (int k = 0; k < count; k++) {
                        Transaction current3 = unique_transactions[k];
                        if (current2.id == current3.id) {
                            if (transaction_count[k] > 1) {
                                // Remove transaction
                                transaction_count[k]--;
                                unique_transactions[k].value -= current2.value;
                                resource -= current2.value;
                                to_remove_ids.push_back(j);

                                goto skip_no_solution;
                            }
                            break;
                        }
                    }
                }
            }

            std::cout << "No solutions!" << std::endl;
            return;

            skip_no_solution:;
        }

        maximum_load = std::max(resource, maximum_load);
    }

    if (!to_remove_ids.empty()) {
        std::cout << "Not ok." << std::endl;
        std::cout << "Remove:" << std::endl;

        for (auto id : to_remove_ids) {
            Transaction transaction = this->transactions[id];

            std::cout << id << "\t" << transaction.id << "\t" << transaction.value << std::endl;
        }
    } else {
        std::cout << "Ok." << std::endl;
    }

    std::cout << "Free pool at the end " << pool_size - resource << "." << std::endl;
    std::cout << "Free pool under the maximum load " << pool_size - maximum_load << "." << std::endl;
}