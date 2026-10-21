#include "hashtable.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INITIAL_CAPACITY 16 // Capacidade inicial do hash, aumenta com o extend

// key, value
typedef struct {
    const char*  key;
    void* value; // the void acts like any or universal type
} hash_table_entry;

struct hash_table {
    hash_table_entry* entries;
    size_t capacity; // size of entries array
    size_t length; // number of items in hash table  
};


void ht_destroy(hash_table* table) {
    // Libera as chaves (copiadas com strdup). Os values sao responsabilidade de quem chamou
    for (size_t i = 0; i < table->capacity; i++) {
        free((void*)table->entries[i].key);
    }

    free(table->entries);
    free(table);
}

hash_table* hashTableCreate(void) {
    hash_table* table = malloc(sizeof(hash_table));
    
    if (table == NULL) {
        return NULL; // Alocação falhou
    }

    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    // Aloca memoria iniciando com zero. (amount, size). Amount é a quantidade de elementos posíveis
    // size tamanho de cada item
    table->entries = calloc(table->capacity, sizeof(hash_table_entry));

    if (table->entries == NULL) {
        free(table);
        return NULL;
    }

    return table;

}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL


// Fowler-Noll-Vo hash function
static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;

    for (const char* p = key; *p; p++) { // roda enquanto o ponteiro apontar para um valor diferente de zero (nao for terminador nulo)
        hash *= FNV_PRIME;
        hash ^= (uint64_t)(unsigned char) (*p);
    }

    return hash;
}

// Se já tiver colocado uma vez, atualiza apenas  o value
// Se nao tiver colocado nenhuma vez, atualiza value e key
static const char* ht_set_entry(hash_table_entry* entries, size_t capacity, const char* key, void* value, size_t* plength) {
    uint64_t hash = hash_key(key);
    size_t index = (size_t) (hash & (uint64_t)(capacity -1)); // *

    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            entries[index].value = value;
            return entries[index].key;
        }

        index++;
        if (index >= capacity) {
            index = 0;
        }
    }

    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plength)++;
    }
    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;
    }


// Dobra a capacidade da tabela e reposiciona todas as entradas
static bool ht_expand(hash_table* table) {
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) {
        return false; // overflow
    }

    hash_table_entry* new_entries = calloc(new_capacity, sizeof(hash_table_entry));
    if (new_entries == NULL) {
        return false;
    }

    // plength NULL: as chaves ja foram copiadas, so move os ponteiros
    for (size_t i = 0; i < table->capacity; i++) {
        hash_table_entry entry = table->entries[i];
        if (entry.key != NULL) {
            ht_set_entry(new_entries, new_capacity, entry.key, entry.value, NULL);
        }
    }

    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return true;
}

const char* ht_set(hash_table* table, const char* key, void* value) {
    //assert(value != NULL);
    if (value == NULL) {
        return NULL;
    }

    if (table->length >= table->capacity / 2) {
        if (!ht_expand(table)) {
            return NULL;
        }
    }

    return ht_set_entry(table->entries, table->capacity, key, value, &table->length);
}

hti ht_iterator(hash_table* table) {
    hti it;
    it._table = table;
    it._index = 0;
    return it;
}

bool ht_next(hti* it) {
    hash_table* table = it->_table;
    while (it->_index < table->capacity) {
        size_t i = it->_index;
        it->_index++;
        if (table->entries[i].key != NULL) {
            hash_table_entry entry = table->entries[i];
            it->key = entry.key;
            it->value = entry.value;
            return true;
        }
    }
    return false;
}


void* ht_get(hash_table* table, const char* key) {
    uint64_t hash = hash_key(key);
    size_t index = (size_t) (hash & (uint64_t) (table->capacity -1 ));

    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            return table->entries[index].value;
        }

        index++;
        if (index >= table->capacity) {
            index = 0;
        }
    }

    return NULL;

}

size_t ht_length(hash_table* table) {
    return table->length;
}