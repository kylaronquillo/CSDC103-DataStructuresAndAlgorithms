#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

bool gameOver = false; // to determine if game is over or nah
const int width = 35; // width of border
const int height = 15; // height of border
int score = 0; // score of player
int level = 1; // gradually increase the snake's speed as the player advances

//  structure that contains the (x,y) of either food or snake body in the game box
struct Snake {
    int x, y;

    Snake(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class SnakeGame {
    private:
    char direction;
    char graph[height][width];
    list<Snake> body;
    queue<Snake> food;
    stack<Snake> move;

public: 
    // initialize where to put the head and food 
    SnakeGame() {

        int startX = width/2;
        int startY = height/2;
        body.push_front(Snake(startX, startY));

        createGameBox();
        spawnSnack();
        dispGameBox();
    }

    // assign characters to the game box 
    void createGameBox() {
        // use the const height and width
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == 0 || j == width - 1 || j == 0  || i == height - 1) { // this is based on the appearance of the border
                    graph[i][j] = '#'; 
                } else {
                    graph[i][j] = ' ';
                }
            }
        }
    }

    // interface
    void dispGameBox() {
        system("cls");
        // output the content of 2d array
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << graph[i][j];
            }
            cout << endl;
        }

        // display score and level
        cout << "SCORE: " << score << endl;
        cout << "LEVEL: " << level << endl;

    }
    
    // push xy coordinates of snack to queue food
    void spawnSnack() {
        int x, y;
        srand(static_cast<unsigned>(time(nullptr))); 

        do {
            x = 1 + rand() % (width - 2);
            y = 1 + rand() % (height - 2);
        } while (graph[y][x] != ' ');
        // push food coordinates to queue
        food.push(Snake(x, y));
    }   

    // get input from user using arrow keys
    void getDirection() {
        if (_kbhit()) {
            switch (_getch()) {
                case 72: // up
                    if(direction!= 'd') direction = 'u';
                    break;
                case 75: // left
                    if(direction!= 'r') direction = 'l';
                    break;
                case 80: // down
                    if(direction!= 'u') direction = 'd';
                    break;
                case 77: // right
                    if(direction!= 'l') direction = 'r';
                    break;
            }
        }
    }

    // update (x,y) coordinates depending on ur previoys input
    void moveSnake() {
        Snake head = body.front();
        int frontX = head.x;
        int frontY = head.y;

        switch (direction) {
            case 'u':
                frontY = head.y - 1;
                break;
            case 'd':
                frontY = head.y + 1;
                break;
            case 'l':
                frontX = head.x - 1;
                break;
            case 'r':
                frontX = head.x + 1;
                break;
        }
        move.push({frontX, frontY}); // push the coordinates to stack
    }

    //  get moves from the stack of moveSnake()
    void getMoves() {
        if (!move.empty()) {
            Snake head2 = move.top();
            move.pop();
            // if snake encounters food
            if (graph[head2.y][head2.x] == '*') {
                body.push_front(head2);
                food.pop();
                spawnSnack();
                score++;
            } else { // if snake is still hungry and is yet to encounter food
                body.pop_back();
                body.push_front(head2);
            }
        }
    }

    // use breadth first search (bfas) to check if the snake collides with itself
    bool bfsBody(char direction) {
        Snake head = body.front();
        queue<Snake> q;
        bool visited[height][width];

        //initialize 2d array with bool false
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                visited[i][j] = false; // so that the 2d array has a known value to begin
            }
        }

        // puts head to queue
        q.push({head.x, head.y});
        visited[head.y][head.x] = true;

        while (!q.empty()) {
            // remove current pos
            Snake current = q.front();
            q.pop();

            int x = current.x;
            int y = current.y;

            if (graph[y][x] == 'O' && !(x == head.x && y == head.y)) {
                //cout << "GAME OVER!!! Snake collided with itself.";
                return true;
            } 
            
            // get position based on the direction inpyt
            int dirX = 0, dirY = 0;
            switch (direction) {
                case 'u': dirY = -1; break;
                case 'd': dirY = 1; break;
                case 'l': dirX = -1; break;
                case 'r': dirX = 1; break;
            }

            int newX = x + dirX;
            int newY = y + dirY;

            // check if new position is within the grid and has not been visited
            if (newX >= 0 && newX < width && newY >= 0 && newY < height && !visited[newY][newX]) {
                q.push({newX, newY});
                visited[newY][newX] = true;
            }
        }
    
        return false;
    }

    // returns bool result from bfsBody
    bool hasCollisionBody() {
        return bfsBody(direction); 
    }

    // check if there is collision with border
    bool hasCollisionBorder() {
        Snake head = body.front();

        if (head.x == 0 || head.x == width - 1 || head.y == 0 || head.y == height - 1) {
            return true;  // collision with the border detected
        }
        return false;
    }
    
    // update game box for the position of snake and food depending on the list and queue
    void updateGameBox() {
        createGameBox();

        for (const auto &part : body) {
            graph[part.y][part.x] = 'O';
        }
        if (!food.empty()) {
            Snake foodPos = food.front();
            graph[foodPos.y][foodPos.x] = '*';
        }

        dispGameBox();
    }

};

int main(){
    SnakeGame s;
    while(!gameOver){
        s.getDirection();
        s.moveSnake();
        // if snake collides with itself, games over
        if (s.hasCollisionBody()) {
            gameOver = true;
            cout << "GAME OVER!!! Snake collided with itself.\n"; break;
        }
        // if snake collides with the borders #, games over
        if (s.hasCollisionBorder()) {
            gameOver = true;
            cout << "GAME OVER!!! Snake collided with the border.\n"; break;
        }
        s.getMoves(); 
        s.updateGameBox();
        // level increases , speed increases
        if (score <= 5){
            Sleep(200);
        }
        if(score > 5 && score <= 10){
            Sleep(150);
            level = 2;
        }
        if(score > 10 && score <= 15){
            Sleep(100);
            level = 3;
        }
        if (score > 15){
            Sleep(50);
            level = 4;
        }
    }
    return 0;
}