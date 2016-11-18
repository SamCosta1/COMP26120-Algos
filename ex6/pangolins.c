#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    question,
    object
} nodeType;

#define true 1
#define false 0

typedef struct node Node;

struct node {
    nodeType type;

    union {
        char *question;
        char *name;
    } data;

    Node *yes;
    Node *no;
};

void nodePrint(Node *node) {

    printf("Object: %s \nQuestion: %s \n", node->type == object ?
                                                             node->data.name
                                                             : "[-]",
                                           node->type == question ?
                                                             node->data.question
                                                             : "[-]");
    if (node->yes != NULL) {
        printf("Yes: %s\n", node->yes->type == object ? node->yes->data.name :
                                                       "[OBJ]");
        printf("No: %s\n", node->no->type == object ? node->no->data.name :
                                                       "[OBJ]");
    }
}

void treePrint(Node *root) {
    if (root == NULL)
        return;

    if (root->type == question) {
        printf("%s\n", root->data.question);
        treePrint(root->yes);
        treePrint(root->no);
    } else {
        printf("%s\n", root->data.name);
    }

}

Node * createBaseNode(char *name) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->type = object;
    new->yes = NULL;
    new->no = NULL;
    new->data.name = name;

    return new;
}

Node * createTreeNode(char *query, Node *yes, Node*no) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->type = question;
    new->yes = yes;
    new->no = no;
    new->data.question = query;

    return new;
}


Node * constructInitialTree() {
    Node *pizza = createBaseNode("pizza");
    Node *pangolin = createBaseNode("pangolin");
    Node *globalWarming = createBaseNode("global warning");
    Node *yeti = createBaseNode("yeti");

    Node *eat = createTreeNode("Can I eat it?", pizza, pangolin);
    Node *creature = createTreeNode("Is it a creature?", yeti, globalWarming);

    return createTreeNode("Is it real?", eat, creature);
}

int isYes(char *txt) {
    return strcmp(txt, "yes") == 0 ? true : false;
}

#define buffer_size 100

char *data;
char *getRawInput() {
    data = malloc(buffer_size);
    fgets(data, buffer_size, stdin);
    sscanf(data, "%[^\n]", data); // Extract text before newline character
    return data;
}

void makeGuess(Node *node) {
    printf("Is it a %s?\n>", node->data.name);

    if (isYes(getRawInput()))
        printf("Yeeey I won!!\n");
    else {
        printf("What were you thinking of?\n");
        char *userAns = getRawInput();
        printf("Can you giveme a question about a %s to differentiate between"
               " it, and a %s?\n", userAns, node->data.name);
        char *newQuestion = getRawInput();
        printf("What is the answer for %s?\n", userAns);
        char *newAnswer = getRawInput();

        char *copyGuess = (char *)malloc(strlen(node->data.name));
        strcpy(copyGuess, node->data.name);

        Node *userObj = createBaseNode(userAns);
        Node *oldObj = createBaseNode(copyGuess);

        node->type = question;
        node->data.question = newQuestion;

        if (isYes(newAnswer)) {
            node->yes = userObj;
            node->no = oldObj;
        } else {
            node->yes = oldObj;
            node->no = userObj;
        }
    }
}

Node * askQuestion(Node *node) {
    printf("%s\n>", node->data.question);
    if (isYes(getRawInput())) {
        printf("yes\n");
        return node->yes;
    } else {
        return node->no;
    }
}

int main(int argc, char **argv) {
    Node *tree = constructInitialTree();

    int finished = false;
    Node *currentNode = tree;
    while(!finished) {
        if (currentNode->type == object) {
            makeGuess(currentNode);
            currentNode = tree;//finished = true;
        }
        else {
            currentNode = askQuestion(currentNode);
        }
    }
}
