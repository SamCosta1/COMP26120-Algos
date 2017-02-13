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
  int height;
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
    new -> parent = parent;
    new -> left = left;
    new -> right = right;
    new -> height = 1;
    new -> element = strdup(element);
    return new;
}

Boolean isRoot(tree_ptr t) {
    return t->parent == NULL;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int maxNodes(tree_ptr a, tree_ptr b) {
    return max(a == NULL ? 0 : a->height, b == NULL ? 0 : b->height);
}

tree_ptr tallest(tree_ptr node) {
    if (node == NULL)
        return NULL;

    int leftHeight = node->left == NULL ? 0 : (node->left)->height;
    int rightHeight = node->right == NULL ? 0 : (node->right)->height;

    if (leftHeight > rightHeight)
        return node->left;

    return node->right;
}

void setParent(tree_ptr node, tree_ptr parent) {
    if (node != NULL)
        node -> parent = parent;
}

int getHeight(tree_ptr node) {
    return node == NULL ? 0 : node -> height;
}

tree_ptr restructure(tree_ptr x, tree_ptr y, tree_ptr z) {
    tree_ptr T0;
    tree_ptr T1;
    tree_ptr T2;
    tree_ptr T3;
    tree_ptr a;
    tree_ptr b;
    tree_ptr c;

    if (z->right == y) {
        a = z;

        if (y->right == x) { // (a)
            b = y;
            c = x;

            T1 = b->left;
            T2 = c->left;
        } else { // (c)
            b = x;
            c = y;

            T1 = b -> left;
            T2 = b -> right;
        }
    } else {
        c = z;

        if (y -> right == x) { // (d)
            a = y;
            b = x;

            T1 = b -> left;
            T2 = b -> right;
        } else { // (b)
            b = y;
            a = x;

            T1 = a -> right;
            T2 = b -> right;
        }
    }

    T0 = a -> left;
    T3 = c -> right;

    if (z->parent != NULL) {
        if (z->parent->left == z)
            z->parent->left = b;
        else
            z->parent->right = b;
    }

    b->parent = z->parent;

    b->left = a;
    a->left = T0;
    a->right = T1;

    b->right = c;
    c->left = T2;
    c->right = T3;

    setParent(a,b);
    setParent(T0,a);
    setParent(T1,a);
    setParent(c,b);
    setParent(T2,c);
    setParent(T3,c);

    a->height = 1 + max(getHeight(T0), getHeight(T1));
    c->height = 1 + max(getHeight(T2), getHeight(T3));
    b->height =  1 + max(getHeight(a), getHeight(c));


    return b;
}

int nodeHeight(tree_ptr n) {
    if (n == NULL)
        return 0;
    return n->height;
}

void rebalance(tree_ptr node, tree_ptr tree) {

    while (node->parent != NULL) {
        node = node->parent;

        if (abs(nodeHeight(node->left) - nodeHeight(node->right)) > 1) {
            tree_ptr tallestChild = tallest(node);
            node = restructure(tallest(tallestChild), tallestChild, node);
        }
        node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
    }
}

void calculateHeight(tree_ptr node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    if (node->parent != NULL)
        calculateHeight(node->parent);
}

void insertToTree(Key_Type word, tree_ptr tree) {
    int compareVal = strcmp(tree->element, word);

    if (compareVal > 0) {
        if (tree -> left != NULL)
            insertToTree(word, tree->left);
        else {
            tree -> left = newNode(word, tree, NULL, NULL);
            calculateHeight(tree->left);

            if (mode == 1)
                rebalance(tree, tree);
        }
    }

    if (compareVal < 0) {
        if (tree -> right != NULL)
            insertToTree(word, tree->right);
        else {
            tree -> right = newNode(word, tree, NULL, NULL);
            calculateHeight(tree->right);

            if (mode == 1)
                rebalance(tree->right, tree);
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
    //printf("word: |%s|, element: |%s|\n, compvak: %d", word, tree->element);
    numStringComps++;

    if (compareVal > 0) {
        if (tree->left != NULL)
            return findInTree(word, tree->left);
        else
            return FALSE;
    }

    if (compareVal < 0) {
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
    fflush(stdout);
    print_tree_in_order(tree->right);
}

void print_table(Table table) {
    print_tree_in_order(table->head);
}

void print_stats (Table table) {
    printf("Avarage #String compares in find: %d\n", averageStringComps);
    printf("Height: %d\n", table->head->height);

}
