#ifndef _HT_H // # check if a unique value is defined. If its not defined, it defines it and continues to the rest of the page
#define _HT_H // When the code ins inclded again, the first ifndef fails, resulting in a blank file

#include <stdbool.h>
#include <stddef.h>

typedef struct hash_table hash_table;

hash_table* hashTableCreate(void);

// void ht_destroy(hash_table* table);

void* ht_get(hash_table* table, const char* key);

const char* ht_set(hash_table* table, const char* key, void* value);

size_t ht_length(hash_table* table);

hash_table* hashTableCreate(void);

typedef struct {
    const char* key;
    void* value;

    hash_table* _table;
    size_t _index;

} hti;

hti ht_iterator(hash_table* table);

bool ht_next(hti* it);

#endif