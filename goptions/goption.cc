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
help{h}
{
	// assigning non structured option with their defaults values
	if (! joptionDefinition.begin().value().is_structured()) {
		json jValue;
		// by constructon the keys will be there
		string jKey  = joptionDefinition[GNAME];
		jValue[jKey] = joptionDefinition[GDFLT];
		jUserValues.push_back(jValue);
		
		return;
	}
	
	// skipping structured options if the tag has GDFLT = NODFLT (constructor will return w/o push_back)
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		
		if ( definitionJsonValue[GDFLT] == NODFLT ) {
			// nothing to do, user will have to define this option
			return;
		}
	}
	
	// we didn't return from the loop above:
	// all tags have a default value. Building the default json value.
	// assigning structured option with default values
	json newUserValue;
	
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		string optionKey        = definitionJsonValue[GNAME];
		newUserValue[optionKey] = definitionJsonValue[GDFLT];
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
	// and the option is groupable (jUserValues.size())
	if (!isAddition && jUserValues.size() > 0 ) {
		if (gverbosity) {
			cout << GWARNING << " No add directive for groupable. Resetting option: clearing jValues. " << endl;
		}
		jUserValues.clear();
	}
	
	// looping over all user jsons
	for(auto &userJson: userJsons) {
		
		// building new value to add to jValues
		json newUserValue;
		
		// if a simple key/value option (not is_structured) then assigning the new user value and return true
		// the last appereance of the option is the valid one
		if (! userJson.is_structured() ) {
			jUserValues.clear();
			newUserValue[userJsonKey] = userJson.items().begin().value();
			jUserValues.push_back(newUserValue);
			
			if (gverbosity) {
				cout << TGREENPOINTITEM << "Json Option " << GREENHHL << userJsonKey << RSTHHR << " set with value: " << userJson.items().begin().value() <<  endl;
			}
			
			// done, return
			return true;
		}
		
		// userJsons is structured.
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
			// exiting if the tag is not defined
			if ( !isTagDefined(userJsonKey, gverbosity) )  {
				cout << FATALERRORL  " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is not known to this system. Exiting." << endl;
				exit(NOOPTIONFOUND);
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
		// if some of the unset values option must provide a default, this routine will exit
		
		// looking for unset keys in the option definition
		for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items())  {
			
			bool thisTagWasFoundAndAssigned = false;

			string tagToCheck = definitionJsonValue[GNAME] ;

			for (auto& [userJsonKey, userJsonValue] : newUserValue.items()) {
				// user assigned an option definition
				if (userJsonKey == tagToCheck) {
					thisTagWasFoundAndAssigned = true;
				}
			}
			
			// tag value not defined.
			// Exiting if it was mandatory.
			// assign the default value if
			if(!thisTagWasFoundAndAssigned) {
				
				if (definitionJsonValue[GDFLT] == NODFLT) {
					cerr << FATALERRORL << tagToCheck <<  " in " << userJson << " is marked mandatory but it's not set. Exiting. " << endl;
					exit(MANDATORYOPTIONNOTFOUND);
				}
				// assigning its default value
				newUserValue[tagToCheck] = definitionJsonValue[GDFLT];
				
			}
		}
		
		// no unset key found at this point
		jUserValues.push_back(newUserValue);
		
	}
	
	
	return true;
}


// checking if the key is the json object is defined
bool GOption::isTagDefined(string key, int gverbosity) {
	
	bool isDefined = false;
	
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		
		// if it's a JSON object
		string jsonTagName = definitionJsonValue[GNAME];
		if (gverbosity > 3) {
			cout << TTPOINTITEM << " Checking user key " << key << " against definition item tag " << GNAME << endl;
		}
		
		if (key == GNAME) {
			if (gverbosity > 1) {
				cout << TTGREENARROWITEM << key << " matches " << GNAME << endl;
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
		if (onlyOption.begin().value() == joptionDefinition[GDFLT]) {
			isDefault = " (default)";
		}
		
		cout << KGRN << ARROWITEM << onlyOption.begin().key() << RST << ": " << onlyOption.begin().value() << isDefault  <<  endl;
		return;
	}

	// not the only option
	// structured option
	cout << KGRN << ARROWITEM << name << RST << ":" << endl;
	cout << TPOINTITEM << "help: " << help << endl;
	//cout << TPOINTITEM << "verbosity: " << verbosity << endl;

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
