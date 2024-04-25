#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printBoard(char **board, char *targetWord);
int getFileLength(char *fileName);
void gameLoop();
char *getTargetWord(int fileLen, char *fileName);
char **initBoard(int rows, int columns);

enum
{
    GREY = 0,
    YELLOW = 1,
    GREEN = 2

};

int main()
{
    srand(time(NULL));
    gameLoop();
    return 0;
}

void printBoard(char **board, char *targetWord)
{

    char *colors[] = {"\x1b[90m", "\x1b[93m", "\x1b[92m", "\x1b[0m"};

    char *box_top = "┌─";
    char *box_bottom = "└─";
    char *box_side = "│ ";

    for (int i = 0; i < 6; i++)
    {
        // print top of boxes
        for (int j = 0; j < 5; j++)
        {
            int color_index;
            if (board[i][j] == targetWord[j])
                color_index = GREEN;
            else if (strchr(targetWord, board[i][j]) != NULL)
                color_index = YELLOW;
            else
                color_index = GREY;

            printf("%s%s─┐%s ", colors[color_index], box_top, colors[3]);
        }
        printf("\n");

        // print middle
        for (int j = 0; j < 5; j++)
        {
            int color_index;
            if (board[i][j] == targetWord[j])
                color_index = GREEN;
            else if (strchr(targetWord, board[i][j]) != NULL)
                color_index = YELLOW;
            else
                color_index = GREY;

            printf("%s%s%c%s%s", colors[color_index], box_side, board[i][j], box_side, colors[3]);
        }
        // print bottom
        printf("\n");
        for (int j = 0; j < 5; j++)
        {
            int color_index;
            if (board[i][j] == targetWord[j])
                color_index = GREEN;
            else if (strchr(targetWord, board[i][j]) != NULL)
                color_index = YELLOW;
            else
                color_index = GREY;

            printf("%s%s─┘%s ", colors[color_index], box_bottom, colors[3]);
        }
        printf("\n");
    }
}

void gameLoop()
{
    int wins = 0;
    int losses = 0;
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y')
    {

        char *targetWord = getTargetWord(getFileLength("words.txt"), "words.txt");

        char **board = initBoard(6, 5);

        printBoard(board, targetWord);

        int correctGuess = 0;

        // Guess loop
        for (int i = 0; i < 6; i++)
        {
            char *guess = (char *)malloc(sizeof(char) * 5);
            printf("MAKE A GUESS: ");
            scanf("%s", guess);

            if (strcmp(guess, targetWord) == 0)
            {
                printf("YOU WIN\n");
                wins++;
                correctGuess = 1;
                break;
            }

            for (int j = 0; j < 5; j++)
            {
                board[i][j] = guess[j];
            }

            printBoard(board, targetWord);
        }

        if (!correctGuess)
        {
            printf("Sorry, you didn't guess the word. The word was: %s\n", targetWord);
            losses++;
        }

        free(targetWord);
        for (int i = 0; i < 6; i++)
        {
            free(board[i]);
        }
        free(board);

        printf("Wins: %d Losses: %d\n", wins, losses);
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);
    }

    printf("Thanks for playing!\n");
}

int getFileLength(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
        return 0;

    int count = 0;
    char c;
    while ((c = getc(fp)) != EOF)
    {
        if (c == '\n')
            count++;
    }

    fclose(fp);
    return count;
}

char *getTargetWord(int fileLen, char *fileName)
{

    int lineNumber = rand() % fileLen;

    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Error opening file.");
        return NULL;
    }

    fseek(fp, 0, SEEK_SET);

    char *line = NULL;
    size_t len = 0;
    size_t read;
    int currentLine = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (currentLine == lineNumber)
        {

            if (line[read - 1] == '\n')
                line[read - 1] = '\0';
            break;
        }
        currentLine++;
    }

    fclose(fp);
    return line;
}

char **initBoard(int rows, int columns)
{

    char **array = (char **)malloc(rows * sizeof(char *));
    if (array == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        array[i] = (char *)malloc(columns * sizeof(char));
        if (array[i] == NULL)
        {
            printf("Memory allocation failed!\n");

            for (int j = 0; j < i; j++)
            {
                free(array[j]);
            }

            free(array);
            return NULL;
        }

        for (int j = 0; j < columns; j++)
        {
            array[i][j] = ' ';
        }
    }

    return array;
}
