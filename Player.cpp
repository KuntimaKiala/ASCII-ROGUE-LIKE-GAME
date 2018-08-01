#include "Player.h"
#include <random>
#include <iostream>
#include <ctime>
using namespace std;
// Constructor, initializing positions to (0,0) coordinates
Player::Player()
{
    _x = 0 ;
    _y = 0 ;
}

//Initialize the player proprieties
void Player :: init(int level, int health, int attack, int defense, int experience) {
    _level = level;
    _health = health ;
    _attack = attack;
    _defense = defense;
    _experience = experience;
}


// set the position of the player
void Player :: setPosition( int x, int y){

        _x = x ;
        _y = y ;

}

// get the position of the player
void Player ::  getPosition(int &x, int &y) {

    x = _x ;
    y = _y ;


}



int Player :: attack() {

    static default_random_engine randomEngine(time(NULL)) ;
    uniform_int_distribution<int> attackRoll(0,_attack) ;

    return attackRoll(randomEngine) ;
}


void Player :: addExperience(int experience){

    _experience += experience ;
    // Level Up
    while(_experience > 50 ){
        cout << "Leveled Up "<< endl ;
        _experience -= 50 ;
        _attack += 10 ;
        _defense += 5 ;
        _health += 10 ;
        _level++ ;

    }

}


int Player :: takeDamage (int attack){

    attack -= _defense ;
    // check if the attack cause damage
    if (attack > 0){
        _health -= attack ;
        // check if he died
        if (_health <= 0){
            return 1 ;
        }
    }else {
        return 0 ;
    }

}
