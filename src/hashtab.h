#ifndef HASHTAB_H
#define HASHTAB_H

#define HASH_MUL 31
#define HASH_SIZE 50000

typedef struct listnode {
    char *key;
    int value;
    struct listnode *next;
} listnode;

listnode *hashtab[HASH_SIZE];

unsigned fnv_hash(void *key, int len);
int hashtab_hash(char *key);
void hashtab_init(listnode **hashtab);
void hashtab_add(listnode **hashtab, char *key, int value, int *colliz);
listnode *hashtab_lookup(listnode **hashtab, char *key);
void hashtab_delete(listnode **hashtab, char *key);

#endif
