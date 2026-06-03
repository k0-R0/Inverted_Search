#ifndef HASHING_H
#define HASHING_H

#include "common.h"

unsigned int hash_function(char *str, int table_size);
int find_closest_prime(int estimate);

#endif
