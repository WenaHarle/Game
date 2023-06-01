#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define V 20
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
void menu();

int main()
{
    int ukuran;
    char peta[V][H];
    menu();
    inisialisasi(&ukuran, peta);
    tampilkanPeta(peta);
    system("pause");
    perulanganPermainan(peta, ukuran);
    system("pause");
    clearTerminal();
    main();
}

void clearTerminal()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menu()
{

    printf(" ===========================================================================\n");
    printf(" ||                                                                       ||\n");
    printf(" ||                           SNAKE GAME                                  ||\n");
    printf(" ||                                                                       ||\n");
    printf(" ||                      __    __    __    __                             ||\n");
    printf(" ||                     /  \\  /  \\  /  \\  /  \\                            ||\n");
    printf(" ||____________________/  __\\/  __\\/  __\\/  __\\___________________________||\n");
    printf(" ||___________________/  /__/  /__/  /__/  /______________________________||\n");
    printf(" ||                   | / \\   / \\   / \\   / \\  \\____                      ||\n");
    printf(" ||                   |/   \\_/   \\_/   \\_/   \\    o \\                     ||\n");
    printf(" ||                                           \\_____/--<                  ||\n");
    printf(" ||                                                                       ||\n");
    printf(" ||                                                                       ||\n");
    printf(" ||                              Menu                                     ||\n");
    printf(" ||									  ||\n");
    printf(" ||                         -> 1. Play Game                               ||\n");
    printf(" ||                         -> 2. Intruksi                                ||\n");
    printf(" ||                         -> 3. Kredit                                  ||\n");
    printf(" ||                         -> 4. Exit                                    ||\n");
    printf(" ||				                                          ||\n");
    printf(" ||                                                                       ||\n");
    printf(" ===========================================================================\n");


    char input;
    input = getch();
    clearTerminal();

    if (input == '1') {
        clearTerminal();
    } else if (input == '2') {
    printf(" ============================================================================\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                               INSTRUKSI                                 ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||  - Gunakan tombol AWSD untuk mengontrol pergerakan ular.                ||\n");
    printf(" ||  - Tujuan permainan adalah memakan makanan dan memanjangkan ular.       ||\n");
    printf(" ||  - Jika ular menabrak dinding atau dirinya sendiri, permainan berakhir. ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ============================================================================\n");
    system("pause");
    clearTerminal();
    main();


    } else if (input == '3') {
       printf(" ============================================================================\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                                KREDIT                                   ||\n");
    printf(" ||                                                                         ||\n");
    printf(" || Game dikembangkan oleh:                                                 ||\n");
    printf(" ||  - Kelompok 1 Daspro Kelas C                                            ||\n");
    printf(" ||                                                                         ||\n");
    printf(" || Terima kasih kepada:                                                    ||\n");
    printf(" ||  - OpenAI atas menyediakan model ChatGPT yang membantu kami untuk       ||\n");
    printf(" ||    memprogram masterpiece ini                                           ||\n");
    printf(" ||  - GitHub atas menyediakan platform untuk berbagi kode.                 ||\n");
    printf(" ||                                                                         ||\n");
    printf(" ||                      _____ _ _   _    _       _                         || \n");
    printf(" ||                     / ____(_) | | |  | |     | |                        ||  \n");
    printf(" ||                    | |  __ _| |_| |__| |_   _| |__                      || \n");
    printf(" ||                    | | |_ | | __|  __  | | | | '_ \\                     || \n");
    printf(" ||                    | |__| | | |_| |  | | |_| | |_) |                    || \n");
    printf(" ||                     \\_____|_|\\__|_|  |_|\\__,_|_.__/                     || \n");
    printf(" ||                                                                         ||\n");
    printf(" ||     Code source game:    https://github.com/WenaHarle/Game              ||\n");
    printf(" ============================================================================\n");


    system("pause");
    clearTerminal();
    main();
    }

   else if (input == '4')
    {
       exit(0);
    }


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
