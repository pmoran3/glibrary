// goptions
#include "goptions.h"

// c++
#include <iostream>


// if an option is defined with default values, it will be passed to jUserValues
// users reset default values in the jcard or command lines
GOption::GOption(string n, string d, json j, bool g, string h):
name{n},
description{d},
joptionDefinition{j},
groupable{g},
help{h},
verbosity{1}
{
	// assigning non structured option with default values
	if (! joptionDefinition.begin().value().is_structured()) {
		json jValue;
		// what if joptionDefinition[JSONTAGNAME] does not exist?
		string jKey  = joptionDefinition[JSONTAGNAME];
		jValue[jKey] = joptionDefinition[JSONTAGDFLT];
		jUserValues.push_back(jValue);
		
		return;
	}
	
	// assigning structured option with default values
	// checking that all tags in the definition default values
	// if one tag has JSONTAGDFLT = NODEFAULT then the constructor will return
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		
		if ( definitionJsonValue[JSONTAGDFLT] == NODEFAULT ) {
			// nothing to do, user will have to define this option
			return;
		}
	}
	
	// we didn't return from the loop above:
	// all tags have a default value. Building the json value.
	json newUserValue;
	
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		string optionKey        = definitionJsonValue[JSONTAGNAME];
		newUserValue[optionKey] = definitionJsonValue[JSONTAGDFLT];
	}
	
	jUserValues.push_back(newUserValue);
}




// parse user jsons options and assign jValues accordingly
// this returns false if:
// - a tag was not defined
// - add- was used for a non groupable option
// - user did not provide a value that must be set (options w/o default values)
//
// These options come ordered
// if a groupable option didn't have the add directive, jValues is cleared
bool GOption::parseJsons(string userJsonKey, json userJsons, bool isAddition, int gverbosity)
{
	// clear jValues if add- is not found
	if (!isAddition && jUserValues.size() > 0 ) {
		if (gverbosity) {
			cout << GWARNING << " No add directive for a groupable option. Resetting option: clearing jValues. " << endl;
		}
		jUserValues.clear();
	}
	
	// looping over all user jsons
	for(auto &userJson: userJsons) {
		
		// buidling new value to add to jValues
		json newUserValue;
		
		// if a simple key/value option (not is_structured) then assigning the new user value and return true
		if (! userJson.is_structured() ) {
			jUserValues.clear();
			newUserValue[userJsonKey] = userJson.items().begin().value();
			jUserValues.push_back(newUserValue);
			
			if (gverbosity) {
				cout << TGREENPOINTITEM << "Json Option " << GREENHHL << userJsonKey << RSTHHR << " set with value: " << userJson.items().begin().value() <<  endl;
			}
			
			// done
			return true;
		}
		
		// userJsons is structured. Let's proceed
		if (gverbosity) {
			cout << TGREENPOINTITEM << "Json Option " << userJson << endl;
		}
		
		// if add- was found but option is not groupable, it's a mistake.
		if (isAddition && !groupable) {
			cout << GWARNING << " Trying to adding to the non groupable option " << YELLOWHHL << name << RSTHHR". This will be ignored." << endl;
			return false;
		}
		
		// first checking that all user tags are valid entries.
		for (auto& [userJsonKey, userJsonValue] : userJson.items()) {
			
			
			// checking if userJsonKey is defined
			if ( !isTagDefined(userJsonKey, gverbosity) )  {
				cout << GWARNING  " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is not known to this system. This will be ignored." << endl;
				return false;
			}
			
			// tag is defined, can assign value
			if (gverbosity > 1) {
				cout << TTPOINTITEM << " Assingning single user key " << userJsonKey << " with single value: " << userJsonValue << endl;
			}
			
			// tag is valid, assigning key and value to new user option
			newUserValue[userJsonKey] = userJsonValue;
			
		}
		
		// at this point all json keys are valid.
		// we need to assign default values for all the keys the user didn't set
		// if some of the unset values must provide a default, this routine will return false
		
		// looking for unset keys
		for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items())  {
			
			bool tagFound = false;
			string tagToCheck = definitionJsonValue[JSONTAGNAME] ;
			for (auto& [userJsonKey, userJsonValue] : newUserValue.items()) {
				if (userJsonKey == tagToCheck) {
					tagFound = true;
				}
			}
			
			// tag value not defined. Exiting if it was mandatory
			if(!tagFound) {
				
				if (definitionJsonValue[JSONTAGDFLT] == NODEFAULT) {
					cerr << FATALERRORL << tagToCheck <<  " in " << userJson << " is marked mandatory but it's not set. Exiting. " << endl;
					exit(EXIT_FAILURE);
				}
				
				newUserValue[tagToCheck] = definitionJsonValue[JSONTAGDFLT];
				
			}
		}
		
		// no unset key found
		
		jUserValues.push_back(newUserValue);
		
	}
	
	
	return true;
}


// checking if the key is the json object is defined
bool GOption::isTagDefined(string key, int gverbosity) {
	
	bool isDefined = false;
	
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		
		// if it's a JSON object
		string jsonTagName = definitionJsonValue[JSONTAGNAME];
		if (gverbosity > 3) {
			cout << TTPOINTITEM << " Checking user key " << key << " against definition item tag " << jsonTagName << endl;
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


// print option
void GOption::printOption(bool withDefaults)
{
	if (!jUserValues.size()) {
		return;
	}

	// this is a single option, jValue has size 1
	if (jUserValues.front().size() == 1) {
		json onlyOption = jUserValues.front();
		string isDefault = "";
		
		// pointing out this is a default option
		if (onlyOption.begin().value() == joptionDefinition[JSONTAGDFLT]) {
			isDefault = " (default)";
		}
		
		cout << KGRN << ARROWITEM << onlyOption.begin().key() << RST << ": " << onlyOption.begin().value() << isDefault  <<  endl;
		return;
	}

	// not the only option
	// structured option
	cout << KGRN << ARROWITEM << name << RST << ":" << endl;
	cout << TPOINTITEM << "help: " << help << endl;
	cout << TPOINTITEM << "verbosity: " << verbosity << endl;

	// non groupable options are printed on screen differently
	for (auto& jValue: jUserValues) {
		
		if (groupable) {
			cout << TPOINTITEM ;
			for (auto& [jValueKey, jValueValue] : jValue.items()) {
				cout << jValueKey << ": " << jValueValue << "\t";
			}
			cout << endl;
		} else {
			for (auto& [jValueKey, jValueValue] : jValue.items()) {
				cout << TPOINTITEM << jValueKey << ": " << jValueValue << endl;
			}
		}
	}
}
