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
cumulative{false}
{
	// assigning defaults values 
	json jValue;

	// by constructon the keys will always be there
	auto defaultValue = joptionDefinition[GDFLT];

	if ( defaultValue != NODFLT ) {
		string jKey  = joptionDefinition[GNAME];
		jValue[jKey] = defaultValue;
		jOptionAssignedValues.push_back(jValue);
		isDefault = true;
	}
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
cumulative{m}
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
		isDefault               = true;
	}

	jOptionAssignedValues.push_back(newUserValue);
}




// parse user jsons options and assign jValues accordingly
// this exits if:
//
// - a tag is not defined
// - add- was not used for a cumulative option
// - add- was used for a non cumulative option
// - user did not provide a value that must be set (options w/o default values)
//
// These options come ordered
// if a groupable option didn't have the add directive, jValues is cleared
void GOption::assignValuesFromJson(string userJsonKey, json userJsonValues, bool isAddition, bool gdebug, bool gstrict)
{
	// clear jValues if add- is not found
	// and the option is cumulative
	if ( !isAddition && cumulative ) {
		cout << FATALERRORL  " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is cumulative. Mandatory \"add-\" directive was not given. " << endl;
		gexit(NOADDFORCUMULATIVE);
	}

	// if add- was found but option is not cumulative, it's a mistake.
	if ( isAddition && !cumulative ) {
		cout << FATALERRORL  " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is non cumulative but \"add-\" was given. " << endl;
		gexit(ADDFORNONCUMULATIVE);
	}

	// simple option
	if ( ! userJsonValues.is_structured() ) {

		// if userJsonValue is default, nothing to do
		if ( isDefaultValue(userJsonKey, userJsonValues) ) {
			if ( gdebug ) {
				cout << TGREENPOINTITEM << "Simple option " << YELLOWHHL << userJsonKey << RSTHHR << " is assigned the default value. " << userJsonValues << ". Nothing to do." << endl;
			}
			return;
		}

		assignSingleValueFromSimpleJson(userJsonKey, userJsonValues, gdebug, gstrict);

	} else {

		json newUserValue;

		// structure option, looping over tags
		// looping over all user jsons
		for (auto& [userJsonKeyInValues, userJsonValueInValue] : userJsonValues.items()) {

//			// if userJsonValue is default, nothing to do
//			if ( isDefaultValue(userJsonKey, userJsonValue) ) {
//				if ( gdebug ) {
//					cout << TGREENPOINTITEM << "Structure option option " << YELLOWHHL << userJsonKey << RSTHHR << " is assigned the default value. " << userJsonValue << ". Nothing to do." << endl;
//				}
//				return;
//			}

			newUserValue[userJsonKey] = assignSingleValueFromStructuredJson(userJsonKey, userJsonKeyInValues, userJsonValueInValue, gdebug, gstrict);
		}

		// at this point all json keys are valid, and the user json keys are assigned properly
		// we need to assign default values for all the keys the user didn't set
		// if some of the unset values option must provide a default, this routine will exit


		// looking for unset keys in the option definition
		for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items())  {

			bool thisTagWasFoundAndAssigned = false;

			// looping over tags inside option
			for ( auto& jsonTagValue : definitionJsonValue.items() )  {

				if ( jsonTagValue.key() == GNAME ) {
					string tagToCheck = jsonTagValue.value() ;

					if ( gdebug ) {
						cout << TGREENPOINTITEM << "Checking if user key " << YELLOWHHL << tagToCheck << RSTHHR << " is assigned " << endl;
					}


				}


				//			if ( jsonTagValue.key() == GNAME && key == jsonTagValue.value() ) {
				//				if ( gdebug ) {
				//					cout << TTPOINTITEM << key << "key matches " << jsonTagValue.value() << endl;
				//				}
				//				isDefined = true;
				//			}

			}




			//		for (auto& [userJsonKey, userJsonValue] : newUserValue.items()) {
			//
			//			// user assigned an option definition
			//			if (userJsonKey == tagToCheck) {
			//				thisTagWasFoundAndAssigned = true;
			//			}
			//		}
			//
			//		// tag value not defined.
			//		// Exiting if it was mandatory.
			//		// assign the default value if
			//		if(!thisTagWasFoundAndAssigned) {
			//
			//			if (definitionJsonValue[GDFLT] == NODFLT) {
			//				cerr << FATALERRORL << tagToCheck <<  " in " << userJsonValue << " is marked mandatory but it's not set." << endl;
			//				gexit(MANDATORYOPTIONNOTFOUND);
			//			}
			//			// assigning its default value
			//			newUserValue[tagToCheck] = definitionJsonValue[GDFLT];
			//
			//		}
		}



		// no unset key found at this point
		// adding the newUserValue
		// valid, non default assigning it
		jOptionAssignedValues.clear();
		jOptionAssignedValues.push_back(newUserValue);
		isDefault = false;
	}



}


