// gstring 
#include "gstring.h"

// c++
#include <sstream>
using namespace std;

//! Trim Both leading and trailing spaces
string gstring::trimSpacesFromString(string in)
{
	string out;

	size_t leapos = in.find_first_not_of(" \t"); // Find the first character position after excluding leading blank spaces
	size_t endpos = in.find_last_not_of(" \t");  // Find the first character position from reverse af

	// if all spaces or empty return an empty string
	if(( leapos == string::npos) || ( endpos == string::npos))
		out = "";
	else
		out = in.substr( leapos, endpos-leapos+1 );

	return out;
}

//! Get the filename from the path (currently only posix)
string gstring::getFileFromPath(string path)
{
	return path.substr(path.find_last_of("/") + 1);
}

//! Return a vector of strings from a stringstream, space is delimeter
vector<string> gstring::getStringVectorFromString(string input)
{
	vector<string> pvalues;
	stringstream plist(input);
	while(!plist.eof()) {
		string tmp;
		plist >> tmp;
		string toPut = trimSpacesFromString(tmp);
		if(toPut != "")
			pvalues.push_back(toPut);
	}

	return pvalues;
}

//! Replace all occurences of specific chars in a string with a string
string gstring::replaceCharInStringWithChars(string input, string toReplace, string replacement)
{

	string output = "";

	for(unsigned int k=0; k<input.size(); k++) {

		int replace = 0;

		for(unsigned int j=0; j<toReplace.size(); j++) {
			// found common char, replacing it with replacement
			if(input[k] == toReplace[j]) {
				output.append(replacement);
				replace = 1;
			}
		}
		if(!replace) output += input[k];
	}

	return output;
}

//! Replace all occurences of a a string with a string
string gstring::replaceAllStringsWithString(string source, const string from, const string to)
{
	string newString;

	size_t lastPos = 0;
	size_t findPos;

	while((findPos = source.find(from, lastPos) != string::npos))
	{
		newString += to;
		newString.append(source, lastPos + from.length(), findPos - lastPos  );
		lastPos = findPos + from.length();
	}

	// Care for the rest after last occurrence
	newString += source.substr(lastPos);

	return newString;
}


//! Fill a string with the string c to be ndigits long
string gstring::fillDigits(string word, string c, int ndigits)
{
	string filled;

	int toFill = ndigits - (int) word.size();

	for(int d=0; d<toFill; d++) {
		filled += c;
	}

	filled += word;

	return filled;
}




// Numbers / strings with units / io

// CLHEP units
#include "CLHEP/Units/PhysicalConstants.h"
using namespace CLHEP;

// c++
#include <iostream>

/// \fn double getG4Number(string v, bool warnIfNotUnit)
/// \brief Return value of the input string, which may or may not
/// contain units (warning given if requested)
/// \param v input string. Ex: 10.2*cm
/// \return value with correct G4 unit.
double gstring::getG4Number(string v, bool warnIfNotUnit)
{
	string value = trimSpacesFromString(v);

	// no * found
	if(value.find("*") == string::npos) {
		// no * found, this should be a number
		// No unit is still ok if the number is 0

		if(value.length()>0 && warnIfNotUnit && stod(value) != 0) {
			cout << " ! Warning: value " << v << " does not contain units." << endl;
		}
		return stod(value);

	} else {
		string rootValue = value.substr(0, value.find("*"));
		string units     = value.substr(value.find("*") + 1);

		double answer = stod(rootValue);

		if( units == "m")         answer *= m;
		else if( units == "inches")    answer *= 2.54*cm;
		else if( units == "inch")      answer *= 2.54*cm;
		else if( units == "cm")        answer *= cm;
		else if( units == "mm")        answer *= mm;
		else if( units == "um")        answer *= 1E-6*m;
		else if( units == "fm")        answer *= 1E-15*m;
		else if( units == "deg")       answer *= deg;
		else if( units == "degrees")   answer *= deg;
		else if( units == "arcmin")    answer = answer/60.0*deg;
		else if( units == "rad")       answer *= rad;
		else if( units == "mrad")      answer *= mrad;
		else if( units == "eV")        answer *= eV;
		else if( units == "MeV")       answer *= MeV;
		else if( units == "KeV")       answer *= 0.001*MeV;
		else if( units == "GeV")       answer *= GeV;
		else if( units == "T")         answer *= tesla;
		else if( units == "T/m")       answer *= tesla/m;
		else if( units == "Tesla")     answer *= tesla;
		else if( units == "gauss")     answer *= gauss;
		else if( units == "kilogauss") answer *= gauss*1000;
		else if( units == "ns")        answer *= ns;
		else if( units == "na")        answer *= 1;
		else if( units == "counts")    answer *= 1;
		else cerr << ">" << units << "<: unit not recognized for string <" << v << ">" << endl;
		return answer;
	}

	return EXIT_SUCCESS;
}

