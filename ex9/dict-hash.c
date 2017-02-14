#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct
{ // hash-table entry
  Key_Type element; // only data is the key itself
  enum {empty, in_use, deleted} state;
} cell;


typedef unsigned int Table_size; // type for size-of or index-into hash table

struct table
{
  cell *cells;
  Table_size table_size; // cell cells [table_size];
  Table_size num_entries; // number of cells in_use
  // add anything else that you need
};

Table initialize_table (Table_size tsize) {
    printf("Table size = %d\n", tsize);
    Table table = malloc(sizeof(struct table));
    check(table);
    table->cells = malloc(sizeof(cell) * tsize);
    check(table->cells);

    table->num_entries = 0;
    table->table_size = tsize;

    return table;
}

unsigned long fme(unsigned long primitiveRoot, unsigned long exponent,
                  unsigned long prime) {
    unsigned long d = primitiveRoot;
    unsigned long e = exponent;
    unsigned long accumulator = 1;

    while (e != 0) {
        if ((e % 2) != 0)
            accumulator = (accumulator * d) % prime;
        d = (d * d) % prime;
        e = e / 2;
    }

    return accumulator;
}

int hash(Key_Type key, int size) {
    int hash = 0;
    for (int i = 0; i < sizeof(key); i++) {
        if (key[i] == 0) // ignoring trailing spaces
            break;

        hash += (int) fme(key[i], i + 1, size);
    }
    return hash % size;
}

Table insert (Key_Type key, Table t) {
    int hashVal = hash(key, t->table_size);

    cell *cells = t->cells;
    cell *hashCell = &cells[hashVal];

    if (hashCell->state == empty) {
        hashCell->state = in_use;
        hashCell->element = strdup(key);

        t->num_entries++;
    }

    return t;

}

Boolean find (Key_Type key, Table t)
{
    return FALSE;
}

void print_table (Table t)
{
    int i;
    cell *cells = t->cells;
    for (i = 0; i < t->table_size; i++) {
        cell *c = &cells[i];

        printf("%2d  %s\n", i, c->element == NULL? "" : c->element);
    }
}

void print_stats (Table t)
{
}
