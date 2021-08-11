#ifndef  GVOLUME_H
#define  GVOLUME_H 1

// conventions
#include "gsystemConventions.h"

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
	string getName()       {return name;}
	string getMapName()    {
		if (mother == MOTHEROFUSALL) {
			return ROOTWORLDGVOLUMENAME;
		}
		return system + "/" + name;
	}
	string getMother()     {return mother;}
	string getMotherMapName()     {
		if (mother == ROOTWORLDGVOLUMENAME) {
			return ROOTWORLDGVOLUMENAME;
		} else if (mother == MOTHEROFUSALL) {
			return MOTHEROFUSALL;
		}
		return system + "/" + mother;
	}


	string getType()       {return type;}
	string getParameters() {return parameters;}
	string getMaterial()   {return material;}
	int    getPCopyNo()    {return pCopyNo;}
	string getColor()      {return color;}
	bool   isVisible()     {return visible;}
	int    getStyle()      {return style;}

	string getPos()   {return pos;}
	string getRot()   {return rot;}
	string getShift() {return shift;}
	string getTilt()  {return tilt;}

	string  getDigitization(){return digitization;}
	string  getGIdentity() {return gidentity;}

	// special cases
	string getCopyOf()     {return copyOf;}
	string getReplicaOf()  {return replicaOf;}
	string getSolidsOpr()  {return solidsOpr;}

	// assign modifier
	void applyShift(string s)    {shift = s;}
	void applyTilt(string t)     {tilt  = t;}
	void modifyExistence(bool e) {exist = e;}

	// imported volumes
	string getImportedFile() {return importFilename;}
};


#endif
