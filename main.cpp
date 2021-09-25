#include <iostream>
#include <vector> 
#include <algorithm>



using namespace std;



const int MAX_BOARD_SIZE = 21;  //  Global variable for max x and y coordinate of board; boards origin is 0, 0
string board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];  //  constant for board size
vector<pair<int,int>> snake;  //  global so all functions can directly acess the snake vector
bool playGame = true;  //  condtion to end game when false
int total = 0;




void collision();  //  implemented
bool collectApple(pair<int, int>);  //  not implemented
void genApple(vector<pair<int, int>>);   //  not implemented
void printBoard();  //  implemented
void draw(string value, vector<pair<int, int>> &list);  //  implemented
void draw(string value, pair<int, int> coord);
void move(char direction);  //  implemented
void clearBoard();  //  implemented



int main(){
    string input;
    for(int i = 0; i < 3; i++){
        snake.push_back(    make_pair(((MAX_BOARD_SIZE+1)/2-1), (((MAX_BOARD_SIZE+1)/2))-i)   );  //  Sets the starting position of the snake to middle three sections of board
    }
    reverse(snake.begin(), snake.end());
    
      //  reverses snake so head is at front as array is reverse of mathmatical graphs
    clearBoard();
    draw("■", snake);  //  draws snake in middle of board and displays it for starting position
    printBoard();

    while(playGame){
        input = ' ';
        while(input != "w" && input != "a" && input != "s" && input != "d" && input != "q"){
            cin >> input;
        if(input == "q"){
            playGame = false;
            break;
        }
        move(input[0]);
        system("clear");
        printBoard();
        }
    }
    cout << "GAME OVER\n";
}



void collision(){  //  Exits game when collision is detected with wall or rest of snake
    if(snake[0].first < 0 || snake[0].second < 0 || snake[0].first > MAX_BOARD_SIZE-1 || snake[0].second > MAX_BOARD_SIZE-1){
        playGame = false;
    }else{
        for(int i = 1; i < snake.size(); i++){
            if(snake[0] == snake[i]){
                playGame = false;
            }
        }
    }
}



void printBoard(){  //  prints the board with a neat boarder around it
    system("clear");
    for(int i = 0; i < MAX_BOARD_SIZE*2+3; i++){
        cout << "▄";
    }
    cout << "\n";
    for(int i = 0; i < MAX_BOARD_SIZE; i++){
        cout << "█ ";
        for(int j = 0; j < MAX_BOARD_SIZE; j++){
            cout << board[i][j] << " ";
        }
        cout << "█";
        cout << "\n";
    }
    for(int i = 0; i < MAX_BOARD_SIZE*2+3; i++){
        cout << "▀";
    }
    cout << "\n";
}



void draw(string value, vector<pair<int, int>> &list){  //  draws the specified value onto the board using the coordinates from a vector
    for(auto coord : list){
        board[coord.second][coord.first] = value;
    }
}



void draw(string value, pair<int, int> coord){  //  draw fuction when only a single item needs to be drawn
    board[coord.second][coord.first] = value;
}



void move(char direction){  //  adds new snake head position, checks it doesn't collide with anything then prints the new board
    bool valid = true;
    pair<int, int> clean, head;
    clean.first = snake[snake.size()-1].first;  //  removes the last section of the snake
    clean.second = snake[snake.size()-1].second;
    switch(direction){
        default:
            system("clear");  //  prevents invalid moves being made
            printBoard();
            valid = false;
            break;
        case 'w':
            snake.insert(snake.begin(), make_pair(snake[0].first, snake[0].second-1));  //  moves snake up
            break;
        case 'a':
            snake.insert(snake.begin(), make_pair(snake[0].first-1, snake[0].second));  //  moves snake left
            break;
        case 's':
            snake.insert(snake.begin(), make_pair(snake[0].first, snake[0].second+1));  //  moves snake down
            break;
        case 'd':
            snake.insert(snake.begin(), make_pair(snake[0].first+1, snake[0].second));  //  moves snake right
            break;
    }
    if(valid){
        collision();
        if(playGame){
            head.first = snake[0].first;  //  makes pair for snakes head new coordinates
            head.second = snake[0].second;
            draw(" ", clean);  //  removes the last section of the snake from the board
            snake.pop_back();
            draw("■", head);  //  draws the new snake position onto the board
            printBoard();
        }
    }
}




void clearBoard(){
    for(int i = 0; i < MAX_BOARD_SIZE; i++){  //  fills board with spaces when board is created
    for(int j = 0; j < MAX_BOARD_SIZE; j++){
        board[j][i] = " "; 
        }
    }
}