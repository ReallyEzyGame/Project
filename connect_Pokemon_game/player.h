#include <string>
#include <vector>
#include <iostream>
#define __SCORE 10
using namespace std;
class Player {
public:
    string name;

    Player(string __name) {
        name = __name;
        level = 1;
        score = 0;
    }
private:
    unsigned level;
    unsigned int score;
    void UpdateScore();
public:
    void NewGame();
    void RefreshScore();
    void Rename();

};