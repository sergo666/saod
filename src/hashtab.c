#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtab.h"
#define HASH_MUL 31
#define HASH_SIZE 50000

int colliz = 0;

int hashtab_hash(char *key)
{
    int h = 0;
    char *p;

    for (p = key; *p != '\0'; p++)
        h *= HASH_MUL + (unsigned int)*p;
    return h % HASH_SIZE;
}

unsigned fnv_hash(void *key, int len)
{
    unsigned char *p = key;
    unsigned h = 2166136261;
    int i;

    for (i = 0; i < len; i++) {
        h = (h * 16777619) ^ p[i];
    }
    return h;
}

void hashtab_init(listnode **hashtab)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
        hashtab[i] = NULL;
}


void hashtab_add(listnode **hashtab, char *key, int value, int *colliz)
{
    listnode *node;
    int index = hashtab_hash(key);
    *colliz = 0;

    node = malloc(sizeof(*node));
    if (node) {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
        *colliz++;
    }
}


listnode *hashtab_lookup(listnode **hashtab, char *key)
{
    int index;
    listnode *node;

    index = hashtab_hash(key);
    for (node = hashtab[index]; node; node = node->next)
        if (!strcmp(node->key, key))
            return node;

    return NULL;
}

void hashtab_delete(listnode **hashtab, char *key)
{
    int index;
    listnode *p, *prev = NULL;

    index = hashtab_hash(key);
    for (p = hashtab[index]; p; p = p->next) {
        if (!strcmp(p->key, key)) {
            if (!prev)
                hashtab[index] = p->next;
            else
                prev->next = p->next;
            free(p);
            return;
        }
        prev = p;        
    }
    return NULL;
}
