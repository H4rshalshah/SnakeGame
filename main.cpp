#include <iostream>
#include <conio.h>   // getch() aur kbhit() ke liye
#include <windows.h> // gotoxy() aur Sleep() ke liye
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
using namespace std;

#define MAX_LENGTH 1000 // Snake ki max length

// Directions define kar rahe hain
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;

// gotoxy function cursor ko x, y par le jaata hai
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Console screen ki width aur height nikalne ke liye
void initScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;
}

// Ek simple point structure - x aur y coordinates ke liye
struct Point
{
    int xCoord;
    int yCoord;
    Point() {}
    Point(int x, int y)
    {
        xCoord = x;
        yCoord = y;
    }
};

// Snake class
class Snake
{
    int length;
    char direction;

public:
    Point body[MAX_LENGTH]; // Snake ke sare body parts

    Snake(int x, int y)
    {
        length = 1;
        body[0] = Point(x, y); // Initial position
        direction = DIR_RIGHT; // Starting direction
    }

    int getLength()
    {
        return length;
    }

    // Direction change karne ka function
    void changeDirection(char newDirection)
    {
        if ((newDirection == DIR_UP && direction != DIR_DOWN) ||
            (newDirection == DIR_DOWN && direction != DIR_UP) ||
            (newDirection == DIR_LEFT && direction != DIR_RIGHT) ||
            (newDirection == DIR_RIGHT && direction != DIR_LEFT))
        {
            direction = newDirection;
        }
    }

    // Snake move karega aur agar food milta hai to lamba hoga
    bool move(Point food)
    {
        for (int i = length - 1; i > 0; i--)
        {
            body[i] = body[i - 1]; // Body ek step aage shift
        }

        switch (direction)
        {
        case DIR_UP:
            body[0].yCoord--;
            break;
        case DIR_DOWN:
            body[0].yCoord++;
            break;
        case DIR_RIGHT:
            body[0].xCoord++;
            break;
        case DIR_LEFT:
            body[0].xCoord--;
            break;
        }

        // Snake agar apne body se takraata hai to game over
        for (int i = 1; i < length; i++)
        {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord)
            {
                return false;
            }
        }

        // **NEW FEATURE:** Game Over if Snake touches the console window
        if (body[0].xCoord < 0 || body[0].xCoord >= consoleWidth ||
            body[0].yCoord < 0 || body[0].yCoord >= consoleHeight)
        {
            return false;
        }

        // Agar food mil gaya
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord)
        {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length++;
        }

        return true;
    }
};

// Board class - pura game yahin manage hota hai
class Board
{
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;

public:
    Board()
    {
        spawnFood();               // Starting food generate karo
        snake = new Snake(10, 10); // Snake starting point
        score = 0;
    }

    ~Board()
    {
        delete snake;
    }

    int getScore()
    {
        return score;
    }

    // Random food generate karna
    void spawnFood()
    {
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x, y);
    }

    // Score print karna
    void displayCurrentScore()
    {
        gotoxy(consoleWidth / 2, 0);
        cout << "Current Score : " << score;
    }

    // Draw karna screen pe
    void draw()
    {
        system("cls"); // Clear screen

        for (int i = 0; i < snake->getLength(); i++)
        {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }

        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;

        displayCurrentScore();
    }

    // Snake ka update har frame mein
    bool update()
    {
        bool isAlive = snake->move(food);
        if (!isAlive)
            return false;

        // Agar food khaya to score badhao aur naya food spawn karo
        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord)
        {
            score++;
            spawnFood();
        }

        return true;
    }

    // User ka input lena
    void getInput()
    {
        if (kbhit())
        {
            int key = getch();
            if (key == 'w' || key == 'W')
                snake->changeDirection(DIR_UP);
            else if (key == 'a' || key == 'A')
                snake->changeDirection(DIR_LEFT);
            else if (key == 's' || key == 'S')
                snake->changeDirection(DIR_DOWN);
            else if (key == 'd' || key == 'D')
                snake->changeDirection(DIR_RIGHT);
        }
    }
};

// Main function - Game loop start yahan se hota hai
int main()
{
    srand(time(0)); // Random seed for food spawn
    initScreen();   // Console size le lo
    Board *board = new Board();

    while (board->update())
    {
        board->getInput(); // Input lo
        board->draw();     // Draw karo screen pe
        Sleep(100);        // **Ensuring uniform speed for both directions**
    }

    cout << "\nGame Over!\n";
    cout << "Final Score is: " << board->getScore() << endl;
    return 0;
}
