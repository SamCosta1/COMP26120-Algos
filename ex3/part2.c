#include <stdio.h>
#include <stdlib.h>

enum Square {
    black,
    white
};

// Generate board of given size
void generateBoard (int width, int length, int*** boardRef) {
    int i, j,
    isBlack = 1;

    if (boardRef == NULL) {
        printf("Something went wrong");
        exit(-1);
    }

    int **board = (int **)malloc(length * sizeof(int *));

    // Create 2D array
    for (i = 0; i < length; i++)
        board[i] = (int *)malloc(width * sizeof(int));

    // Populate with alteranting black and white
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++, isBlack = (isBlack + 1) % 2)
            board[i][j] = isBlack ? black : white;

        // Need to alternate once per row for boards of even widths
        if (width % 2 == 0)
            isBlack = (isBlack + 1) % 2;
    }

    *boardRef = board;
}

// Helper method for testing
void outputBoard(int width, int length, int** board) {
    int i,j;

    printf("Board of dimensions %d x %d\n", width,length);
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++)
            if (board[i][j] == black)
                printf("|||");
            else
                printf("   ");
        printf("\n");
    }
    printf("\n");

}

int main(int argc, char **argv) {
    int** board = NULL;
    int i;

    generateBoard(10,9, &board);
    outputBoard(10,9, board);
    for (i = 0; i < 9; i++)
        free(board[i]);
    free(board);

    generateBoard(10,20, &board);
    outputBoard(10,20, board);
    for (i = 0; i < 20; i++)
        free(board[i]);
    free(board);

    generateBoard(2,2, &board);
    outputBoard(2,2, board);
    for (i = 0; i < 2; i++)
        free(board[i]);
    free(board);

    generateBoard(7,7, &board);
    outputBoard(7,7, board);
    for (i = 0; i < 7; i++)
        free(board[i]);
    free(board);

    generateBoard(10,10, NULL);


    return 0;
}
