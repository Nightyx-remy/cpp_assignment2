#include "transaction.h"

Transaction Transaction::clone() {
    return Transaction {
        this->id,
        this->value
    };
}
