#include <iostream>
#include <vector>
#include <chrono>       // Get the Better Cpp-11 replace for  srand()
#include <random>       // Get the Engine & Distribution
using namespace std;
// Object
// Tile: contains the Pokemon in the table that need to earse
class Tile {
public:
    int type;           // Type of the Tile (ex: 0 -> Pikachu, 1 -> Bulbasal)
    int row, column;    // the row, column in the table
    bool visible;       // Is Erase or not( Lazy notation)
    
    Tile(int __type, int __row, int __column){
        type = __type; row = __row; column = __column;
        visible  = false;
    }
};
// Contains all the tiles
class Board {
public:
    vector<vector<Tile*>> board;
    int row_size, col_size;
    int kinds;                      // Number of tile types in the board
    int remain;                     // Number of tiles left that is still visible
    Board(int __row_size, int __col_size, int __kinds) {
        row_size = __row_size; col_size = __col_size; kinds  = __kinds;
        remain = (__row_size-2)*(__col_size-2);
    }
public:
    void CreateNewBoard();
    bool canConnect(vector<pair<int,int>>& path,int r1, int c1, int r2, int c2); // Check wether a pair can be Connect or not
    bool canConnect(int r1, int c1, int r2, int c2);
    void RemoveTile(int r1, int c1, int r2, int c2);
    void Shuffle();
public:
    bool InBoard(int r, int c);
    bool IsEmptyOrTarget(int row_from, int col_from, int row_des, int col_des);
    vector<pair<int,int>> getSameType(const int type);
    bool HasAvaibleMove();
    void Shuffle(vector<int>& list);                                // Shuffle the Vector
};