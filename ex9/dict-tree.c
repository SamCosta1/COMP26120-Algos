#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;
struct node
{
  Key_Type element; // only data is the key itself
  tree_ptr left, right;
  // add anything else that you need
};

struct table
{
  tree_ptr head; // points to the head of the tree
};


Table initialize_table(/*ignore parameter*/)
{
    Table table = malloc(sizeof(table));
    table->head = NULL;
    return table;
}

Table insert(Key_Type word, Table table)
{

}

Boolean findInTree(Key_Type word, tree_ptr tree) {
    int compareVal = strcmp(tree->element, word);

    if (compareVal < 0) {
        if (tree->left != NULL)
            findInTree(word, tree->left);
        else
            return FALSE;
    }

    if (compareVal > 0) {
        if (tree->right != NULL)
            findInTree(word, tree->right);
        else
            return FALSE;
    }

    if (compareVal == 0)
        return TRUE;
}

Boolean find(Key_Type word, Table table)
{
    if (table->head == NULL) // There is no tree
    return FALSE;

    return findInTree(word, table->head);
}

void print_table(Table table)
{
}

void print_stats (Table table)
{
}
