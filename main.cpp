#include <iostream>
#include <fstream>
#include <string>
#include "GameSystem.h"



using namespace std;

int main()
{
    GameSystem GameSystem("level1.txt") ;
    GameSystem.playGame();

    return 0;
}
