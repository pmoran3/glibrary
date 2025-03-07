#ifndef  GVOLUME_H
#define  GVOLUME_H 1

// conventions
#include "gsystemConventions.h"

// glibrary, namespace for the inline functions below
#include "gutilities.h"
using namespace gutilities;

// c++
#include <string>
using std::string;
using std::ostream;
using std::vector;

class GVolume
{
public:
	GVolume(string system, vector<string> pars, string importPath = UNINITIALIZEDSTRINGQUANTITY);
	GVolume(string rootVolumeDefinition); // special constructor for root volume

private:
	string         system; ///< System of provenience
	string           name; ///< Name of the volume
	string         mother; ///< Mother Volume name
	string    description; ///< Volume Description, for documentation
	string importFilename; ///< For imports, filename with path, set with the import factory
	
	// solid parameters
	string        type;    ///< solid type. This follows the GEANT4 definitions
	string  parameters;    ///< vector of parameters used in the geant4 solid constructor

	// solid visualization style
	bool        visible;   ///< visibility of the detector: 0=invisible 1=visible
	int           style;   ///< Visual style: 0=wireframe 1=solid
	string        color;   ///< 6(7) digits colors in RRGGBB format. Last optional digit is transparency

	// logical attributes
	string     material;   ///< Volume Material name.
	string     emfield;    ///< Magnetic Field. Possible choices: "inherit", "fieldName", "noField"

	// physical attributes
	string          pos;   ///< Defines the position relative to the mother volume
	string          rot;   ///< Define the rotation Matrix, defined by rotations along x,y,z axis relative to the mother volume
	string        shift;   ///< Position modifier
	string         tilt;   ///< Rotation modifier
	bool          exist;   ///< Existance modifier

	string  digitization;   ///< Assigns digitization type and collection ID
	string  gidentity;      ///< String with identifiers in it. Example: 'sector: 2, layer: 4, wire; 33'

	// special cases
	string       copyOf;   ///< name of gvolume to copy from
	string    replicaOf;   ///< name of gvolume to replica from
	string    solidsOpr;   ///< solids operation
	
	int         pCopyNo;   ///< should be set to 0 for the first volume of a given type

	// mirrors
	string       mirror;

	friend ostream &operator<<(ostream &stream, GVolume); ///< Logs infos on screen.

public:
	inline const string getName() const {return name;}
	inline const string getMapName() const {
		if (mother == MOTHEROFUSALL) {
			return ROOTWORLDGVOLUMENAME;
		}
		return system + "__" + name;
	}
	inline const string getMother() const {return mother;}
	inline const string getMotherMapName() const {
		if (mother == ROOTWORLDGVOLUMENAME) {
			return ROOTWORLDGVOLUMENAME;
		} else if (mother == MOTHEROFUSALL) {
			return MOTHEROFUSALL;
		}
		return system + "__" + mother;
	}

	inline vector<double> getDetectorDimensions() const {return getG4NumbersFromString(parameters);}

	inline const string getType()       const {return type;}
	inline const string getParameters() const {return parameters;}
	inline const string getMaterial()   const {return material;}
	inline const int    getPCopyNo()    const {return pCopyNo;}
	inline const string getColor()      const {return color;}
	inline const bool   isVisible()     const {return visible;}
	inline const int    getStyle()      const {return style;}

	inline const string getPos()   const {return pos;}
	inline const string getRot()   const {return rot;}
	inline const string getShift() const {return shift;}
	inline const string getTilt()  const {return tilt;}

	inline const string  getDigitization() const {return digitization;}
	inline const string  getGIdentity()    const {return gidentity;}

	// special cases
	inline const string getCopyOf()     const {return copyOf;}
	inline const string getReplicaOf()  const {return replicaOf;}
	inline const string getSolidsOpr()  const {return solidsOpr;}

	inline const string getDescription()  const {return description;}

	// assign modifier
	void applyShift(string s)    {shift = s;}
	void applyTilt(string t)     {tilt  = t;}
	void modifyExistence(bool e) {exist = e;}

	// imported volumes
	string getImportedFile() {return importFilename;}
};


#endif
