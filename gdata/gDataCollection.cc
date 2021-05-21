// gdata
#include "gDataCollection.h"

// public interface to add hit
void GDataCollection::addDigitizedData(GDigitizedData *dgtzData) {
	digitizedData->push_back(dgtzData);
}
