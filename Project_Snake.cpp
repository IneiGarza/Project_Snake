#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

#define Up 72
#define Down 80
#define Left 75
#define Right 77
#define ESC 27

int body[200][2];
int n = 1;
int height = 3;
int x = 10 , y = 12;
int dir = 3;
int fx = 30, fy = 15;
int vel = 100 , g = 1;
int score = 0;
bool isPaused = false;
char key;

void gotoxy(int x,int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void start_screen()
{
    char cover[18][71] =
    {
        "   SSSSSSSS  N       N  AAAAAAAAA  K     K   EEEEEEE  ",
        "  S         S N N     N  A       A  K    K    E         ",
        "  S          N  N    N  A       A  K   K     E         ",
        "   SSSSSSS   N   N   N  AAAAAAAAA  K  K      EEEEE     ",
        "           S  N    N  N  A       A  K K       E         ",
        "           S  N     N N  A       A  KK        E         ",
        "  SSSSSSSS   N      N N  A       A  K  K      EEEEEEE   ",
        "                                                        ",
        "                                                        ",
        "                                                        ",
        "                                                        ",
        "                                                        ",
        "                                                        ",
        "                                                        ",
        "                                                        ",
        "    SSSS                                              ",
        "   S    S                                             ",
        "    SSSS                                              "
    };

    for (int i = 0; i < 18; ++i)
    {
        printf("%s\n", cover[i]);
    }

    printf("\n\nPresiona cualquier tecla para comenzar...\n");
    _getch(); // Esperamos a que el usuario presione una tecla
    system("cls");
}

void draw()
{
    //Horizontal Line
    for (int i = 2 ; i < 78 ; i++)
    {
        gotoxy(i,3);    printf("%c",205);
        gotoxy(i,23);   printf("%c",205);
    }
    //Vertical Line
    for(int i = 4 ; i < 23 ; i++)
    {
        gotoxy(2,i);    printf("%c",186);
        gotoxy(77,i);    printf("%c",186);
    }
    //Corner
    gotoxy(2,3);    printf("%c",201);
    gotoxy(2,23);    printf("%c",200);
    gotoxy(77,3);    printf("%c",187);
    gotoxy(77,23);    printf("%c",188);
}

void save_position()
{
    body[n][0] = x;
    body[n][1] = y;
    n++;
    if(n == height) n = 1;
}

void draw_body()
{
    for(int i = 1 ; i < height ; i++)
    {
        gotoxy(body[i][0] , body[i][1]); printf("*");
    }
}

void remove_body()
{
    gotoxy(body[n][0] , body[n][1]); printf(" ");
}

void move_character()
{
    if (_kbhit())
    {
        key = _getch();
        switch (key)
        {
            case Up:
                if(dir != 2)
                dir=1;
                break;
            case Down:
                if(dir != 1)
                dir=2;
                break;
            case Left:
                if(dir != 3)
                dir=4;
                break;
            case Right:
                if(dir != 4)
                dir=3;
                break;
            case ESC:
                isPaused = true;
                break;
        }
    }
}

void change_vel()
{
    if(score == g*20)
    {
        vel -= 10;
        g++;
    }
}

void food()
{
    if (x == fx && y == fy)
    {
        fx = (rand()%73)+4;
        fy = (rand()%19)+4;

        height++;
        score +=10;
        gotoxy(fx,fy); printf("%c",250);

        change_vel();
    }
}

bool game_over()
{
    if ( y == 3  || y == 23 || x == 2 || x == 77) return false;
    for(int j = height -1 ; j > 0 ; j--)
    {
        if(body[j][0] == x && body[j][1] == y)
        {
            return false;
        }
    }
    return true;
}

void point ()
{
    gotoxy(3,1); printf("score %d",score);
}

void pause_menu()
{
    int option = 0;
    bool inMenu = true;
    char options[2][10] = { "Continuar", "Salir" };

    while (inMenu)
    {
        // Dibuja el marco del menú de pausa
        for (int i = 30; i <= 50; ++i)
        {
            gotoxy(i, 10); printf("%c", 205);
            gotoxy(i, 14); printf("%c", 205);
        }
        for (int i = 11; i <= 13; ++i)
        {
            gotoxy(30, i); printf("%c", 186);
            gotoxy(50, i); printf("%c", 186);
        }
        gotoxy(30, 10); printf("%c", 201);
        gotoxy(50, 10); printf("%c", 187);
        gotoxy(30, 14); printf("%c", 200);
        gotoxy(50, 14); printf("%c", 188);

        // Dibuja las opciones del menú
        for (int i = 0; i < 2; ++i)
        {
            gotoxy(35, 11 + i);
            if (i == option)
                printf("-> %s", options[i]);
            else
                printf("   %s", options[i]);
        }

        char ch = _getch();
        if (ch == Up && option > 0)
        {
            option--;
        }
        else if (ch == Down && option < 1)
        {
            option++;
        }
        else if (ch == '\r') // tecla Enter
        {
            if (option == 0)
            {
                inMenu = false;
                isPaused = false;
                // Limpia el menú de pausa
                for (int i = 10; i <= 14; ++i)
                {
                    gotoxy(30, i);
                    printf("                      ");
                }
                draw();
            }
            else if (option == 1)
            {
                exit(0);
            }
        }
    }
}

void game_over_screen()
{
    char gameOver[14][50] =
    {
        "  GGGGGG    AAAAA   M       M  EEEEEEE   ",
        " G         A     A  M M   M M  E         ",
        "G         A       A M  M M  M  EEEEE     ",
        "G   GGGG  AAAAAAAAA M   M   M  E         ",
        "G      G  A       A M       M  E         ",
        " G     G  A       A M       M  E         ",
        "  GGGGG   A       A M       M  EEEEEEE   ",
        "                                          ",
        "  OOOOO   V     V  EEEEEEE  RRRRRR        ",
        " O     O  V     V  E        R     R       ",
        "O       O V     V  EEEEE    RRRRRR        ",
        "O       O  V   V   E        R  R          ",
        " O     O    V V    E        R   R         ",
        "  OOOOO      V     EEEEEEE  R    R        "
    };

    system("cls");
    for (int i = 0; i < 14; ++i)
    {
        gotoxy(15, 7 + i); // Centro aproximado de la pantalla
        printf("%s\n", gameOver[i]);
    }

    printf("\n\nPresiona cualquier tecla para salir...\n");
    _getch(); // Esperamos a que el usuario presione una tecla
    exit(0);
}

int main()
{
    start_screen();
    draw();
    gotoxy(fx,fy); printf("%c",250);

    while (true)
    {
        if (isPaused)
        {
            pause_menu();
        }
        else
        {
            if (!game_over())
            {
                game_over_screen(); // Llama a la pantalla de fin de juego
            }
            remove_body();
            save_position();
            draw_body();
            food();
            point();
            move_character();
            move_character(); // Se agrega 2do para realizar movimientos bruscos

            if (dir == 1) y--;
            if (dir == 2) y++;
            if (dir == 3) x++;
            if (dir == 4) x--;

            Sleep(vel);
        }
    }
    return 0;
}

