#include "hashing.h"

// Hardcoded primes from the plan
static int primes[] = {
    11, 101, 251, 503, 751, 1009, 1259, 1511, 1753, 2003, 2251, 2503, 2753, 3001, 3251,
    3511, 3761, 4001, 4253, 4507, 4751, 5003, 5261, 5501, 5779, 6007, 6257, 6521, 6761, 
    7001, 7253, 7507, 7753, 8009, 8273, 8501, 8753, 9001, 9257, 9511, 9767, 10007, 10253,
    10501, 10753, 11003, 11251, 11503, 11777, 12007, 12251, 12503, 12757, 13001, 13259, 
    13513, 13751, 14009, 14251, 14503, 14753, 15013, 15259, 15511, 15761, 16001, 16267, 
    16519, 16759, 17011, 17257, 17507, 17767, 18013, 18251, 18503, 18757, 19001, 19259, 
    19501, 19751, 20011, -1 // Sentinel
};

unsigned int hash_function(char *str, int table_size) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % table_size;
}

int find_closest_prime(int estimate) {
    for (int i = 0; primes[i] != -1; i++) {
        if (primes[i] >= estimate) {
            return primes[i];
        }
    }
    return 20011; // Return largest if estimate exceeds
}
