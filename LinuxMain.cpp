#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <bits/stdc++.h>
#include <unistd.h>

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering              // NOT MINE
        termios term;                                         


                                                                          /**
                                                           Linux (POSIX) implementation of _kbhit().
                                                          Morgan McGuire, morgan@cs.brown.edu
                                                          */
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

//////////////////////////////////////////////
//    Simple demo of _kbhit()



using namespace std;
deque <pair<int,int>> historyOfMoves;
char tab[10][10];
char buffer;
int xHead;
int yHead;
int direction;
void lose()
{
    system("clear");
    cout << "                \n";
    cout << "                \n";
    cout << "                \n";
    cout << "                \n";
    cout << "   Przegrales   \n";
    cout << "                \n";
    cout << "                \n";
    cout << "                \n";
    cout << "                \n";
}
void clear()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            tab[i][j] = '.';
    }
}
void draw()
{
    for (auto it: historyOfMoves)
    {
        tab[it.first][it.second] = 'X';
    }
    for (int i =0 ; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << tab[i][j];
        cout << "\n";
    }
}
void genFood()
{
    int X = rand() % 10;
    int Y = rand() % 10;
    while(tab[X][Y] != '.')
    {
        X = rand() % 10;
        Y = rand() % 10;
    }
    tab[X][Y] = 'o';
}
bool move()
{
    int lastX = xHead;
    int lastY = yHead;
    switch(direction)
    {
    case 0:
        yHead++;
        break;
    case 1:
        xHead++;
        break;
    case 2:
        yHead--;
        break;
    case -1:
        xHead--;
        break;
    }

    if (xHead == 10)
        xHead = 0;
    if (xHead == -1)
        xHead = 9;
    if (yHead == -1)
        yHead = 9;
    if (yHead == 10)
        yHead = 0;
    if (tab[xHead][yHead] == 'X')
    {
        lose();
        return true;
    }
    else if (tab[xHead][yHead] == 'o')
    {
        tab[xHead][yHead] = '.';
        genFood();
    }
    else
    {
        tab[historyOfMoves.front().first][historyOfMoves.front().second] = '.';
        historyOfMoves.pop_front();
        tab[xHead][yHead] = 'X';

    }
    historyOfMoves.push_back({xHead,yHead});
    return false;
}

int main()
{
    srand(time(NULL));
    clear();

    while(true)
    {
        clear();
        xHead = rand() % 10;
        yHead = rand() % 10;
        direction = 0;
        tab[xHead][yHead] = 'X';
        historyOfMoves.push_back({xHead,yHead});
        genFood();
        while(true)
        {
            system("clear");
            if (_kbhit())
            {
                switch(getchar_unlocked())
                {
                case 'w':
                    if (direction != 1)
                    {
                        direction = -1;
                    }
                    break;
                case 'd':
                    if (direction != 2)
                    {
                        direction = 0;
                    }
                    break;
                case 's':
                    if (direction != -1)
                    {
                        direction = 1;
                    }
                    break;
                case 'a':
                    if (direction != 0)
                    {
                        direction = 2;
                    }
                    break;
                }
            }
            if(move() == true)
            {
                return 0;
            }
            draw();
            usleep(400000);
        }
    }
    return 0;
}
