#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void toLowerCase ( char *p ) {
    for (int i = 0; i < strlen(p); i++) {
        p[i] = tolower(p[i]);
    }
}
int isYes(char *txt) {
    toLowerCase(txt);
    if (strcmp(txt, "yes") == 0)
        return true;
    if (strcmp(txt, "ye") == 0)
        return true;
    if (strcmp(txt, "correct") == 0)
        return true;
    if (strcmp(txt, "yup") == 0)
        return true;
    if (strcmp(txt, "oui") == 0)
        return true;
    if (strcmp(txt, "ya") == 0)
        return true;
    return false;
}

#define BUFFER_SIZE 100

char *newInput;
char *getRawInput() {
    char *data = malloc(BUFFER_SIZE);
    fgets(data, BUFFER_SIZE, stdin);

    newInput = malloc(strlen(data) + 1);
    sscanf(data, "%[^\n]", newInput); // Extract text before newline character
    free(data);
    return newInput;
}

char * formatQuestion(char *question) {
    question[0] = toupper(question[0]);

    // Check for question mark
    if(question[(int)strlen(question) - 1] != '?'
        && strlen(question) < BUFFER_SIZE)
        question[(int)strlen(question)] = '?';
    return  question;
}

char * getPreWord(char *in) {
    switch (tolower(in[0])) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return "an";
    }
    return "a";
}

char * formatAnswer(char *in) {
    in[0] = tolower(in[0]);
    if (in[0] == 'a' && in[1] == ' ') {
        char *input = malloc(strlen(in) - 1);
        sscanf(in, "a %s", input);
        input[0] = tolower(input[0]);
        free(in);
        return input;
    } else if (in[0] == 'a' && in[1] == 'n' && in[2] == ' ') {
        char *input = malloc(strlen(in) - 1);
        sscanf(in, "an %s", input);
        free(in);
        input[0] = tolower(input[0]);
        return input;
    }
    return in;
}

void makeGuess(Node *node) {
    printf("Is it %s %s?\n>", getPreWord(node->data.name), node->data.name);
    char *answer = getRawInput();
    if (isYes(answer))
        printf("Yeeey I won!!\n");
    else {
        printf("What were you thinking of?\n");
        char *correctAns = formatAnswer(getRawInput());

        printf("Can you give me a question about %s %s to differentiate between"
               " it, and %s %s?\n", getPreWord(correctAns),
                                    correctAns,
                                    getPreWord(node->data.name),
                                    node->data.name);

        char *newQuestion = formatQuestion(getRawInput());
        printf("What is the answer for %s?\n", correctAns);
        char *newAnswer = getRawInput();

        char *copyGuess = (char *)malloc(strlen(node->data.name)+1);
        strcpy(copyGuess, node->data.name);

        Node *userObj = createBaseNode(correctAns);
        Node *oldObj = createBaseNode(copyGuess);

        node->type = question;
        free(node->data.name);

        node->data.question = newQuestion;

        if (isYes(newAnswer)) {
            node->yes = userObj;
            node->no = oldObj;
        } else {
            node->yes = oldObj;
            node->no = userObj;
        }
        free(newAnswer);
    }
    free(answer);
}

Node * askQuestion(Node *node) {
    printf("%s\n>", node->data.question);
    char *answer = getRawInput();
    if (isYes(answer)) {
        free(answer);
        return node->yes;
    } else {
        free(answer);
        return node->no;
    }
}

void treePrintToFile(Node *root, FILE *outputStream) {
    if (root == NULL)
        return;
    else if (root->type == question) {
        fprintf(outputStream, "question:%s\n", root->data.question);
        treePrintToFile(root->yes, outputStream);
        treePrintToFile(root->no, outputStream);
    } else {
        fprintf(outputStream, "object:%s\n", root->data.name);
    }
}

void saveToFile(char *fileName, Node *root) {
    FILE *outputStream = fopen(fileName, "w");
    if (!outputStream) {
        fprintf(stderr, "can't open %s \n", fileName);
        exit(-1);
    }
    treePrintToFile(root, outputStream);
    fclose(outputStream);
}

char *input;
Node * treeReadFromFile(FILE *stream) {
    char data[BUFFER_SIZE];
    fgets(data, BUFFER_SIZE, stream);

    if (strcmp(data,"") == 0) {
        return NULL;
    }

    Node *ptr = malloc(sizeof(Node));

    char subString[8];
    // check if line starts with 'question:'
    sscanf(data, "%[^:]", subString);
    if (strcmp(subString, "question") == 0) { // Line is question
        input = malloc(strlen(data) - 6);
        sscanf(data, "%*[^:]:%[^\n]", input);
        ptr->type=question;
        ptr->data.question = input;
        ptr->yes = treeReadFromFile(stream);
        ptr->no = treeReadFromFile(stream);

    } else { // Line is object
        char subString[8];
        // check if line starts with 'object:'
        sscanf(data, "%[^:]", subString);
        if (strcmp(subString, "object") == 0) {
            input = malloc(strlen(data) - 6);
            sscanf(data, "%*[^:]:%[^\n]", input);
            free(ptr);
            ptr = createBaseNode(input);

        }
    }
    return ptr;

}

Node * loadFromFile(char *fileName) {
    FILE *inputStream = fopen(fileName, "r");
    if (!inputStream) {
        fprintf(stderr, "can't open %s \n", fileName);
        exit(-1);
    }
    Node *tree = treeReadFromFile(inputStream);
    fclose(inputStream);
    return tree;
}

void freeTree(Node *root) {
    if (root->yes == NULL) {
        free(root->data.name);
        free(root);
    }
    else {
        freeTree(root->yes);
        freeTree(root->no);

        free(root->data.question);
        free(root);
    }

}

// Returns true if the user wanted to end the game
int finishGame() {
    printf("Would you like to play again?\n>");
    char *answer = getRawInput();
    if (isYes(answer)) {
        free(answer);
        return false;
    } else {
        free(answer);
        return true;
    }
}

int main(int argc, char **argv) {
    Node *tree = loadFromFile("pangolinsTree.txt");
    //Node *tree = constructInitialTree();

    int finished = false;
    Node *currentNode = tree;
    while(!finished) {
        if (currentNode->type == object) {
            makeGuess(currentNode);
            currentNode = tree;
            finished = finishGame();
        }
        else {
            currentNode = askQuestion(currentNode);
        }
    }
    saveToFile("pangolinsTree.txt", tree);
    freeTree(tree);
    return 0;
}
