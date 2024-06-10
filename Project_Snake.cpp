#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20

int x, y, fruitX, fruitY;
int tailX[100], tailY[100];
int nTail;
int fruitCount;
int maxFruits = 0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;
enum eDirection lastDir;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
bool gameOver;

// Dimensions of the console
const int consoleWidth = 80;
const int consoleHeight = 25;

// Margins for centering the game
const int marginX = (consoleWidth - (WIDTH + 2)) / 2;
const int marginY = (consoleHeight - (HEIGHT + 4)) / 2;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void ShowCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void ClearScreen() {
    COORD topLeft = {0, 0};
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD length;
    GetConsoleScreenBufferInfo(console, &screen);
    length = screen.dwSize.X * screen.dwSize.Y;
    FillConsoleOutputCharacter(console, TEXT(' '), length, topLeft, &written);
    FillConsoleOutputAttribute(console, screen.wAttributes, length, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void SetConsoleSize(int width, int height) {
    _COORD coord;
    coord.X = width;
    coord.Y = height;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = height - 1;
    Rect.Right = width - 1;
    SetConsoleScreenBufferSize(console, coord);
    SetConsoleWindowInfo(console, TRUE, &Rect);
}

void Setup() {
    gameOver = false;
    dir = STOP;
    lastDir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    fruitCount = 0;
    nTail = 0;
}

void DrawBorders() {
    gotoxy(marginX, marginY);
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    for (int i = 0; i < HEIGHT; i++) {
        gotoxy(marginX, marginY + 1 + i);
        printf("#");
        gotoxy(marginX + WIDTH + 1, marginY + 1 + i);
        printf("#");
    }
    gotoxy(marginX, marginY + 1 + HEIGHT);
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
}

void DrawGame() {
    for (int i = 0; i < HEIGHT; i++) {
        gotoxy(marginX + 1, marginY + 1 + i);
        for (int j = 0; j < WIDTH; j++) {
            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }
        }
    }

    gotoxy(marginX, marginY + HEIGHT + 2);
    printf("Fruits: %d", fruitCount);
    gotoxy(marginX + WIDTH - 7, marginY + HEIGHT + 2); // Ajusta esta línea para mover el récord a la derecha
    printf("Record: %d", maxFruits);
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (lastDir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (lastDir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (lastDir != DOWN) dir = UP;
            break;
        case 's':
            if (lastDir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    lastDir = dir;
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Colisión con paredes
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        gameOver = true;
    }

    // Colisión con el cuerpo
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // Comer la fruta
    if (x == fruitX && y == fruitY) {
        fruitCount++;
        if (fruitCount > maxFruits) {
            maxFruits = fruitCount;
        }
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
        tailX[nTail - 1] = tailX[nTail - 2];
        tailY[nTail - 1] = tailY[nTail - 2];
    }
}

void WelcomeScreen() {
    ClearScreen();
    printf("***********************************\n");
    printf("*        Bienvenido al juego      *\n");
    printf("*      Presiona cualquier tecla   *\n");
    printf("*          para comenzar          *\n");
    printf("***********************************\n");
    getch();
    ClearScreen();
}

void GameOverScreen() {
    ClearScreen();
    printf("***********************************\n");
    printf("*           Game Over             *\n");
    printf("*       Presiona 'Enter' para     *\n");
    printf("*            reiniciar              *\n");
    printf("***********************************\n");
    printf("Fruits: %d\n", fruitCount);
    printf("Record: %d\n", maxFruits);
    while (_getch() != 13);  // 13 es el código ASCII de la tecla 'Enter'
    ClearScreen();
}

int main() {
    SetConsoleSize(consoleWidth, consoleHeight); // Cambia el tamaño de la consola
    WelcomeScreen();
    HideCursor();
    Setup();
    DrawBorders();
    while (1) {
        if (gameOver) {
            ShowCursor();
            GameOverScreen();
            Setup();
            DrawBorders();
            HideCursor();
        }
        DrawGame();
        Input();
        Logic();
        Sleep(100); // sleep(10) for faster speed
    }
    return 0;
}
