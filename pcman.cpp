#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
using namespace std;
void calculateScore();
void printScore();
void calculateLives();
void printLives();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
int ghostDirection();
bool ghostMovement();
bool ghost4MoveDown();
bool ghost4MoveLeft();
bool ghost4MoveUp();
bool ghost4MoveRight();
bool ghostMoveVertical();
bool ghostMoveHorizontal();
void ghost2MoveUp();
void ghost2MoveDown();
void ghost3MoveLeft();
void ghost3MoveRight();
bool ghost4MoveRandom();
bool move();
void loadMaze();
void loadNewMaze();
void resetMaze();
void printMaze();
bool isEnergizer();
int energizer_count = 0;
string energizerStatus = "Low_power";
void gotoxy(int x, int y);
int count = 0;
bool switch_flag = true;
char maze[24][71];
int tmp_count1 = 0;
int tmp_count2 = 0;
int pacmanX = 9;
int pacmanY = 31;
int score = 0;
int lives = 3;
int ghostX1 = 19;
int ghostY1 = 25;
int ghostX2 = 3;
int ghostY2 = 3;
int ghostX3 = 22;
int ghostY3 = 2;
int ghostX4 = 3;
int ghostY4 = 8;
string row_flag = "pass";
string col_flag = "pass";
void moveGhost();
char previousItem1 = ' ';
char previousItem2 = ' ';
char previousItem3 = ' ';
char previousItem4 = ' ';
main()
{
    loadMaze();
    system("CLS");
    printMaze();
    for (int i = lives; i != 0; i--)
    {
        bool gameRunning = true;
        while (gameRunning)
        {
            Sleep(100);
            gameRunning = ghostMovement();
            if (!gameRunning)
            {
                break;
            }
            gameRunning = ghostMoveVertical();
            if (!gameRunning)
            {
                break;
            }
            gameRunning = ghostMoveHorizontal();
            if (!gameRunning)
            {
                break;
            }
            gameRunning = move();
            if (GetAsyncKeyState(VK_LEFT))
            {
                movePacmanLeft();
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {
                movePacmanRight();
            }
            if (GetAsyncKeyState(VK_UP))
            {
                movePacmanUp();
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                movePacmanDown();
            }
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                cout << "gameover" << endl;
                gameRunning = false;
            }
            if(energizerStatus == "eaten"){
                energizer_count++;
                if(energizer_count == 30){
                    energizerStatus = "Low_power";
                }
            }
            gotoxy(0, 25);
            printScore();
            gotoxy(40, 25);
            printLives();
        }
        calculateLives();
        resetMaze();
    }
}
void calculateLives()
{
    lives = lives - 1;
}
void printLives()
{

    cout << "Lives: " << lives;
}
void calculateScore()
{
    score = score + 1;
}
void printScore()
{
    cout << "Score: " << score;
}
void loadNewMaze()
{
    string line = " ";
    int idx = 0;
    fstream file;
    file.open("newmaze.txt", ios::in);
    while (!file.eof())
    {
        getline(file, line);
        for (int a = 0; a < line.length(); a++)
        {
            maze[idx][a] = line[a];
        }
        idx++;
    }
    file.close();
}
void resetMaze()
{
    previousItem1 = ' ';
    previousItem2 = ' ';
    previousItem3 = ' ';
    previousItem4 = ' ';
    gotoxy(pacmanY, pacmanX);
    cout << " ";
    gotoxy(ghostY1, ghostX1);
    cout << " ";
    gotoxy(ghostY2, ghostX2);
    cout << " ";
    gotoxy(ghostY3, ghostX3);
    cout << " ";
    gotoxy(ghostY4, ghostX4);
    cout << " ";
    ghostX1 = 19;
    ghostY1 = 25;
    ghostX2 = 3;
    ghostY2 = 3;
    ghostX3 = 22;
    ghostY3 = 2;
    ghostX4 = 3;
    ghostY4 = 8;
    pacmanX = 9;
    pacmanY = 31;
    maze[pacmanX][pacmanY] = 'P';
    gotoxy(pacmanY, pacmanX);
    cout << "P";
    maze[ghostX1][ghostY1] = 'G';
    gotoxy(ghostY1, ghostX1);
    cout << "G";
    maze[ghostX2][ghostY2] = 'G';
    gotoxy(ghostY2, ghostX2);
    cout << "G";
    maze[ghostX3][ghostY3] = 'G';
    gotoxy(ghostY3, ghostX3);
    cout << "G";
    maze[ghostX4][ghostY4] = 'G';
    gotoxy(ghostY4, ghostX4);
    cout << "G";
}
void movePacmanLeft()
{
    if (maze[pacmanX][pacmanY - 1] == ' ' || maze[pacmanX][pacmanY - 1] ==
                                                 '.' || maze[pacmanX][pacmanY-1] == '+')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY - 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        else if(maze[pacmanX][pacmanY] == '+'){
            energizerStatus = "eaten";
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}
void movePacmanRight()
{
    if (maze[pacmanX][pacmanY + 1] == ' ' || maze[pacmanX][pacmanY + 1] == '.' || maze[pacmanX][pacmanY+1] == '+')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY + 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        else if(maze[pacmanX][pacmanY] == '+'){
            energizerStatus = "eaten";
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}
void movePacmanUp()
{
    if (maze[pacmanX - 1][pacmanY] == ' ' || maze[pacmanX - 1][pacmanY] == '.' || maze[pacmanX-1][pacmanY] == '+')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX - 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        else if(maze[pacmanX][pacmanY] == '+'){
            energizerStatus = "eaten";
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}
void movePacmanDown()
{
    if (maze[pacmanX + 1][pacmanY] == ' ' || maze[pacmanX + 1][pacmanY] == '.' || maze[pacmanX+1][pacmanY] == '+')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX + 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        else if(maze[pacmanX][pacmanY] == '+'){
            energizerStatus = "eaten";
        }
        maze[pacmanX][pacmanY] = 'P';
    }
}
int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

bool ghostMovement()
{
    int value = ghostDirection();
    if (value == 1)
    {
        if (maze[ghostX1][ghostY1 - 1] == ' ' || maze[ghostX1][ghostY1 - 1] == '.' || maze[ghostX1][ghostY1 - 1] == 'P')
        {
            maze[ghostX1][ghostY1] = previousItem1;
            gotoxy(ghostY1, ghostX1);
            cout << maze[ghostX1][ghostY1];
            ghostY1 = ghostY1 - 1;
            gotoxy(ghostY1, ghostX1);
            cout << "G";
            if(maze[ghostX1][ghostY1] != 'G')
            previousItem1 = maze[ghostX1][ghostY1];
            if (ghostX1 == pacmanX && ghostY1 == pacmanY && energizerStatus == "Low_power")
            {
                return 0;
            }
            maze[ghostX1][ghostY1] = 'G';
        }
    }
    else if (value == 2)
    {
        if (maze[ghostX1][ghostY1 + 1] == ' ' || maze[ghostX1][ghostY1 + 1] == '.' || maze[ghostX1][ghostY1 + 1] == 'P')
        {
            maze[ghostX1][ghostY1] = previousItem1;
            gotoxy(ghostY1, ghostX1);
            cout << maze[ghostX1][ghostY1];
            ghostY1 = ghostY1 + 1;
            gotoxy(ghostY1, ghostX1);
            cout << "G";
            if(maze[ghostX1][ghostY1] != 'G')
            previousItem1 = maze[ghostX1][ghostY1];
            if (ghostX1 == pacmanX && ghostY1 == pacmanY && energizerStatus == "Low_power")
            {
                return 0;
            }
            maze[ghostX1][ghostY1] = 'G';
        }
    }
    else if (value == 3)
    {
        if (maze[ghostX1 - 1][ghostY1] == ' ' || maze[ghostX1 - 1][ghostY1] == '.' || maze[ghostX1 - 1][ghostY1] == 'P')
        {
            maze[ghostX1][ghostY1] = previousItem1;
            gotoxy(ghostY1, ghostX1);
            cout << maze[ghostX1][ghostY1];
            ghostX1 = ghostX1 - 1;
            gotoxy(ghostY1, ghostX1);
            cout << "G";
            if(maze[ghostX1][ghostY1]!='G')
            previousItem1 = maze[ghostX1][ghostY1];
            if (ghostX1 == pacmanX && ghostY1 == pacmanY && energizerStatus == "Low_power")
            {
                return 0;
            }
            maze[ghostX1][ghostY1] = 'G';
        }
    }
    else if (value == 4)
    {
        if (maze[ghostX1 + 1][ghostY1] == ' ' || maze[ghostX1 + 1][ghostY1] == '.' || maze[ghostX1 + 1][ghostY1] == '.')
        {
            maze[ghostX1][ghostY1] = previousItem1;
            gotoxy(ghostY1, ghostX1);
            cout << maze[ghostX1][ghostY1];
            ghostX1 = ghostX1 + 1;
            gotoxy(ghostY1, ghostX1);
            cout << "G";
            if(maze[ghostX1][ghostY1] != 'G')
            previousItem1 = maze[ghostX1][ghostY1];
            if (ghostX1 == pacmanX && ghostY1 == pacmanY && energizerStatus == "Low_power")
            {
                return 0;
            }
            maze[ghostX1][ghostY1] = 'G';
        }
    }
    return 1;
}

bool ghost4MoveRight()
{
    maze[ghostX4][ghostY4] = previousItem4;
    gotoxy(ghostY4, ghostX4);
    cout << maze[ghostX4][ghostY4];
    ghostY4++;
    gotoxy(ghostY4, ghostX4);
    cout << "G";
    if(maze[ghostX4][ghostY4] != 'G')
    {previousItem4 = maze[ghostX4][ghostY4];}
    if (ghostX4 == pacmanX && ghostY4 == pacmanY && energizerStatus == "Low_power")
    {
        return 0;
    }
    maze[ghostX4][ghostY4] = 'G';
    return true;
}
bool ghost4MoveLeft()
{
    maze[ghostX4][ghostY4] = previousItem4;
    gotoxy(ghostY4, ghostX4);
    cout << maze[ghostX4][ghostY4];
    ghostY4--;
    gotoxy(ghostY4, ghostX4);
    cout << "G";
    if(maze[ghostX4][ghostY4]!='G')
    {previousItem4 = maze[ghostX4][ghostY4];}
    if (ghostX4 == pacmanX && ghostY4 == pacmanY && energizerStatus == "Low_power")
    {
        return 0;
    }
    maze[ghostX4][ghostY4] = 'G';
    return true;
}
bool ghost4MoveUp()
{
    maze[ghostX4][ghostY4] = previousItem4;
    gotoxy(ghostY4, ghostX4);
    cout << maze[ghostX4][ghostY4];
    ghostX4--;
    gotoxy(ghostY4, ghostX4);
    cout << "G";
    if(maze[ghostX4][ghostY4] != 'G')
    {previousItem4 = maze[ghostX4][ghostY4];}
    if (ghostX4 == pacmanX && ghostY4 == pacmanY && energizerStatus == "Low_power") 
    {
        return 0;
    }
    maze[ghostX4][ghostY4] = 'G';
    return true;
}
bool ghost4MoveDown()
{
    maze[ghostX4][ghostY4] = previousItem4;
    gotoxy(ghostY4, ghostX4);
    cout << maze[ghostX4][ghostY4];
    ghostX4++;
    gotoxy(ghostY4, ghostX4);
    cout << "G";
    if(maze[ghostX4][ghostY4] != 'G')
  {  previousItem4 = maze[ghostX4][ghostY4];}
    if (ghostX4 == pacmanX && ghostY4 == pacmanY && energizerStatus == "Low_power")
    {
        return 0;
    }
    maze[ghostX4][ghostY4] = 'G';
    return true;
}
bool move()
{
    bool flag1 = false;
    bool flag2 = false;
    bool flag = true;
    if (switch_flag && count == 0)
    {
        if (ghostX4 > pacmanX)
        {
            if (maze[ghostX4 - 1][ghostY4] != '|' && maze[ghostX4 - 1][ghostY4] != '#' && maze[ghostX4 - 1][ghostY4] != '%')
            {
                flag = ghost4MoveUp();
                col_flag = "pass";
            }
            else
            {
                col_flag = "stuck";
            }
        }
        else if (ghostX4 < pacmanX)
        {
            if (maze[ghostX4 + 1][pacmanX] != '#' && maze[ghostX4 + 1][ghostY4] != '|' && maze[ghostX4 + 1][ghostY4] != '%')
            {
                flag = ghost4MoveDown();
                col_flag = "pass";
            }
            else
            {
                col_flag = "stuck";
            }
        }
        else
        {
            flag1 = true;
        }

        switch_flag = false;
    }
    else if (!switch_flag && count == 0)
    {
        if (ghostY4 > pacmanY)
        {
            if (maze[ghostX4][ghostY4 - 1] != '#' && maze[ghostX4][ghostY4 - 1] != '|' && maze[ghostX4][ghostY4 - 1] != '%')
            {
                flag = ghost4MoveLeft();
                row_flag = "pass";
            }
            else
            {
                row_flag = "stuck";
            }
        }
        else if (ghostY4 < pacmanY)
        {
            if (maze[ghostX4][ghostY4 + 1] != '#' && maze[ghostX4][ghostY4 + 1] != '|' && maze[ghostX4][ghostY4 + 1] != '%')
            {
                flag = ghost4MoveRight();
                row_flag = "pass";
            }
            else
            {
                row_flag = "stuck";
            }
        }
        else
        {
            flag2 = true;
        }
        switch_flag = true;
    }
    else if (flag1 == true && row_flag == "stuck" || flag2 == true && col_flag == "stuck")
    {
        flag = ghost4MoveRandom();
        count++;
        if (count == 10)
        {
            count = 0;
        }
    }
    return flag;
}

void loadMaze()
{
    string line;
    int idx = 0;
    fstream file;
    file.open("maze.txt", ios::in);
    while (!file.eof())
    {
        getline(file, line);
        for (int i = 0; i < line.length(); i++)
        {
            maze[idx][i] = line[i];
        }
        idx++;
    }
    file.close();
}
void printMaze()
{
    for (int row = 0; row < 24; row++)
    {
        for (int col = 0; col < 71; col++)
        {
            cout << maze[row][col];
        }
        cout << endl;
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
bool ghostMoveVertical()

{
    if (tmp_count1 < 21)
    {
        if (maze[ghostX2 - 2][ghostY2] == '#' || maze[ghostX2 - 2][ghostY2] == '%' || maze[ghostX2 - 2][ghostY2] == '|')
        {
            tmp_count1 = 21;
        }
        ghost2MoveUp();
    }
    else
    {
        if (maze[ghostX2 + 2][ghostY2] == '#' || maze[ghostX2 + 2][ghostY2] == '|' || maze[ghostX2 + 2][ghostY2] == '%')
        {
            tmp_count1 = 0;
        }
        ghost2MoveDown();
    }
    if (ghostX2 == pacmanX && ghostY2 == pacmanY && energizerStatus == "Low_power")
    {
        return false;
    }
    return true;
}
bool ghostMoveHorizontal()
{
    if (tmp_count2 < 68)
    {
        if (maze[ghostX3][ghostY3 + 2] == '#' || maze[ghostX3][ghostY3 + 2] == '%' || maze[ghostX3][ghostY3 + 2] == '|')
        {
            tmp_count2 = 69;
        }
        ghost3MoveRight();
    }
    else
    {
        if (maze[ghostX3][ghostY3 - 2] == '#' || maze[ghostX3][ghostY3 - 2] == '|' || maze[ghostX3][ghostY3 - 2] == '%')
        {
            tmp_count2 = 0;
        }
        ghost3MoveLeft();
    }
    if (ghostX3 == pacmanX && ghostY3 == pacmanY && energizerStatus == "Low_power")
    {
        return false;
    }
    return true;
}

void ghost2MoveUp()
{
    maze[ghostX2][ghostY2] = previousItem2;
    gotoxy(ghostY2, ghostX2);
    cout << maze[ghostX2][ghostY2];
    ghostX2--;
    gotoxy(ghostY2, ghostX2);
    cout << "G";
    if (maze[ghostX2][ghostY2] != 'G')
    {
        previousItem2 = maze[ghostX2][ghostY2];
    }
    maze[ghostX2][ghostY2] = 'G';
}
void ghost2MoveDown()
{
    maze[ghostX2][ghostY2] = previousItem2;
    gotoxy(ghostY2, ghostX2);
    cout << maze[ghostX2][ghostY2];
    ghostX2++;
    gotoxy(ghostY2, ghostX2);
    cout << "G";
    if (maze[ghostX2][ghostY2] != 'G')
    {
        previousItem2 = maze[ghostX2][ghostY2];
    }
    maze[ghostX2][ghostY2] = 'G';
}
void ghost3MoveLeft()
{
    maze[ghostX3][ghostY3] = previousItem3;
    gotoxy(ghostY3, ghostX3);
    cout << maze[ghostX3][ghostY3];
    ghostY3--;
    gotoxy(ghostY3, ghostX3);
    cout << "G";
    if (maze[ghostX3][ghostY3] != 'G')
    {
        previousItem3 = maze[ghostX3][ghostY3];
    }
    maze[ghostX3][ghostY3] = 'G';
}
void ghost3MoveRight()
{
    maze[ghostX3][ghostY3] = previousItem3;
    gotoxy(ghostY3, ghostX3);
    cout << maze[ghostX3][ghostY3];
    ghostY3++;
    gotoxy(ghostY3, ghostX3);
    cout << "G";
    if (maze[ghostX3][ghostY3] != 'G')
    {
        previousItem3 = maze[ghostX3][ghostY3];
    }
    maze[ghostX3][ghostY3] = 'G';
}
bool ghost4MoveRandom()
{
    int value = ghostDirection();
    if (value == 1)
    {
        if (maze[ghostX4][ghostY4 - 1] == ' ' || maze[ghostX4][ghostY4 - 1] == '.' || maze[ghostX4][ghostY4 - 1] == 'P')
        {
            maze[ghostX4][ghostY4] = previousItem4;
            gotoxy(ghostY4, ghostX4);
            cout << maze[ghostX4][ghostY4];
            ghostY4 = ghostY4 - 1;
            gotoxy(ghostY4, ghostX4);
            cout << "G";
            previousItem4 = maze[ghostX4][ghostY4];
            if (ghostX4 == pacmanX && ghostY4 == pacmanY && energizerStatus == "Low_power")
            {
                return 0;
            }
            maze[ghostX4][ghostY4] = 'G';
        }
    }
    else if (value == 2)
    {
        if (maze[ghostX4][ghostY4 + 1] == ' ' || maze[ghostX4][ghostY4 + 1] == '.' || maze[ghostX4][ghostY4 + 1] == 'P')
        {
            maze[ghostX4][ghostY4] = previousItem4;
            gotoxy(ghostY4, ghostX4);
            cout << maze[ghostX4][ghostY4];
            ghostY4 = ghostY4 + 1;
            gotoxy(ghostY4, ghostX4);
            cout << "G";
            previousItem4 = maze[ghostX4][ghostY4];
            if (ghostX4 == pacmanX && ghostY4 == pacmanY && energizerStatus == "Low_power")
            {
                return 0;
            }
            maze[ghostX4][ghostY4] = 'G';
        }
    }
    else if (value == 3)
    {
        if (maze[ghostX4 - 1][ghostY4] == ' ' || maze[ghostX4 - 1][ghostY4] == '.' || maze[ghostX4 - 1][ghostY4] == 'P')
        {
            maze[ghostX4][ghostY4] = previousItem4;
            gotoxy(ghostY4, ghostX4);
            cout << maze[ghostX4][ghostY4];
            ghostX4 = ghostX4 - 1;
            gotoxy(ghostY4, ghostX4);
            cout << "G";
            previousItem4 = maze[ghostX4][ghostY4];
            if (ghostX4 == pacmanX && ghostY4 == pacmanY && energizerStatus == "Low_power")
            {
                return 0;
            }
            maze[ghostX4][ghostY4] = 'G';
        }
    }
    else if (value == 4)
    {
        if (maze[ghostX4 + 1][ghostY4] == ' ' || maze[ghostX4 + 1][ghostY4] == '.' || maze[ghostX4 + 1][ghostY4] == '.')
        {
            maze[ghostX4][ghostY4] = previousItem4;
            gotoxy(ghostY4, ghostX4);
            cout << maze[ghostX4][ghostY4];
            ghostX4 = ghostX4 + 1;
            gotoxy(ghostY4, ghostX4);
            cout << "G";
            previousItem4 = maze[ghostX4][ghostY4];
            if (ghostX4 == pacmanX && ghostY4 == pacmanY && energizerStatus == "Low_power")
            {
                return 0;
            }
            maze[ghostX4][ghostY4] = 'G';
        }
    }
    return 1;
}


