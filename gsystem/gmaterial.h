#ifndef  GMATERIAL_H
#define  GMATERIAL_H 1

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

class GMaterial
{
public:
	GMaterial(string system, vector<string> pars);

private:
	string         system; ///< System of provenience
	string           name; ///< Name of the material
	string    description; ///< Volume Description, for documentation

	// material properties
	// the material is recorded with a string 'components'
	// that contains both the element (material) name and its number of atoms (fractional mass)
	//
	// examples:
	// C 9 H 10
	// G4_N 0.7 G4_O 0.3
	//
	double         density;            ///< Material density, in g/cm3
	vector<string> components;         ///< The list of atoms/material
	vector<double> amounts;            ///< Each component quantity or fractional mass

	// optical properties
	vector<double> photonEnergy;       ///< A list of photon energies with units, at which any other optical parameters will be evaluated
	vector<double> indexOfRefraction;  ///< A list of the refractive index evaluated at the energies named in photonEnergy
	vector<double> absorptionLength;   ///< A list of the material absorption length with units, evaluated at the energies in photonEnergy
	vector<double> reflectivity;       ///< A list of reflectivity values evaluated at the energies in photonEnergy
	vector<double> efficiency;         ///< A list of absorption efficiency evaluated at the energies in photonEnergy

	// scintillation properties
	vector<double> fastcomponent;      ///< A list of the fast component relative spectra values evaluated at the energies in photonEnergy
	vector<double> slowcomponent;      ///< A list of the fast component relative spectra values evaluated at the energies in photonEnergy
	double         scintillationyield; ///< Characteristic light yield in photons/MeV e-, given as a single number
	double         resolutionscale;    ///< Resolution scale broadens the statistical distribution of generated photons
	double         fasttimeconstant;   ///< FIX ME believe this is related to the scintillator pulse rise time.
	double         slowtimeconstant;   ///< FIX ME believe this is related to scintillator slow decay time.
	double         yieldratio;         ///< Relative strength of the fast component as a fraction of total scintillation yield, given as a single number
	double         birkConstant;       ///<  FIX ME

	// other optical properties
	vector<double> rayleigh;           ///< A list of the Rayleigh scattering attenuation coefficient evaluated at the energies in photonEnergy

	// load material components from DB entry
	void setComponentsFromString(string composition);

	// load optical properties from DB entry
	void opticalsFromString(string, string);

	friend ostream &operator<<(ostream &stream, GMaterial); ///< Logs infos on screen.

public:
	// getters
	inline const string getName()         const {return name;}
	inline const string getDescription()  const {return description;}

	
	inline const int            getNcomponents()        const;
	inline const double         getDensity()            const {return density;}
	inline const vector<string> getComponents()         const {return components;}
	inline const vector<double> getAmounts()            const {return amounts;}

	// optical properties
	inline const vector<double> getPhotonEnergy()       const {return photonEnergy;}
	inline const vector<double> getIndexOfRefraction()  const {return indexOfRefraction;}
	inline const vector<double> getAbsorptionLength()   const {return absorptionLength;}
	inline const vector<double> getReflectivity()       const {return reflectivity;}
	inline const vector<double> getEfficiency()         const {return efficiency;}

	// scintillation properties
	inline const vector<double> getFastcomponent()      const {return fastcomponent;}
	inline const vector<double> getSlowcomponent()      const {return slowcomponent;}
	inline const double         getScintillationyield() const {return scintillationyield;}
	inline const double         getResolutionscale()    const {return resolutionscale;}
	inline const double         getFasttimeconstant()   const {return fasttimeconstant;}
	inline const double         getSlowtimeconstant()   const {return slowtimeconstant;}
	inline const double         getYieldratio()         const {return yieldratio;}
	inline const double         getBirkConstant()       const {return birkConstant;}

	// other optical properties
	inline const vector<double> getRayleigh()           const {return rayleigh;}

};


#endif
