#include "Enemy.h"
#include <random>
#include <iostream>
#include <ctime>
using namespace std ;
Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int experienceValue)
{
   _name = name;
   _level = level ;
   _attack = attack ;
   _defense = defense ;
   _health = health ;
   _experienceValue = experienceValue ;
   _tile = tile ;
}



// set the position of the Enemy
void Enemy :: setPosition( int x, int y){

        _x = x ;
        _y = y ;

}

// Get the position of the Enemy
void Enemy :: getPosition(int &x, int &y) {

    x = _x ;
    y = _y ;


}



int Enemy :: attack() {

    static default_random_engine randomEngine(time(NULL)) ;
    uniform_int_distribution<int> attackRoll(0,_attack) ;

    return attackRoll(randomEngine) ;
}


int Enemy :: takeDamage (int attack){

    attack -= _defense ;
    // check if the attack cause damage
    if (attack > 0){
        _health -= attack ;
        // check if he died
        if (_health <= 0){
            return _experienceValue ;
        }
    }else {
        return 0 ;
    }

}



char Enemy :: getMove(int playerX, int playerY){

    static default_random_engine randEngine(time(NULL)) ;
    uniform_int_distribution<int> moveRoll(0,6) ;
    int distance ;
    int dx  = _x - playerX;
    int dy  = _y - playerY ;
    int adx = abs(dx) ;
    int ady = abs(dy) ;
    distance =  adx + ady ;

    if (distance <= 5 ){
        // Moving  in the X axis
        if (adx > ady) {
            if (dx > 0 ){
                return 's' ;
            }
            else {
                return 'd' ;
            }
        }
        // Moving in the Y axis
        else {

        if (dy > 0 ){
                return 'e' ;
            }
            else {
                return 'x' ;
            }


        }
    }

    int randomMove = moveRoll(randEngine) ;
    switch (randomMove){
        case 0 :
            return 's' ;
        case 1 :
            return 'x' ;
        case 2 :
            return 'e' ;
        case 3 :
            return 'd' ;
        default :
            return '.' ;

    }
}


