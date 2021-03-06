#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <string>


using namespace std;

class Enemy
{
    public:
        Enemy(string name, char tile, int level, int attack, int defense, int health, int experienceValue);

        int attack() ;
        int  takeDamage (int attack) ;

        // Gets AI move command

        char getMove(int playerX, int playerY) ;

        //Setter
        void setPosition(int x, int y) ;

        //Getter
        void getPosition(int &x, int &y) ;
        string getName() {return _name ;}
        char getTile(){ return _tile ;}

    private:

        string _name ;
        char _tile ;
        int _level ;
        int _attack ;
        int _defense ;
        int _health ;
        int _experienceValue ;

        // positions

        int _x ;
        int _y ;
};

#endif // ENEMY_H
