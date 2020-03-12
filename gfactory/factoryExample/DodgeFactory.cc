#include "DodgeFactory.h"

#include <iostream>
using namespace std;

void Dodge::go() {
	cout << " Instantiating Dodge" << endl;
	cout << " Factory car dodge dodgeVar[1][0] " << dodgeVar[1][0] << std::endl;
}

Dodge::Dodge() {
	dodgeVar[0][0] = 0;
	dodgeVar[0][1] = 1;
	dodgeVar[1][0] = 10;
	dodgeVar[1][1] = 11;
}
