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

    int leftHeight = node->left == NULL ? 0 : node->left->height;
    int rightHeight = node->right == NULL ? 0 : node->right->height;

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

Boolean equals(tree_ptr a, tree_ptr b) {
    if (a == NULL || b == NULL)
        return 0;

    return strcmp(a->element, b->element) == 0;
}

tree_ptr restructure(tree_ptr x, tree_ptr y, tree_ptr z) {
    //printf("Restruc:  %s %s %s\n", x->element, y->element, z->element);

    if (equals(z->right, y)) {
        if (equals(y->right, x)) {
        //    printf("(A), %s %s %s\n", x->element, y->element, z->element);
        //    fflush(stdout);
            // (a)
            z->right = y->left;
            y->left = z;

            if (z->parent != NULL) {
                if (strcmp(z->parent->left->element, z->element) == 0)
                    z->parent->left = y;
                else
                    z->parent->right = y;
            }

            z->height = 1 + maxNodes(z->left, z->right);
            x->height = 1 + maxNodes(x->left, x->right);
            y->height = 1 + maxNodes(y->left, y->right);


            setParent(y, z->parent);
            setParent(z, y);
            setParent(z->right, z);
            return y;
        }

        if (equals(y->left, x)) {
            //printf("(C), %s %s %s\n", x->element, y->element, z->element);
            // (c)
            z->right = x->left;
            y->left = x->right;

            x->left = z;
            x->right = y;

            z->height = 1 + maxNodes(z->left, z->right);
            y->height = 1 + maxNodes(y->left, y->right);
            x->height = 1 + maxNodes(x->left, x->right);

            if (z->parent != NULL) {
                if (strcmp(z->parent->left->element, z->element) == 0)
                    z->parent->left = x;
                else
                    z->parent->right = x;
            }

            setParent(x, z->parent);
            setParent(z, x);
            setParent(y, x);
            setParent(z->right, z);
            setParent(y->left, y);


            return x;
        }
    }

    if (equals(z->left, y)) {
        if (equals(y->left, x)) {
            //printf("(B), %s %s %s\n", x->element, y->element, z->element);
            // (b)
            z->left = y->right;
            y->right = z;

            if (z->parent != NULL) {
                if (equals(z->parent->left, z))
                    z->parent->left = y;
                else
                    z->parent->right = y;
            }

            z->height = 1 + maxNodes(z->left, z->right);
            x->height = 1 + maxNodes(x->left, x->right);
            y->height = 1 + maxNodes(y->left, y->right);

            setParent(y, z->parent);
            setParent(z, y);
            setParent(z->left, z);
            setParent(y->right, y);

            return y;
        }

        if (equals(y->right, x)) {
            //printf("(D), %s %s %s\n", x->element, y->element, z->element);
            // (d)
            y->right = x->left;
            z->left = x->right;

            x->right = z;
            x->left = y;

            if (z->parent != NULL) {
                if (equals(z->parent->left, z) == 0)
                    z->parent->left = x;
                else
                    z->parent->right = x;
            }

            z->height = 1 + maxNodes(z->left, z->right);
            y->height = 1 + maxNodes(y->left, y->right);
            x->height = 1 + maxNodes(x->left, x->right);

            setParent(x, z->parent);
            setParent(y, x);
            setParent(z, x);
            setParent(y->right, y);
            setParent(z->left, z);
            return x;
        }
    }

printf("SHOULN'T BE HERE");
    return NULL;


/*
        if (strcmp(y->right->element, x->element) == 0) { // (a)
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

        if (strcmp(y->right->element, x->element) == 0) { // (d)
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
        if (strcmp(z->parent->left->element, z->element) == 0)
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


    return b;*/
}

int nodeHeight(tree_ptr n) {
    if (n == NULL)
        return 0;
    return n->height;
}

void rebalance(tree_ptr node, Table t) {

    while (node->parent != NULL) {
        node = node->parent;

        if (abs(nodeHeight(node->left) - nodeHeight(node->right)) > 1) {
            tree_ptr  tallestChild = tallest(node);

            /*printf("Before Restructure ---\n");
            print_tree_in_order(node);fflush(stdout);*/

            node = restructure(tallest(tallestChild), tallestChild, node);

        /*    printf("After restructure, node=%s\n", node->element);
            print_tree_in_order(node);
            printf("---\n");
            fflush(stdout);*/
        }
    }
    t->head = node;
}

void calculateHeight(tree_ptr node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    if (node->parent != NULL)
        calculateHeight(node->parent);
}

void insertToTree(Key_Type word, tree_ptr tree, Table table) {

    int compareVal = strcmp(tree->element, word);

    if (compareVal > 0) {
        if (tree -> left != NULL)
            insertToTree(word, tree->left, table);
        else {
            tree -> left = newNode(word, tree, NULL, NULL);
            calculateHeight(tree->left);

            if (mode == 1)
                rebalance(tree->left, table);
        }
    }


    if (compareVal < 0) {
        if (tree -> right != NULL)
            insertToTree(word, tree->right, table);
        else {
            tree -> right = newNode(word, tree, NULL, NULL);
            calculateHeight(tree->right);

            if (mode == 1)
                rebalance(tree->right, table);
        }
    }
}

Table insert(Key_Type word, Table table) {
    // There isn't yet a root, so make this the root
    if (table->head == NULL) {
        table -> head = newNode(word, NULL, NULL, NULL);
    } else {
        insertToTree(word, table->head, table);
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



void print_stats (Table table) {
    printf("Avarage #String compares in find: %d\n", averageStringComps);
    printf("Height: %d\n", table->head->height);



}
