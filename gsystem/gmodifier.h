#ifndef  GMODIFIER_H
#define  GMODIFIER_H 1

// c++
#include <iostream>
using std::string;
using std::cout;
using std::endl;

class GModifier
{
	
public:
	GModifier(string n, string s, string t, bool existance, int verbosity) :
	name(n),
	shift(s),
	tilts(t),
	isPresent(existance) {

		if( verbosity ) {
			cout << GSETUPLOGHEADER <<  " volume " << name << " modified with:";
			if (  shift != NOMODIFIER) cout << " - shift: "     << shift   ;
			if (  tilts != NOMODIFIER) cout << " - tilts: "     << tilts   ;
			if ( !isPresent )         cout << " - existance: " << isPresent ;
			cout << endl;
		}
	}

private:
	string name;  // volume name
	string shift;
	string tilts;
	bool   isPresent; // true by default

public:
	string getShift()     { return shift; }
	string getTilts()     { return tilts; }
	bool   getExistence() { return isPresent; }
};

#endif
