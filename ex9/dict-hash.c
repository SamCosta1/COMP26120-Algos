#define _XOPEN_SOURCE 500
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

    // Initialize all cells
    for (int i = 0; i < tsize; i++) {
      (&(table->cells)[i])->state = empty;
      (&(table->cells)[i])->element = NULL;
   }

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

int hashBad(Key_Type key, int size) {
    int hash = 0;
    for (int i = 0; i < sizeof(key); i++) {
        if (key[i] == 0) // ignoring trailing spaces
            break;
        hash += key[i];
    }
    return hash % size;
}

int hashBetter(Key_Type key, int size) {
    int hash = 0;
    for (int i = 0; i < sizeof(key); i++) {
        if (key[i] == 0) // ignoring trailing spaces
            break;

        hash += (int) fme(key[i], i + 1, size);
    }
    return hash % size;
}

int hash(Key_Type key, int size) {
    if (mode == 1)
        return hashBetter(key, size);

    return hashBad(key, size);
}

void populateCell(Key_Type key, cell* theCell) {
   theCell->state = in_use;
   theCell->element = strdup(key);
}

int primes[] = {7, 47,  191, 569, 1217, 2411, 5437, 7919};
int getPrimeLessThanValue(int value) {
   if (value < 7)
      return value - 1;

   for (int i = 0; i < 8; i++)
      if (primes[i] > value)
         return primes[i-1];

   // Should never happen
   return 7;

}

int secondaryHash(Key_Type key, int size) {
   int prime =  getPrimeLessThanValue(size);

   return prime - (hash(key, size) % prime);
}

Boolean equals(Key_Type a, Key_Type b) {
   return strcmp(a,b) == 0;
}

Table insert (Key_Type key, Table t) {
printf("Insert: %s\n", key);
    if (t->num_entries == t->table_size)
        return t;

    int hashVal = hash(key, t->table_size);

    cell *cells = t->cells;
    cell *hashCell = &cells[hashVal];


    if (hashCell->state == empty) {
        populateCell(key, hashCell);
        t->num_entries++;
        return t;
    }

    // Ignore duplicates
    if (equals(hashCell->element, key))
      return t;

    // Perform double hashing if no space found
    int i = 1;
    Boolean spaceFound = FALSE;

    while (spaceFound == FALSE) {
      int newHash = (hashVal + i * secondaryHash(key, t->table_size))
                    % t->table_size;

      cell *hashCell = &cells[newHash];


      if (hashCell->state == empty) {
         populateCell(key, hashCell);
         t->num_entries++;
         spaceFound = TRUE;
      }

      // Ignore duplicates
      if (equals(hashCell->element, key))
      return t;
   }

   return t;
}

Boolean find (Key_Type key, Table t)
{
    cell *cells = t->cells;
    int hashVal = hash(key, t->table_size);
    // Try normal hash location
    cell* hashCell = &cells[hashVal];

    if (hashCell->state == empty)
      return FALSE;

    if (equals(key, hashCell->element))
      return TRUE;

    // Apply double hash until found or empty cell found
    int i = 1;
    Boolean stop = FALSE;

    while (stop == FALSE) {
      int newHash = (hashVal + i * secondaryHash(key, t->table_size))
                    % t->table_size;

      cell *hashCell = &cells[newHash];

      if (equals(key, hashCell->element))
         return TRUE;
      else if (hashCell->state != deleted)
         stop = TRUE;
   }

    return FALSE;
}

void print_table (Table t)
{
   printf("Printing");fflush(stdout);
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
