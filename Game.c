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
    int x, y; // posisi awal
    int movX, movY;
    char image;
} Ular;

typedef struct
{
    int x, y;
} Buah;

Ular ular[N]; // ukuran maksimal
Buah buah;

void inisialisasi(int *ukuran, char peta[V][H]);
void tampilkanIntro(char peta[V][H]);
void aturDataIntro(char peta[V][H], int *ukuran);
void perulanganPermainan(char peta[V][H], int ukuran);
void ambilInputPengguna(char peta[V][H], int *ukuran, int *mati);
void perbaruiPermainan(char peta[V][H], int ukuran);
void aturDataIntro2(char peta[V][H], int ukuran);

void gotoxy(int x, int y);

void tampilkanPeta(char peta[V][H]);

int main()
{
    int ukuran;
    char peta[V][H];

    inisialisasi(&ukuran, peta);
    tampilkanPeta(peta);
    system("pause");
    perulanganPermainan(peta, ukuran);

    system("pause");
    return 0;
}

void inisialisasi(int *ukuran, char peta[V][H])
{
    int i;

    // Atur posisi awal kepala ular
    ular[0].x = 32;
    ular[0].y = 10;
    *ukuran = 4;

    srand(time(NULL));

    buah.x = rand() % (H - 2) + 1;
    buah.y = rand() % (V - 2) + 1;

    for (i = 0; i < *ukuran; i++)
    {
        ular[i].movX = 1;
        ular[i].movY = 0;
    }

    tampilkanIntro(peta);
    aturDataIntro(peta, ukuran);
}

void tampilkanPeta(char peta[V][H])
{
    int i, j;

    for (i = 0; i < V; i++)
    {
        for (j = 0; j < H; j++)
        {
            printf("%c", peta[i][j]);
        }
        printf("\n");
    }
}

void tampilkanIntro(char peta[V][H])
{
    int i, j;

    for (i = 0; i < V; i++)
    {
        for (j = 0; j < H; j++)
        {
            if (i == 0 || i == V - 1)
            {
                peta[i][j] = '-';
            }
            else if (j == 0 || j == H - 1)
            {
                peta[i][j] = '|';
            }
            else
            {
                peta[i][j] = ' ';
            }
        }
    }
}

void aturDataIntro(char peta[V][H], int *ukuran)
{
    int i;

    for (i = 1; i < *ukuran; i++)
    {
        ular[i].x = ular[i - 1].x - 1;
        ular[i].y = ular[i - 1].y;
        ular[i].image = 'X';
    }
    ular[0].image = 'O';

    for (i = 0; i < *ukuran; i++)
    {
        peta[ular[i].y][ular[i].x] = ular[i].image;
    }

    peta[buah.y][buah.x] = 'M';
}

void perulanganPermainan(char peta[V][H], int ukuran)
{
    int mati = 0;

    do
    {
        gotoxy(0, 0);
        tampilkanPeta(peta);
        ambilInputPengguna(peta, &ukuran, &mati);
        perbaruiPermainan(peta, ukuran);
    } while (mati == 0);
}

void ambilInputPengguna(char peta[V][H], int *ukuran, int *mati)
{
    int i;
    char key;

    if (ular[0].x == 0 || ular[0].x == H - 1 || ular[0].y == 0 || ular[0].y == V - 1)
    {
        *mati = 1;
    }

    for (i = 1; i < *ukuran && *mati == 0; i++)
    {
        if (ular[0].x == ular[i].x && ular[0].y == ular[i].y)
        {
            *mati = 1;
        }
    }

    if (ular[0].x == buah.x && ular[0].y == buah.y)
    {
        *ukuran += 1;
        ular[*ukuran - 1].image = 'X';
        buah.x = rand() % (H - 2) + 1;
        buah.y = rand() % (V - 2) + 1;
    }

    if (*mati == 0)
    {
        if (kbhit() == 1)
        {
            key = getch();

            if (key == 's' && ular[0].movY != -1)
            {
                ular[0].movX = 0;
                ular[0].movY = 1;
            }
            else if (key == 'w' && ular[0].movY != 1)
            {
                ular[0].movX = 0;
                ular[0].movY = -1;
            }
            else if (key == 'a' && ular[0].movX != 1)
            {
                ular[0].movX = -1;
                ular[0].movY = 0;
            }
            else if (key == 'd' && ular[0].movX != -1)
            {
                ular[0].movX = 1;
                ular[0].movY = 0;
            }
        }
    }
}

void perbaruiPermainan(char peta[V][H], int ukuran)
{
    tampilkanIntro(peta);
    aturDataIntro2(peta, ukuran);
}

void aturDataIntro2(char peta[V][H], int ukuran)
{
    int i;

    for (i = ukuran - 1; i > 0; i--)
    {
        ular[i].x = ular[i - 1].x;
        ular[i].y = ular[i - 1].y;
    }

    ular[0].x += ular[0].movX;
    ular[0].y += ular[0].movY;

    for (i = 0; i < ukuran; i++)
    {
        peta[ular[i].y][ular[i].x] = ular[i].image;
    }

    peta[buah.y][buah.x] = 'M';
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