vector<double> gstring::getG4NumbersFromStringVector(vector<string> vstring, bool warnIfNotUnit)
{
	vector<double> output;

	for(auto &s: vstring) {
		output.push_back(getG4Number(s, warnIfNotUnit));
	}

	return output;
}

vector<double>  gstring::getG4NumbersFromString(string vstring, bool warnIfNotUnit) {
	return getG4NumbersFromStringVector(getStringVectorFromString(vstring), warnIfNotUnit);
}


// c++
#include <fstream>

// need to add verbosity
string gstring::parseFileAndRemoveComments(string filename, string commentChars, int verbosity) {

	// reading file
	stringstream strStream;
	ifstream in(filename.c_str());
	if(!in) {
		cerr << FATALERRORL << " Error: can't open input file " << filename << ". Check your spelling. " << endl;
		gexit(EC__FILENOTFOUND);
	} else {
		if(verbosity > 0) {
			cout << endl << CIRCLEITEM <<  " Loading string from " << filename << endl;
		}
		strStream << in.rdbuf(); //read the file
	}
	in.close();


	string parsedString = strStream.str();

	// removing all occurances of commentChars
	while (parsedString.find(commentChars.c_str()) !=  string::npos ) {
		size_t nFPos = parsedString.find(commentChars.c_str());   // locate commentChars in the string
		size_t secondNL = parsedString.find('\n', nFPos);         // locate the next CR starting from where commentChars was found
		size_t firstNL = parsedString.rfind('\n', nFPos);         // locate the last CR before where commentChars was found

		// remove the lines containing the comment
		parsedString.erase(firstNL, secondNL - firstNL);

	}

	return parsedString;
}

// retrieve string between two strings
string gstring::retrieveStringBetweenChars(string input, string firstDelimiter, string secondDelimiter)
{
	string out;

	size_t firstpos  = input.find(firstDelimiter);  // Find the first character position after excluding leading blank spaces
	size_t secondpos = input.find(secondDelimiter); // Find the second character position after excluding leading blank spaces

	// if all spaces or empty return an empty string
	if(( firstpos == string::npos) || ( secondpos == string::npos))
		out = "";
	else
		out = input.substr( firstpos + 1, secondpos - firstpos - 1 );

	return out;

}


// thread safe message systems

#include <mutex>
std::mutex mu;

// exiting with error, print error on screen.
void gexit(int error) {
	mu.lock();
	cerr << KBOLD << KRED << " Exiting with error " << error << RST << endl;
	mu.unlock();
	exit(error);
}

// class constructor
void gLogClassConstruct(string className) {
	mu.lock();
	cout << KGRN << CONSTRUCTORLOG <<  className << KWHT << " class constructor" << RST << endl;
	mu.unlock();
}

// copy constructor
void gLogCopyConstruct(string className) {
	mu.lock();
	cout << KGRN << CONSTRUCTORLOG <<  className << KWHT << " copy constructor" << RST << endl;
	mu.unlock();
}

// move constructor
void gLogMoveConstruct(string className) {
	mu.lock();
	cout << KBLU << CONSTRUCTORLOG <<  className << KWHT << " move constructor" << RST << endl;
	mu.unlock();
}

// destructor
void gLogDestruct(string className) {
	mu.lock();
	cout << KRED << DESTRUCTORLOG <<  className << KWHT << " destructor" << RST << endl;
	mu.unlock();
}
