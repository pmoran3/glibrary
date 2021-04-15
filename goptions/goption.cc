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

// constructor for structured option
// if an option is defined with default values, it will be passed to jUserValues
// users reset default values in the jcard or command lines
GOption::GOption(string n, string d, json j, string h, bool m):
name{n},
description{d},
joptionDefinition{j},
help{h},
multiple{m}
{
	// don't do anything if any tag has GDFLT = NODFLT
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {

		if ( definitionJsonValue[GDFLT] == NODFLT ) {
			// nothing to do, user will have to define this option
			return;
		}
	}

	// all tags in this option have default values
	// assigning structured option default values
	json newUserValue;

	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {
		string optionKey        = definitionJsonValue[GNAME];
		newUserValue[optionKey] = definitionJsonValue[GDFLT];
	}

	jOptionAssignedValues.push_back(newUserValue);
}




// parse user jsons options and assign jValues accordingly
// this exits if:
//
// - a tag is not defined
// - add- was not used for a multiple option
// - add- was used for a non multiple option
// - user did not provide a value that must be set (options w/o default values)
//
// These options come ordered
// if a groupable option didn't have the add directive, jValues is cleared
void GOption::assignValuesFromJson(string userJsonKey, json userJsonValues, bool isAddition, bool gdebug, bool gstrict)
{

	// clear jValues if add- is not found
	// and the option is multiple
	if (!isAddition && multiple ) {
		cout << FATALERRORL  " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is multiple. Mandatory \"add-\" directive was not given. " << endl;
		gexit(NOADDFORMULTIPLE);
	}

	// if add- was found but option is not multiple, it's a mistake.
	if (isAddition && !multiple) {
		cout << FATALERRORL  " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is non multiple but \"add-\" was given. " << endl;
		gexit(ADDFORNONMULTIPLE);
	}

	// looping over all user jsons
	for(auto &userJsonValue: userJsonValues) {
		
		// building new value to add to jOptionAssignedValues
		json newUserValue;
		
		// non structured option
		if ( ! userJsonValue.is_structured() ) {

			checkTagIsValid(userJsonKey, gdebug);

			if ( jOptionAssignedValues.size() ) {
				// strict: error
				if ( gstrict ) {
					cout << FATALERRORL " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is non multiple and is already present." << endl;
					gexit(NONMULTIPLEFOUND);
					// non strict: warning and clear
					// the last appereance of the option is the valid one
				} else {
					cout << GWARNING " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is non multiple but \"add-\" was given. " << endl;
					jOptionAssignedValues.clear();
				}
			}


			if ( gdebug ) {
				cout << TGREENPOINTITEM << " Assigning Json Option " << GREENHHL << userJsonKey << RSTHHR << " set with value: " << userJsonValue.items().begin().value() <<  endl;
			}

			// valid, assigning it
			newUserValue[userJsonKey] = userJsonValue.items().begin().value();
			jOptionAssignedValues.push_back(newUserValue);
			

			// done, return
			return;
		}
		
		// userJsons is structured.
		if ( gdebug ) {
			cout << TGREENPOINTITEM << "Json Option Value: " << userJsonValue << endl;
		}
		

		// first checking that all user tags are valid entries.
		// if it's valid, assigning the value
		for (auto& [userJsonKeyInValues, userJsonValueInValues] : userJsonValues.items()) {

			checkTagIsValid(userJsonKeyInValues, gdebug);

			// tag is defined, can assign value
			if ( gdebug ) {
				cout << TTPOINTITEM << " Assingning single user key " << userJsonKeyInValues << " with single value: " << userJsonValue << endl;
			}
			
			// tag is valid, assigning key and value to new user option
			newUserValue[userJsonKeyInValues] = userJsonValueInValues;
		}
		
		// at this point all json keys are valid, and the user json keys are assigned properly
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
		// adding the newUserValue
		jOptionAssignedValues.push_back(newUserValue);
		
	}

}


// checking if the key is the json object is defined
void GOption::checkTagIsValid(string key, bool gdebug) {
	
	bool isDefined = false;

	// joptionDefinition is a json
	// Example: {
	//    { GNAME: "runno",    GDESC: "run number",       GDFLT: 11},
	//    { GNAME: "nthreads", GDESC: "number of thrads", GDFLT: 4}
	// }
	// matching key to GNAME definition
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {

		if ( definitionJsonKey == GNAME) {

			if ( gdebug ) {
				cout << TTPOINTITEM << " Checking user key " << key << " against definition item tag " << definitionJsonValue << endl;
			}

			if (key == definitionJsonValue) {
				if ( gdebug ) {
					cout << TTPOINTITEM << key << " matches " << definitionJsonValue << endl;
				}
				isDefined = true;
			}
		}
	}
	if ( !isDefined )  {
		cout << FATALERRORL  " the " << YELLOWHHL << key << RSTHHR << " tag is not known to this system. " << endl;
		gexit(NOOPTIONFOUND);
	}

}

// true if the option is a simple option
bool GOption::isSimpleption() {

	bool isSimple = false;

	if ( jOptionAssignedValues.size() == 1 ) {
		if ( jOptionAssignedValues.front().size() == 1 ) {
			isSimple = true;
		}

	}

	return isSimple;
}


// print option
void GOption::printOption(bool withDefaults)
{
	if (!jOptionAssignedValues.size()) {
		return;
	}

	//if ( gdebug ) {
//		cout << TTGREENARROWITEM << "jOptionAssignedValues size: " <<  jOptionAssignedValues.size() << endl;
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
		
		if (multiple) {
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
