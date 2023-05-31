#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <conio.h>
#define V 21
#define H 75
#define N 100

typedef struct
{
    int x, y; // initial position
    int movX, movY;
    char image;
} Snake;

typedef struct
{
    int x, y;
} Fruit;

Snake snake[N]; // maximum size
Fruit fruit;

void initialize(int *size, char map[V][H]);
void displayIntro(char map[V][H]);
void setIntroData(char map[V][H], int *size);
void gameLoop(char map[V][H], int size);
void getUserInput(char map[V][H], int *size, int *isDead);
void updateGame(char map[V][H], int size);
void setIntroData2(char map[V][H], int size);

void gotoxy(int x, int y);

void showMap(char map[V][H]);

int main()
{
    int size;
    char map[V][H];

    initialize(&size, map);
    showMap(map);
    system("pause");
    gameLoop(map, size);

    system("pause");
    return 0;
}

void initialize(int *size, char map[V][H])
{
    int i;

    // Set snake head initial position
    snake[0].x = 32;
    snake[0].y = 10;
    *size = 4;

    srand(time(NULL));

    fruit.x = rand() % (H - 2) + 1;
    fruit.y = rand() % (V - 2) + 1;

    for (i = 0; i < *size; i++)
    {
        snake[i].movX = 1;
        snake[i].movY = 0;
    }

    displayIntro(map);
    setIntroData(map, size);
}

void showMap(char map[V][H])
{
    int i, j;

    for (i = 0; i < V; i++)
    {
        for (j = 0; j < H; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void displayIntro(char map[V][H])
{
    int i, j;

    for (i = 0; i < V; i++)
    {
        for (j = 0; j < H; j++)
        {
            if (i == 0 || i == V - 1)
            {
                map[i][j] = '-';
            }
            else if (j == 0 || j == H - 1)
            {
                map[i][j] = '|';
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }
}

void setIntroData(char map[V][H], int *size)
{
    int i;

    for (i = 1; i < *size; i++)
    {
        snake[i].x = snake[i - 1].x - 1;
        snake[i].y = snake[i - 1].y;
        snake[i].image = 'X';
    }
    snake[0].image = 'O';

    for (i = 0; i < *size; i++)
    {
        map[snake[i].y][snake[i].x] = snake[i].image;
    }

    map[fruit.y][fruit.x] = 'M';
}

void gameLoop(char map[V][H], int size)
{
    int isDead = 0;

    do
    {
        gotoxy(0, 0);
        showMap(map);
        getUserInput(map, &size, &isDead);
        updateGame(map, size);
    } while (isDead == 0);
}

void getUserInput(char map[V][H], int *size, int *isDead)
{
    int i;
    char key;

    if (snake[0].x == 0 || snake[0].x == H - 1 || snake[0].y == 0 || snake[0].y == V - 1)
    {
        *isDead = 1;
    }

    for (i = 1; i < *size && *isDead == 0; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            *isDead = 1;
        }
    }

    if (snake[0].x == fruit.x && snake[0].y == fruit.y)
    {
        *size += 1;
        snake[*size - 1].image = 'X';
        fruit.x = rand() % (H - 2) + 1;
        fruit.y = rand() % (V - 2) + 1;
    }

    if (*isDead == 0)
    {
        if (kbhit() == 1)
        {
            key = getch();

            if (key == 's' && snake[0].movY != -1)
            {
                snake[0].movX = 0;
                snake[0].movY = 1;
            }
            else if (key == 'w' && snake[0].movY != 1)
            {
                snake[0].movX = 0;
                snake[0].movY = -1;
            }
            else if (key == 'a' && snake[0].movX != 1)
            {
                snake[0].movX = -1;
                snake[0].movY = 0;
            }
            else if (key == 'd' && snake[0].movX != -1)
            {
                snake[0].movX = 1;
                snake[0].movY = 0;
            }
        }
    }
}

void updateGame(char map[V][H], int size)
{
    displayIntro(map);
    setIntroData2(map, size);
}

void setIntroData2(char map[V][H], int size)
{
    int i;

    for (i = size - 1; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    snake[0].x += snake[0].movX;
    snake[0].y += snake[0].movY;

    for (i = 0; i < size; i++)
    {
        map[snake[i].y][snake[i].x] = snake[i].image;
    }

    map[fruit.y][fruit.x] = 'M';
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
