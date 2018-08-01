#include "Level.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>

using namespace std ;


Level::Level()
{
    //ctor
}




void Level :: load(string fileName, Player &player){


    // Loading the level
    ifstream inputFile ;
    inputFile.open(fileName) ;

    if (inputFile.fail()) {
        perror(fileName.c_str()) ;
        exit(1) ;
    }

    string line ;

    while (getline(inputFile, line)) {


    _levelData.push_back(line) ;

    }
    inputFile.close() ;

     // Processing the level

     char tile ;
     // x = columns
     // y = row
     for (int row = 0; row < _levelData.size(); row++){
        for (int columns = 0; columns <_levelData[row].size() ; columns++ ) {
            tile = _levelData[row][columns] ;

            switch(tile){
                case '@' : //Player
                player.setPosition(columns, row) ;
                    break ;

                 case 'S' : // Snake
                    _enemies.push_back(Enemy("Snake", tile, 1,3,1,10,50)) ;
                    _enemies.back().setPosition(columns, row) ;
                    break ;

                case 'g' : // Snake
                    _enemies.push_back(Enemy("Goblin", tile, 2,10,5,35,150)) ;
                    _enemies.back().setPosition(columns, row) ;
                    break ;

                case 'O' : // Ogre
                    _enemies.push_back(Enemy("Ogre", tile, 4,20,40,200,500)) ;
                    _enemies.back().setPosition(columns, row) ;
                    break ;

                case 'D' : // Dragon
                    _enemies.push_back(Enemy("Dragon", tile, 100,2000,2000,2000,500000)) ;
                    _enemies.back().setPosition(columns, row) ;
                    break ;

                case 'B' : // Bandit
                    _enemies.push_back(Enemy("Bandit", tile, 3,15,10,100,250)) ;
                    _enemies.back().setPosition(columns, row) ;
                    break ;
            }
        }

     }




}

void Level :: print() {

     for (int i = 0 ;  i < _levelData.size(); i++){
     cout << _levelData[i].c_str() << endl ;

     }

     cout << endl ;

}


void Level :: movePlayer(char input, Player &player){

    int playerX;
    int playerY ;

    player.getPosition(playerX, playerY) ;

    switch(input){
        case 's' : //Left
            controlPlayerMove(player, playerX-1 , playerY);
            break ;

        case 'e' : //Up
            controlPlayerMove(player, playerX , playerY-1);

            break ;

        case 'd' : //Right
            controlPlayerMove(player, playerX+1 , playerY);

            break ;

        case 'x' : //Down
            controlPlayerMove(player, playerX , playerY+1);

            break ;

        default :

            cout << "Invalid Input"<< endl;
            break ;



    }
}


char Level ::getTile(int X, int Y) {

    return _levelData[Y][X] ;


}


void Level ::setTile(int X, int Y, char tile){

        _levelData[Y][X] =tile ;

}

void Level :: controlPlayerMove(Player &player, int targetX, int targetY) {

    int playerX;
    int playerY ;
    player.getPosition(playerX, playerY) ;
    char moveTile = getTile(targetX, targetY ) ;
    switch(moveTile){

        case '.' :
            player.setPosition(targetX  , targetY) ;
            // deplacement of the player
            setTile(playerX, playerY, '.') ; // replace the dot sign to at sign
            setTile(targetX , targetY, '@') ; // Put the player in the new location
            break ;

        case '#' :
            //cout << "Wall" << endl ;
            break ;
        default :
            battleMonster(player, targetX, targetY) ;
            break ;

    }

}


void Level :: battleMonster(Player &player, int targetX, int targetY) {

    int enemyX ;
    int enemyY ;
    int playerX ;
    int playerY ;
    int attackRoll ;
    int attackResult ;
    string enemyName ;

    player.getPosition(playerX, playerY) ;
    for (int i =0 ; i < _enemies.size(); i++){

        _enemies[i].getPosition(enemyX, enemyY) ;
        enemyName = _enemies[i].getName();
        if (targetX == enemyX && targetY == enemyY) {

            // Battle Royal!

            attackRoll = player.attack();
            cout << " You attacked a " << enemyName.c_str() << " with a roll of " << attackRoll << endl ;
            attackResult = _enemies[i].takeDamage(attackRoll) ;
            if (attackResult != 0){
                setTile(targetX, targetY, '.');
                print();
                cout << "Nice, the Monster died by your hands" ;

                // remove the enemy
                _enemies[i] = _enemies.back() ;
                _enemies.pop_back() ;
                i-- ;
                system("PAUSE") ;
                player.addExperience(attackResult) ;
                return ;
            }
            else {

                //Monster time
                cout << " A " << enemyName.c_str() << " attacked you with a roll of " << attackRoll << endl ;
                attackRoll = _enemies[i].attack() ;
                attackResult = player.takeDamage(attackRoll) ;

                if (attackResult != 0){
                    setTile(playerX, playerY, 'X');
                    print() ;
                     cout << " Bad a " << enemyName.c_str() << " Killed You" <<  endl ;
                     system("PAUSE") ;

                    exit(0);
            }
            }


        system("PAUSE") ;
        return;
        }


    }

}



void Level :: processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {


    int playerX;
    int playerY ;
    int enemyX ;
    int enemyY ;

    _enemies[enemyIndex].getPosition(enemyX, enemyY) ;
    player.getPosition(playerX, playerY) ;

    char moveTile = getTile(targetX, targetY ) ;

    switch(moveTile){

        case '.' :
            _enemies[enemyIndex].setPosition(targetX  , targetY) ;
            // deplacement of the player
            setTile(enemyX, enemyY, '.') ; // replace the dot sign to at sign
            setTile(targetX , targetY, _enemies[enemyIndex].getTile()) ; // Put the Enemy in the new location
            break ;

        case '@' :
            battleMonster(player, enemyX, enemyY) ;
            break ;
        default :
            break ;

    }



}


void Level :: updateEnemy(Player &player) {

    char aiMove ;
    int playerX ;
    int playerY ;
    int enemyX ;
    int enemyY ;
    player.getPosition(playerX, playerY) ;
    for (int i = 0; i < _enemies.size(); i++){
        aiMove = _enemies[i].getMove(playerX, playerY) ;
        _enemies[i].getPosition(enemyX, enemyY) ;
        //cout << "move :"<<aiMove << endl << endl ;

        switch(aiMove){
            case 's' : //Left
                processEnemyMove(player, i, enemyX-1 , enemyY);
                break ;

            case 'e' : //Up
                processEnemyMove(player, i, enemyX , enemyY-1);

                break ;

            case 'd' : //Right
                processEnemyMove(player, i,enemyX+1 , enemyY);

                break ;

            case 'x' : //Down
                processEnemyMove(player, i, enemyX , enemyY+1);

                break;


        }
    }
    //exit(0);
}

