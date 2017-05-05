#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "bstree.h"
#include "hashtab.h"

const int MAX_WORDS = 50000;
const int STEP = 2500;
const int COUNT_OF_SEARCH = 100;

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max) {
    return (double) rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main() 
{
    double timeTable[MAX_WORDS / STEP + 1];
    double t;
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    int i = 0;
    char *words[MAX_WORDS]; //SIZE

    f = fopen("words.txt", "r");
    if (!f)
        exit(-1);
    while ((getline(&line, &len, f)) != -1 && i < MAX_WORDS) {
        line[strlen(line) - 1] = '\0';
        words[i] = malloc(strlen(line) + 1);
        strcpy(words[i++], line);
    }
    
    bstree *tree = bstree_create(words[0], 0), *node;

    for(i = 1; i <= MAX_WORDS; i++) {
    int ti = (i-1) / STEP;
        bstree_add(tree, words[i], i);
        //hashtab_add(hashtab, words[i], i);
        if(i % STEP == 0) {
            timeTable[ti] = 0;
            int j;
            for(j = 0; j < COUNT_OF_SEARCH; j++) {
                int r = getrand(1, i);
                t = wtime();
                node = bstree_lookup(tree, /* "ящичному"*/words[r]);
                //node = hashtab_lookup(hashtab, /*"ящичному"*/ words[r]);
                timeTable[ti] = wtime() - t;
            }
      timeTable[ti] /= COUNT_OF_SEARCH;


      printf("%d %.9lf\n", i, timeTable[ti]);
        }
    }
}
