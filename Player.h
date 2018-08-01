#ifndef PLAYER_H
#define PLAYER_H


class Player
{
    public:
        Player();
        void init(int level, int health, int attack, int defense, int experience) ;
        int attack() ;
        int  takeDamage (int attack) ;

        //Setter
        void setPosition(int x, int y) ;

        //Getter
        void getPosition(int &x, int &y) ;
        void addExperience(int experience) ;

    private:
    //Proprieties
    int _level ;
    int _health ;
    int _attack ;
    int _defense ;
    int _experience ;

    // positions

    int _x ;
    int _y ;
};

#endif // PLAYER_H
