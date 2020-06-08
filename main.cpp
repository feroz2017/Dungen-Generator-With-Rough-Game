/*

    including libraries
*/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

/*Defining Maximum number of dimensions*/

/*
    Defining the Definintion of Constant 
*/
#define MAX_DIM 500
#define EMPTY ' '
#define FLOOR '.'
#define WALL '/'
#define PLAYER '&'
#define TREASURE 'T'
using namespace std;

/*Defining the Game's Require functions's Declartions*/
void loadMap(string filename,char map[][MAX_DIM],int & rows, int & cols);
void printMap(const char map[][MAX_DIM],int rows,int cols);
void objectPlace(char toPlace,char map[][MAX_DIM],int rows,int cols);
bool makeMove(char move,char map[][MAX_DIM],int rows,int cols);

/*Stating Point of Main Program*/
int main() {
    /*Defining the rows and Colums for storing map Dimensions*/
    int rows,cols = 0;
    // Making a flag for gameOver
    bool game = false;
    srand(time(0)); 
    char map[MAX_DIM][MAX_DIM]; // defining variable for Map
    char filename[100];
    cout << "Enter the name of the map to be loaded: ";
    cin >> filename;
    loadMap(filename,map,rows,cols);
    objectPlace(PLAYER,map,rows,cols);
    objectPlace(TREASURE,map,rows,cols);
    printMap(map,rows,cols);
    
   // Making game as require

     while(!game){
        char move;
        cout << "Which direction would you like to move? (n, s, w, e):";
        cin >> move;
        if(!makeMove(move,map,rows,cols)){
            printMap(map,rows,cols);
            continue;
        }
        else{
            break;
        }
    } 
    
    int end;
    while(!game){
        cout << "Process finished with exit code 0:";
        cin >> end;
        if(end == 0)
            break;
    }
    return 0;
}
// Loading Map
void loadMap(string filename,char map[][MAX_DIM],int & rows, int & cols)
{
    ifstream openfile;
    string line;
    openfile.open(filename,ios::in);
    if(openfile){
        getline(openfile,line);
        cout << line;
        string delimiter = " ";
        size_t pos = 0;
        string token;
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        rows = stoi(token);
        line.erase(0, pos + delimiter.length());
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        cols =  stoi(token);
        char ch;
        for (int r = 0 ;r < rows; r++ ){
            for (int c = 0;c< cols;c++){
             if(openfile >> noskipws >> ch) {
                 map[r][c] = ch;
             }
             else
             {
                 break;
             }
            }
        }
       
        cout << "\n";
    }
    else{

    }
}
// Printing Map
void printMap(const char map[][MAX_DIM],int rows,int cols)
{
    cout<< "Current Map:";
         for (int r = 0 ;r < rows; r++ ){
            for (int c = 0;c< cols; c++){
                cout << map[r][c];
            }
        }
        cout << "\n";
}
// For placing PLAYER AND TREASURE IN DUNGEN
void objectPlace(char toPlace,char map[][MAX_DIM],int rows,int cols)
{
    int validRow = rand()%rows;
    int validCol = rand()%cols;
    bool flag = true;
    while(flag){
        if(map[validRow][validCol] == FLOOR){
            map[validRow][validCol] = toPlace;
            flag = false;
        }
        else{
          
            validRow = rand()%rows;
            validCol = rand()%cols;
        }
    }
}

// Making SMART MOVE AGAINST DUNGEN ......... HURRAH!@
bool makeMove(char move,char map[][MAX_DIM],int rows,int cols){
    int r,c;
    for ( r = 0 ;r < rows; r++ ){
            for ( c = 0;c < cols;c++){
                // Firt finding the our player where it stands
                if(map[r][c] == PLAYER)
                    {
                        // Moving North
                        if(move == 'n'){
                            if(r-1 < rows || (map[r-1][c] != WALL)){
                                if(map[r-1][c] == TREASURE){
                                    cout << "\nFOUND THE TREASURE!!!!!\n";
                                    return true;
                                }
                            else{
                                map[r][c] = FLOOR;
                                map[r-1][c] = PLAYER;
                                return false;
                            }
                            }
                        else{
                            cout << "\n Can't move there...\n";
                        } 
                        }
                        // Moving East
                        else if(move == 'e'){
                            if(c+1 < cols || (map[r][c+1] == FLOOR)){
                                if(map[r][c+1] == TREASURE){
                                    cout << "\nFOUND THE TREASURE!!!!!\n";
                                    return true;
                                }
                            else{
                                map[r][c] = FLOOR;
                                map[r][c+1] = PLAYER;
                                return false;
                            }
                            }
                            else{   
                                cout << "\n Can't move there...\n";
                            }  
                        }
                        // Moving West
                        else if (move == 'w'){
                    // 
                            if(c-1 < cols || (map[r][c-1] != WALL)){
                                if(map[r][c-1] == TREASURE){
                                    cout << "\nFOUND THE TREASURE!!!!!\n";
                                    return true;
                                }
                                else{
                                    map[r][c] = FLOOR;
                                    map[r][c-1] = PLAYER;
                                    return false;
                                }
                            }
                            else{
                                cout << "\n Can't move there...\n";
                            } 
                        }
                        // Moving South
                        else if (move == 's'){
                            if(r+1 < rows || (map[r+1][c] != WALL)){
                                if(map[r+1][c] == TREASURE){
                                    cout << "\nFOUND THE TREASURE!!!!!\n";
                                    return true;
                            }
                            else{
                                map[r][c] = FLOOR;
                                map[r+1][c] = PLAYER;
                                return false;
                            }
                            }
                        else{
                                cout << "\n Can't move there...\n";
                        }
                        }
                    else {
                        cout << "\nEnter valid move\n";
                    }
                        break;
                    }   
            }
            {
                
            } // 
            
        }
   
    return false;
}