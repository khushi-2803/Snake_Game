#include<iostream>
#include<bits/stdc++.h>
#include<conio.h> //keyboard hit
#include<windows.h>//it will tell coordinate system(x,y)
using namespace std;

#define MAX_LENGTH 1000 //MACROS

//directions
const char DIR_UP='U';
const char DIR_DOWN='D';
const char DIR_LEFT='L';
const char DIR_RIGHT='R';

int consoleWidth, consoleHeight;


void initScreen(){ //initialising window for game
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE); //IT bring console handle..predefined fuction of windows header file
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi); //bring info of buffer(csbi)  and console info
    consoleHeight=csbi.srWindow.Bottom - csbi.srWindow.Top;
    consoleWidth=csbi.srWindow.Right-csbi.srWindow.Left+1;

}

struct Point{
    int xCoord;
    int yCoord;
    Point(){

    }
    Point(int x,int y){
        xCoord=x;
        yCoord=y;
    }
};

class Snake{
    int length;
    char direction;
public:
    Point body[MAX_LENGTH];
    Snake(int x,int y){
        length=1;
        body[0]=Point(x,y);
        direction=DIR_RIGHT;
    }
    int getLength(){
        return length;
    }
    void changeDirection(char newDirection){
        if(newDirection == DIR_UP && direction!=DIR_DOWN){//direction is current direction here
            direction =newDirection;
        }
        else if(newDirection==DIR_DOWN && direction!=DIR_UP){
            direction=newDirection;
        }
        else if(newDirection==DIR_LEFT && direction!=DIR_RIGHT){
            direction=newDirection;
        }
        else if(newDirection==DIR_RIGHT && direction!=DIR_LEFT){
            direction=newDirection;
        }

    }
    bool move(Point food){
        for(int i=length-1;i>0;i--){
            body[i]=body[i-1];  //making the body move..moving every part of snake one step forward
        } 

        switch (direction){
            int val;
            case DIR_UP:              //when firection is up then x axis remain same but y axis decrease bye 1
                val=body[0].yCoord;       
                body[0].yCoord=val-1;
                break;
            case DIR_DOWN:              //when direction is down then y axis increase by 1 while x axis remain same;
                val=body[0].yCoord;
                body[0].yCoord=val+1;
                break;
            case DIR_RIGHT:             //when moving right then x axis increase and y axis remain same
                val=body[0].xCoord;
                body[0].xCoord=val+1;
                break;
            case DIR_LEFT:              // when moving left x axis decreases by 1 but y axis remain same
                val=body[0].xCoord;
                body[0].xCoord=val-1;
                break;
        }

        //when snake bites itself
        for(int i=1;i<length;i++){
            if(body[0].xCoord==body[i].xCoord && body[0].yCoord==body[i].yCoord){
                return false;
            }
        }
        //snake eats food
        if(food.xCoord==body[0].xCoord && food.yCoord == body[0].yCoord){
            body[length]=Point(body[length-1].xCoord, body[length-1].yCoord); //the new body part will be equal to the coords points of the body
            // part -1 means jo body[3] k coords the ab woh body[4] k hojynge coords points
            length++; //now length has been increase by 1
        }
        return true;
    }
};
class Board{
    Snake *snake;
    const char SNAKE_BODY ='O';
    Point food;
    const char FOOD='x';
    int score;
public:
    Board(){
        spawnFood();
        snake=new Snake(10,10);
        score=0; 
    }
    ~Board(){
        delete snake;
    }
    int getScore(){
        return score;
    }    
    void spawnFood(){
        int x=rand() % consoleWidth; //it will take any random value at any width
        int y= rand() % consoleHeight; //it will take any random at any height or vertical value
        food=Point(x,y);
    }
    void displayCurrentScore(){
        gotoxy(consoleWidth/2,0);
        cout<< "Current Score: " << score;
    }
    void gotoxy(int x,int y){
        COORD coord;
        coord.X=x;
        coord.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    }

    void draw(){
        system("cls");
        for(int i=0;i<snake->getLength();i++){
            gotoxy(snake->body[i].xCoord,snake->body[i].yCoord);//at these particulars coordinate snake body will be created
            cout<< SNAKE_BODY;
        }
        gotoxy(food.xCoord,food.yCoord);
        cout << FOOD;

        displayCurrentScore();
    }
    bool update(){
        bool isALIVE=snake->move(food);
        if(isALIVE==false){
            return false;
        }
        if(food.xCoord==snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord){
            score++;
            spawnFood();
        }
        return true;
    }
    void getInput(){
        if(kbhit()){
            int key=getch();
            if(key=='w' || key== 'W'){
                snake->changeDirection(DIR_UP);
            }
            else if(key=='a' || key=='A'){
                snake->changeDirection(DIR_LEFT);
            }
            else if(key=='s' || key=='S'){
                snake->changeDirection(DIR_DOWN);
            }
            else if(key=='d' || key=='D'){
                snake->changeDirection(DIR_RIGHT);
            }
        }
    }
};


int main(){
    srand(time(0));
    initScreen();
    Board *board=new Board();
    while(board->update()){
        board->getInput();
        board->draw();
        Sleep(80);
    }
    cout << " Game Over" << endl;
    cout<< "Final Score is:"<<board->getScore();
    return 0;
}
