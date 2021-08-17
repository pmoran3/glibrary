#ifndef  GVOLUME_H
#define  GVOLUME_H 1

// conventions
#include "gsystemConventions.h"

// glibrary
#include "gutilities.h"
using namespace gutilities;

// c++
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;

class GVolume
{
public:
	GVolume(string s, vector<string> pars, string importPath = GSYSTEMNOTAPPLICABLEENTRY);
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
	inline string getName() const {return name;}
	inline string getMapName() const {
		if (mother == MOTHEROFUSALL) {
			return ROOTWORLDGVOLUMENAME;
		}
		return system + "__" + name;
	}
	inline string getMother() const {return mother;}
	inline string getMotherMapName() const {
		if (mother == ROOTWORLDGVOLUMENAME) {
			return ROOTWORLDGVOLUMENAME;
		} else if (mother == MOTHEROFUSALL) {
			return MOTHEROFUSALL;
		}
		return system + "__" + mother;
	}

	inline vector<double> getDetectorDimensions() const {return getG4NumbersFromString(parameters);}

	inline string getType()       const {return type;}
	inline string getParameters() const {return parameters;}
	inline string getMaterial()   const {return material;}
	inline int    getPCopyNo()    const {return pCopyNo;}
	inline string getColor()      const {return color;}
	inline bool   isVisible()     const {return visible;}
	inline int    getStyle()      const {return style;}

	inline string getPos()   const {return pos;}
	inline string getRot()   const {return rot;}
	inline string getShift() const {return shift;}
	inline string getTilt()  const {return tilt;}

	inline string  getDigitization() const {return digitization;}
	inline string  getGIdentity()    const {return gidentity;}

	// special cases
	inline string getCopyOf()     const {return copyOf;}
	inline string getReplicaOf()  const {return replicaOf;}
	inline string getSolidsOpr()  const {return solidsOpr;}

	// assign modifier
	void applyShift(string s)    {shift = s;}
	void applyTilt(string t)     {tilt  = t;}
	void modifyExistence(bool e) {exist = e;}

	// imported volumes
	string getImportedFile() {return importFilename;}
};


#endif