void GOption::assignSingleValueFromSimpleJson(string userJsonKey, json userJsonValue, bool gdebug, bool gstrict) {

	// userJsons is simple
	if ( gdebug ) {
		cout << TGREENPOINTITEM << "Assigning simple option " << BOLDWHHL << userJsonKey << RSTHHR << " with " << userJsonValue << endl;
	}

	checkTagIsValid(userJsonKey, gdebug);

	// overwriting simple options is allowed if gstrict is not set.
	// a warning is given
	if ( jOptionAssignedValues.size() && !isDefault ) {
		// strict: error
		if ( gstrict ) {
			cout << FATALERRORL " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is non cumulative, is already present, and it's not the default. " << endl;
			gexit(NONCUMULATIVEALREADYPRESENT);
			// non strict: warning and clear
			// the last appereance of the option is the valid one
		} else {
			cout << GWARNING " the " << YELLOWHHL << userJsonKey << RSTHHR << " tag is non cumulative and is already present, and it's not the default." << endl;
		}
	}

	json newUserValue;
	auto assignedValue = userJsonValue.items().begin().value();

	// tag is valid, assigning it
	newUserValue[userJsonKey] = assignedValue;
	if ( gdebug ) {
		cout << TGREENPOINTITEM << " Json Option " << GREENHHL << userJsonKey << RSTHHR << " set with value: " << assignedValue <<  endl;
	}

	// valid, non default assigning it
	jOptionAssignedValues.clear();
	jOptionAssignedValues.push_back(newUserValue);
	isDefault = false;
}


json GOption::assignSingleValueFromStructuredJson(string userJsonKey, string tagInJsonValues, json userJsonValue, bool gdebug, bool gstrict) {

	// userJsons is structured
	if ( gdebug ) {
		cout << TGREENPOINTITEM << "Assigning structured option " << BOLDWHHL << userJsonKey << RSTHHR << endl;
	}

	checkTagIsValid(tagInJsonValues, gdebug);

	// tag is valid, returning it
	if ( gdebug ) {
		cout << TTPOINTITEM << "Assigning single user key " << YELLOWHHL << tagInJsonValues << RSTHHR << " with value: " << userJsonValue << endl;
	}

	return userJsonValue;
}


// check if userValue matches the default value
bool GOption::isDefaultValue(string key, json userValue) {

	// false if there is no default
	if ( ! isDefault ) return false;

	bool isUserDefault = false;

	// simple option
	if ( ! userValue.is_structured() ) {
		auto defaultValue =  jOptionAssignedValues.front().items().begin().value();

		// looking for unset keys in the option definition
		// Example: { GNAME: "runno", GDESC: "run number", GDFLT: 11 }
		for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items())  {

			// user assigned an option definition
			if ( key == definitionJsonValue ) {
				if ( userValue == defaultValue ) {
					isUserDefault = true;
				}
			}
		}
	} else {

	}


	return isUserDefault;
}


// checking if the key is the json object is defined
void GOption::checkTagIsValid(string key, bool gdebug) {
	
	bool isDefined = false;

	// joptionDefinition is a json
	// Non Structured Example: { GNAME: "runno",  GDESC: "run number", GDFLT: 11} }
	//
	// Structured Example: {
	//    { GNAME: "runno",    GDESC: "run number",       GDFLT: 11},
	//    { GNAME: "nthreads", GDESC: "number of thrads", GDFLT: 4}
	// }
	for (auto& [definitionJsonKey, definitionJsonValue] : joptionDefinition.items()) {

		// non structured option first
		// matching key to GNAME definition
		if ( !definitionJsonValue.is_structured() ) {

			if ( gdebug ) {
				cout << TTPOINTITEM << "Checking user key " << key << " against definition item tag " << definitionJsonValue << endl;
			}

			if ( definitionJsonKey == GNAME) {

				if (key == definitionJsonValue) {
					if ( gdebug ) {
						cout << TTPOINTITEM << key << "key matches " << definitionJsonValue << endl;
					}
					isDefined = true;
				}
			}

			// structured option
			// when key is GNAME, matching key to definition value
		} else {

			for ( auto& jsonTagValue : definitionJsonValue.items() )  {
				if ( jsonTagValue.key() == GNAME && key == jsonTagValue.value() ) {
					if ( gdebug ) {
						cout << TTPOINTITEM << key << "key matches " << jsonTagValue.value() << endl;
					}
					isDefined = true;
				}
			}
		}
	}

	if ( !isDefined )  {
		cout << FATALERRORL  " the " << YELLOWHHL << key << RSTHHR << " tag is not known to this system. " << endl;
		gexit(NOOPTIONFOUND);
	}

}


// print option
void GOption::printOption(bool withDefaults)
{
	if (!jOptionAssignedValues.size()) {
		return;
	}

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
		
		if (cumulative) {
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
