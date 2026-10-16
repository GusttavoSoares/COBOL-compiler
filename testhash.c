#include <stdio.h>
#include "hashtable.h"
#include <stdlib.h>

void exit_nomem(void) {
    fprintf(stderr, "out of memory\n");
    exit(1);
}

int main(void) {
    hash_table* counts = hashTableCreate();

    if (counts == NULL) {
        exit_nomem;
    }

    char word[101];

    while(scanf("%100s", word) != EOF) {
        void* value = ht_get(counts, word);

        if (value != NULL) {
            int* pcount = (int*) value;
            (*pcount)++;
            continue;
        }

        int* pcount = malloc(sizeof(int));
        if (pcount == NULL) {
            exit_nomem();
        }
        *pcount = 1;
        if (ht_set(counts, word, pcount) == NULL) {
            exit_nomem();
        }
    }

    hti it = ht_iterator(counts);
    while (ht_next(&it)) {
        printf("---------------------\n");
        printf("%s %d\n", it.key, *(int*)it.value);
        free(it.value);

    }

    printf("%d\n", (int)ht_length(counts));
    return 0;
}