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
  tree_ptr parent;
  tree_ptr left, right;
  // add anything else that you need
};

struct table
{
  tree_ptr head; // points to the head of the tree
};

static int averageStringComps = -1;
static int numStringComps = 0;

Table initialize_table(/*ignore parameter*/) {
    Table table = malloc(sizeof(struct table));
    check(table);
    table->head = NULL;
    return table;
}

tree_ptr newNode(Key_Type element, tree_ptr parent, tree_ptr left, tree_ptr right) {
    tree_ptr new = malloc(sizeof(struct node));
    check(new);
    new -> element = strdup(element);
    new -> parent = parent;
    new -> left = left;
    new -> right = right;

    return new;
}

void insertToTree(Key_Type word, tree_ptr tree) {
    int compareVal = strcmp(tree->element, word);

    if (compareVal < 0) {
        if (tree -> left != NULL)
            insertToTree(word, tree->left);
        else {
            tree -> left = newNode(word, tree, NULL, NULL);
        }
    }

    if (compareVal > 0) {
        if (tree -> right != NULL)
            insertToTree(word, tree->right);
        else {
            tree -> right = newNode(word, tree, NULL, NULL);
        }
    }
}

Table insert(Key_Type word, Table table) {
    // There isn't yet a root, so make this the root
    if (table->head == NULL) {
        table -> head = newNode(word, NULL, NULL, NULL);
    } else {
        insertToTree(word, table->head);
    }

    return table;
}

Boolean findInTree(Key_Type word, tree_ptr tree) {
    int compareVal = strcmp(tree->element, word);
    numStringComps++;

    if (compareVal < 0) {
        if (tree->left != NULL)
            return findInTree(word, tree->left);
        else
            return FALSE;
    }

    if (compareVal > 0) {
        if (tree->right != NULL)
            return findInTree(word, tree->right);
        else
            return FALSE;
    }

    return TRUE; // They must be equal so strings must be identical
}

Boolean find(Key_Type word, Table table) {
    if (table->head == NULL) // There is no tree
        return FALSE;
    numStringComps = 0;
    Boolean result = findInTree(word, table->head);

    if (averageStringComps < 0)
        averageStringComps = numStringComps;
    else
        averageStringComps = (averageStringComps + numStringComps) / 2;

    return result;
}

void print_tree_in_order(tree_ptr tree) {
    if (tree == NULL)
        return;

    print_tree_in_order(tree->left);
    printf("%s \n", tree->element);
    print_tree_in_order(tree->right);
}

void print_table(Table table) {
    print_tree_in_order(table->head);
}

void print_stats (Table table) {
    printf("Avarage #String compares in find: %d\n", averageStringComps);
}
