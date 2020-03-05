// goptions
#include "goptions.h"

// c++
#include <iostream>

// gstrings
#include "gstring.h"
using namespace gstring;

// if an option is defined with default values, it will be passed to jValues
GOption::GOption(string n, string d, json j, bool g): name(n), description(d), joptionDefinition(j), groupable(g)
{
	// assigning non structured option with default values
	if (! joptionDefinition.begin().value().is_structured()) {

		json jValue;
		string jKey = joptionDefinition[JSONTAGNAME];
		jValue[jKey] = joptionDefinition[JSONTAGDFLT];

		jValues.push_back(jValue);

		return;
	}

	// checking that
	//	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
	//		cout << "A AAAA " << name << endl;
	//	}

}

void GOption::printOption(bool withDefaults)
{
	if (jValues.size() ) {
		if (! jValues.front().begin().value().is_structured()) {
			cout << ARROWITEM << jValues.front().begin().key() << ": " << jValues.front().begin().value() << endl;
		}
	}
}



// checking if the key is the json object is defined
bool GOption::isTagDefined(string key, int gverbosity) {

	bool isDefined = false;

	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {

		// if it's a JSON object
		string jsonTagName = definitionJsonValue[JSONTAGNAME];
		if (gverbosity > 1) {
			cout << GTABTAB << " Checking  " << key << " against " << jsonTagName << endl;
		}

		if (key == jsonTagName) {
			if (gverbosity > 1) {
				cout << TTGREENARROWITEM << key << " matches " << jsonTagName << endl;
			}
			return true;
		}

	}


	return isDefined;
}


bool GOption::parseJsons(string key, json userJsons, bool isAddition, int gverbosity)
{

	// looping over all user jsons
	for(auto &userJson: userJsons) {

		// buidling new value to add to jValues
		json newUserValue;

		// if a simple key/value option (not is_structured) then assigning the new user value and return true
		if (! userJson.is_structured() ) {
			newUserValue[key] = userJson.items().begin().value();
			jValues.push_back(newUserValue);

			if (gverbosity) {
				cout << TGREENPOINTITEM << "Json Option " << GREENHHL << key << RSTHHR << " set with value: " << userJson.items().begin().value() <<  endl;
			}

			return true;
		}



		if (gverbosity) {
			cout << TGREENPOINTITEM << "Json Option " << userJson << endl;
		}

		// reset jValues if add- is not found
		if (!isAddition && jValues.size() > 0 ) {
			if (gverbosity) { cout << GWARNING << " Resetting Option Content " << endl; }
			jValues.clear();
		}

		// if add- was found but option is not groupable, it's a mistake.
		if (isAddition && !groupable) {
			cout << GWARNING << " Trying to adding to the non groupable option " << YELLOWHHL << name << RSTHHR". This will be ignored." << endl;
			return false;
		}



		// first checking that all user tags are valid entries.
		for (auto& [userJsonKey, userJsonValue] : userJson.items()) {

			// verbose search
			if (gverbosity > 1) {
				cout << TTPOINTITEM << " Single Key: " << userJsonKey << ",  single value: " << userJsonValue << endl;
			}

			// checking if userJsonKey is defined
			if ( !isTagDefined(userJsonKey, gverbosity) )  {
				cout << GWARNING  " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is not known to this system. This will be ignored." << endl;
				return false;
			}

			// tag is valid, assigning key and valie to new user option
			newUserValue[userJsonKey] = userJsonValue;

		}

		// at this point all json keys are valid.
		// we need to assign default values if they are not present

		for (auto& [userJsonKey, userJsonValue] : userJson.items()) {
		}

		// looping

		// looping over detector definitions
		//		for (auto& jsonTag: joptionDefinition) {
		//
		//			string jsonTagName = jsonTag[JSONTAGNAME];
		//			string jsonTagDesc = jsonTag[JSONTAGDESC];
		//			auto jsonTagDflt   = jsonTag[JSONTAGDFLT];
		//
		//		}

	}

	return false;
}

