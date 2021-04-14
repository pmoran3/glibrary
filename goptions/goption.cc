// goptions
#include "goptions.h"

// c++
#include <iostream>


// exiting with error, print error on screen.
void gexit(int error) {
	cerr << KBOLD << KRED << " Exiting with error " << error << RST << endl;
	exit(error);
}


// constructor for simple option
// if an option is defined with default values, it will be passed to jUserValues
// users reset default values in the jcard or command lines
GOption::GOption(json j):
name{j[GNAME]},
description{j[GDESC]},
joptionDefinition{j},
help{j[GDESC]},
multiple{false}
{
	// assigning defaults values 
	json jValue;

	// by constructon the keys will be there
	string jKey  = joptionDefinition[GNAME];
	jValue[jKey] = joptionDefinition[GDFLT];
	jOptionAssignedValues.push_back(jValue);

	return;
}

// if an option is defined with default values, it will be passed to jUserValues
// users reset default values in the jcard or command lines
GOption::GOption(string n, string d, json j, string h, bool m):
name{n},
description{d},
joptionDefinition{j},
help{h},
multiple{m}
{
	// skipping assigning value if the any tag has GDFLT = NODFLT (constructor will return w/o push_back)
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {

		if ( definitionJsonValue[GDFLT] == NODFLT ) {
			// nothing to do, user will have to define this option
			return;
		}
	}

	// assigning structured option  default values
	json newUserValue;

	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		string optionKey        = definitionJsonValue[GNAME];
		newUserValue[optionKey] = definitionJsonValue[GDFLT];
	}

	jOptionAssignedValues.push_back(newUserValue);

}




// parse user jsons options and assign jValues accordingly
// this returns false if:
// - a tag was not defined
// - add- was used for a non groupable option
// - user did not provide a value that must be set (options w/o default values)
//
// These options come ordered
// if a groupable option didn't have the add directive, jValues is cleared
bool GOption::assignValuesFromJson(string userJsonKey, json userJsonValue, bool isAddition, int gdebug)
{
	// clear jValues if add- is not found
	// and the option is groupable
	if (!isAddition && groupable ) {
		if (gdebug) {
			cout << GWARNING << " No add directive for groupable. Resetting option: clearing jValues. " << endl;
		}
		jOptionAssignedValues.clear();
	}
	
	// looping over all user jsons
	for(auto &
		 userJsonValue: userJsonValue) {
		
		// building new value to add to jValues
		json newUserValue;
		
		// if a simple key/value option (not is_structured) then assigning the new user value and return true
		// the last appereance of the option is the valid one
		if (! userJsonValue.is_structured() ) {
			jOptionAssignedValues.clear();
			newUserValue[userJsonKey] = userJsonValue.items().begin().value();
			jOptionAssignedValues.push_back(newUserValue);
			
			if (gdebug) {
				cout << TGREENPOINTITEM << "Json Option " << GREENHHL << userJsonKey << RSTHHR << " set with value: " << userJsonValue.items().begin().value() <<  endl;
			}
			
			// done, return
			return true;
		}
		
		// userJsons is structured.
		if (gdebug) {
			cout << TGREENPOINTITEM << "Json Option Value: " << userJsonValue << endl;
		}
		
		// if add- was found but option is not groupable, it's a mistake.
		if (isAddition && !groupable) {
			cout << GWARNING << " Trying to adding to the non groupable option " << YELLOWHHL << name << RSTHHR". This will be ignored." << endl;
			return false;
		}
		
		// first checking that all user tags are valid entries.
		for (auto& [userJsonKey, userJsonValue] : userJsonValue.items()) {

			// checking if userJsonKey is defined
			// exiting if the tag is not defined
			if ( !isTagDefined(userJsonKey, gdebug) )  {
				cout << FATALERRORL  " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is not known to this system. " << endl;
				gexit(NOOPTIONFOUND);
			}
			
			// tag is defined, can assign value
			if (gdebug > 1) {
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
					cerr << FATALERRORL << tagToCheck <<  " in " << userJsonValue << " is marked mandatory but it's not set." << endl;
					gexit(MANDATORYOPTIONNOTFOUND);
				}
				// assigning its default value
				newUserValue[tagToCheck] = definitionJsonValue[GDFLT];
				
			}
		}
		
		// no unset key found at this point
		jOptionAssignedValues.push_back(newUserValue);
		
	}
	
	
	return true;
}


// checking if the key is the json object is defined
bool GOption::isTagDefined(string key, int gdebug) {
	
	bool isDefined = false;
	
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		
		// if it's a JSON object
		string jsonTagName = definitionJsonValue[GNAME];
		if (gdebug) {
			cout << TTPOINTITEM << " Checking user key " << key << " against definition item tag " << jsonTagName << endl;
		}
		
		if (key == jsonTagName) {
			if (gdebug) {
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
	if (!jOptionAssignedValues.size()) {
		return;
	}

	//if (gdebug) {
		cout << TTGREENARROWITEM << "jOptionAssignedValues size: " <<  jOptionAssignedValues.size() << endl;
	//}


	// non structured option (jValue has size 1)
	if (jOptionAssignedValues.front().size() == 1) {
		json onlyOption = jOptionAssignedValues.front();
		string isDefault = "";
		
		// pointing out this is a default option
		if (onlyOption.begin().value() == joptionDefinition[GDFLT]) {
			isDefault = " (default)";
		}
		
		cout << KGRN << ARROWITEM << onlyOption.begin().key() << RST << ": " << onlyOption.begin().value() << isDefault << endl;
		return;
	}

	// structured option
	cout << KGRN << ARROWITEM << name << RST << ":" << endl << endl;

	// non groupable options are printed on screen differently
	for (auto& jValue: jOptionAssignedValues) {
		
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
			cout << endl;
		}
	}
}
