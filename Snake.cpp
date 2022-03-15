#include <iostream>
#include <string>
#include <winuser.h>
using namespace std;
const int boardSize = 20;
   
class Point{
    public:
    int x;
    int y;
    
    Point(){
        x = 0;
        y = 0;
    }

    Point(int xPos, int yPos){
        x = xPos;
        y = yPos;
    }
};

class Snake {
    public:

    int length;
    Point head;
    Point tail[boardSize*boardSize];
    Point apple;
    int direction;

    Snake(){
        length = 5;
        direction = 2;
        head = Point(boardSize/2, boardSize/2);
        tail[0] = head;
        apple = Point(rand() % boardSize, rand() % boardSize);
        for(int i = 1; i < this->length; i++){
            tail[i] = Point(head.x + i, head.y);
        } 
    }


    void move(){
        switch(this->direction){
            case 0:
                this->head.x = this->head.x + 1;
                this->tail[0].x++;
                break;
            
            case 1:
                this->head.x = this->head.x - 1;
                this->tail[0].x--;
                break;
            
            case 2:
                this->head.y = this->head.y + 1;
                this->tail[0].y++;
                break;

            case 3:
                this->head.y = this->head.y - 1;
                this->tail[0].y--;
                break;
        }

        for(int i = this->length; i > 0; i--){
            this->tail[i].x = this->tail[i-1].x;
            this->tail[i].y = this->tail[i-1].y;
            cout << this->tail[i].x;
            cout << this->tail[i].y;
        }
    }

    void generateApple(){
        int randX = (rand() % boardSize);
        int randY = (rand() % boardSize);

        while(isOnSnake(randX, randY)){
            randX = (rand() % boardSize);
            randY = (rand() % boardSize);
        }
        this->apple.x = randX;
        this->apple.y = randY;
    }

    bool isColiding(){
        if(this->head.x <= 0 || this->head.x >= boardSize || this->head.y <= 0 || this->head.y >= boardSize){
            return true;
        }           

        for(int i = 2; i < this->length; i++){
            if(this->tail[i].x == this->head.x && this->tail[i].y == this->head.y){
                return true;
            }
        }
        return false;
    }

    bool isOnSnake(int x, int y){
        for(int i = 1; i < this->length; i++)
        {
            if(this->tail[i].x == x && this->tail[i].y == y){
                return true;
            }
        }
        return false;
    }

    bool isOnApple(){
        return this->head.x == this->apple.x && this->head.y == this->apple.y;
    }
};


void printBoard(Snake s){
    char board[boardSize][boardSize];

    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            board[i][j] = ' ';
        }
    }

    board[s.head.x][s.head.y] = 'O';
    for(int i = 0; i < s.length; i++){
        board[s.tail[i].x][s.tail[i].y] = 'O';
    }

    board[s.apple.x][s.apple.y] = 'A';

     for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
           cout << board[i][j];
        }
        cout << "\n";
    }
    cout << "\n====================\n====================\n";
}

int main()
{
    Snake snake = Snake(); 
    bool end = false;
    int score = 0;
    while(!end){                                                                           
        if(GetKeyState('D') & 0x8000)
        {
            snake.direction = 0;
        }
        else if(GetKeyState('A') & 0x8000)
        {
            snake.direction = 1;
        }
        else if(GetKeyState('W') & 0x8000)
        {
            snake.direction = 2;
        }
        else if(GetKeyState('S') & 0x8000)
        {
            snake.direction = 3;
        }
        snake.move();
        if(snake.isOnApple()){
            score++;
            snake.length++;
            snake.tail[snake.length] = Point(snake.tail[snake.length-1].x, snake.tail[snake.length - 1].y);
            snake.generateApple();    
        }
        printBoard(snake);
        if(snake.isColiding()){
            end = true;
        }
    }
}
