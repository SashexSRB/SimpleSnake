#include <iostream>
#include <ncurses.h>

using namespace std;

bool gameOver;
const int width = 60;
const int height = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void setup() {
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void draw() {
    clear();

    for (int i = 0; i < width + 2; i++) {
        mvaddch(0, i, '#');
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 2; j++) {
            if (j == 0 || j == width + 1) {
                mvaddch(i + 1, j, '#');
            } else if (i == y && j == x) {
                mvaddch(i + 1, j, 'O');
            } else if (i == fruitY && j == fruitX) {
                mvaddch(i + 1, j, 'F');
            } else {
                bool printTail = false;
                for(int k = 0; k < nTail; k++) {
                    if(tailX[k]==j && tailY[k]==i) {
                        mvaddch(i+1, j, 'o');
                        printTail = true;
                        break;
                    }
                }
                if(!printTail) {
                    mvaddch(i+1, j, ' ');
                }
            }
        }
    }

    for (int i = 0; i < width + 2; i++) {
        mvaddch(height + 1, i, '#');
    }

    mvprintw(height + 3, 0, "Score: %d", score);

    refresh();
}
void input() {
    int ch = getch();
    switch(ch) {
        case 'a':
            dir = LEFT; 
            break;
        case 'd':
            dir = RIGHT; 
            break;
        case 'w':
            dir = UP; 
            break;
        case 's':
            dir = DOWN; 
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            break;
    }
}
void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;

    for(int i=1; i<nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir) {
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

    /*if (x>width || x<0 || y>height || y<0) {
        gameOver = true;
    } omit gameOver if head hits border, disabled by default.*/

    if(x>=width) x=0; else if (x<0) x=width-1;
    if(y>=height) y=0; else if (y<0) y=height-1;

    if (x==fruitX && y==fruitY) {
        score+=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);

    setup();
    while(!gameOver) {
        draw();
        input();
        logic();
        napms(100);
    }
    endwin();
    return 0;
}