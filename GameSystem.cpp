#include "GameSystem.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include<curses.h>

using namespace std ;


// Contructor sets up the game
GameSystem::GameSystem( string levelFileName)
{
    _player.init(1,100,10,10,0);
    _level.load(levelFileName, _player) ;

}


void GameSystem::playGame() {

 bool isDone = false ;

 while (isDone == false) {

    _level.print() ;
    playerMove() ;
    _level.updateEnemy(_player);


 }

}

 void GameSystem::playerMove() {

    char input ;
    cout << "Enter a move command (s/e/d/x): " ;
    input  = getchar();
    _level.movePlayer(input, _player) ;





 }
