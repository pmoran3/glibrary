#ifndef  GMODIFIER_H
#define  GMODIFIER_H 1

// c++
#include <string>
using std::string;
using std::cout;
using std::endl;


class GModifier
{
	
public:
	GModifier(string n, string s, string t, string e, bool verbosity) :
	name(n),
	shift(s),
	tilts(t),
	isPresent(true) {

		if(e == "no") present = false;

		if( verbosity ) {
			cout << GSETUPLOGHEADER <<  " Volume " << name << " modified with:";
			if (  shift != "default") cout << " - shift: "     << shift   ;
			if (  tilts != "default") cout << " - tilts: "     << tilts   ;
			if (present != true)      cout << " - existance: " << present ;
			cout << endl;
		}
	}

private:
	string name;  // volume name
	string shift;
	string tilts;
	bool isPresent; // true by default

public:
	string getShift()     { return shift; }
	string getTilts()     { return tilts; }
	bool   getExistence() { return isPresent; }
};

#endif
