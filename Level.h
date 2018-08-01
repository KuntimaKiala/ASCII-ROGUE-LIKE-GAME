#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

using namespace std ;


class Level
{
    public:
        Level();
        void load(string fileName, Player &player) ;
        void print() ;
        void movePlayer( char input,  Player &player) ;
        void updateEnemy(Player &player) ;
        // getter and setter
        char getTile(int X, int Y) ;
        void setTile(int X, int Y, char tile) ;


    private:
        vector <string> _levelData ;
        void controlPlayerMove(Player &player, int targetX, int targetY) ;
        void battleMonster(Player &player, int targetX, int targetY) ;
        vector <Enemy> _enemies ;
        void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) ;
};

#endif // LEVEL_H
