#ifndef  GFACTORY_H
#define  GFACTORY_H 1

// this code is based on TheComet tutorial here:
// https://www.gamedev.net/topic/683154-c-extend-class-in-dll/

/**
 * \mainpage
 * \section overview Overview
 * This frameworks provides static or dynamic loading of client factories.\n
 * The class GManager registers the client factories and provide methods
 * to instantiate them.
 * \section howto Suggested Use
 * After the gManager registration clients can instantiate
 * the derived class and store them in a map<string, Base>
 * for later use.
 * \section staticUse Registering and Instantiating static client factories
 * In this case the client have access to both the base and the derived class headers.
 * To register a "Triangle" class derived from "Shape":
 * <pre>
 * \#include "ShapeFactory.h"
 * \#include "Triangle.h"
 * map<string, Shape*> shapes;   // map that will contain the derived classes instances
 * GManager manager;
 * manager.RegisterObjectFactory<Triangle>("triangle");  // register class in the manager
 * map["triangle"] = manager.CreateObject<Shape>("triangle");  // retrieve "triangle", instantiate and store new client Triangle class
 * map["triangle"]->Method();  // Method() is pure virtual in Shape. Calling the instance Triangle method here
 * </pre>
 * \section dynamicUse Registering and Instantiating dynamic client factories
 * In this case the client have access to only the base class header.
 * The derived classes are compiled in shared libraries.
 * To register a "ford" class derived from "Car":
 * <pre>
 * \#include "Car.h"
 * map<string, Car*> cars;   // map that will contain the derived classes instances
 * GManager manager;
 * manager.registerDL("fordFactory");  // register class in the manager
 * map["ford"] = manager.LoadObjectFromLibrary<Car>("fordFactory");  // retrieve "fordFactory", instantiate and store new client fordFactory class
 * map["ford"]->Method();  // Method() is pure virtual in Car. Calling the instance fordFactory method here
 * </pre>
 * \section platforms Platforms Supported:
 * - Linux (32, 64)
 * - Mac OS X
 * \n\n
 * \author \n &copy; Maurizio Ungaro
 * \author e-mail: ungaro@jlab.org\n\n\n
 */

// c++
#include <map>
#include <string>
#include <iostream>
using namespace std;

// dynamic loading
#include "gdl.h"


/**
 * @class GFactoryBase
 * @brief Base class. Use polymorphism to run Create on the
 * derived classes
 */
class GFactoryBase {
public:
	/**
	 @fn Create
	 @brief Pure virtual method. Derived classes use this to instantiate themselves
	 */
	virtual void* Create() = 0;
};

/**
 * @class GFactory
 * @brief Derived from GFactoryBase, implements Create to
 * instantiate the derived classes
 */
template <class T>
class GFactory : public GFactoryBase
{
	/**
	 @fn Create
	 @brief Instantiate new client class
	 */
	virtual void* Create() override {
		return new T();
	}
};

/**
 * @class GManager
 * @brief Instantiates derived classes either statically or dynamically
 */
class GManager
{
public:
	/**
	 @param v verbosity.
	 - 0: no not print any log
	 - 1: print gmanager registering and instantiating classes
	 */
	GManager( int v = 0, string log = " ↑") : verbosity(v), logHeader(log) {}

public:
	/**
	 * @fn RegisterObjectFactory
	 * @param name name under which the factory is registered
	 *
	 * Before instantiating the wanted class we need to register
	 * it (as Derived) in the manager first using RegisterObjectFactory.\n
	 * Derived is the derived class, i.e. "Triangle" : "Shape".\n
	 * The client knows about the derived class (through header)
	 */
	template <class Derived> void RegisterObjectFactory(string name) {
		factoryMap[name] = new GFactory<Derived>();
		if(verbosity > 0) {
			cout << logHeader << " GManager: Registering " << name << " factory. Database size is now: " << factoryMap.size() << endl;
		}
	}

	/**
	 * @fn CreateObject
	 * @param name name under which the factory is registered
	 *
	 * After registration we can create the object using CreateObject.\n
	 * Notice that Base here is the client base class.\n
	 * c++ polymorphism is used to called the client methods derived
	 * from the base pure virtual methods.
	 */
	template <class Base> Base* CreateObject(string name) const {
		auto factory = factoryMap.find(name);
		if(factory == factoryMap.end())
			return nullptr;
		//		if(verbosity > 0) {
		//			cout << logHeader << " GManager: Creating factory " << name << endl;
		//		}
		return static_cast<Base*>(factory->second->Create());
	}

	/**
	 * @fn registerDL
	 * @param name base name of the dynamic library to be registered
	 *
	 * The full filename is OS dependent
	 */
	void registerDL(string name) {
		// PRAGMA TODO: make it OS independent?
		dlMap[name] = new DynamicLib( name + ".gplugin");
		if(verbosity > 0) {
			cout  << logHeader << " GManager: Loading DL " << name  << endl;
		}
	}

	/**
	 * @fn LoadObjectFromLibrary
	 * @param name name under which the factory is registered
	 *
	 * Instantiate client derived class.\n
	 * Notice the base class must have the static method instantiate
	 */
	template <class T> T* LoadObjectFromLibrary(string name) {

		// will return nullptr if handle is null
		DynamicLib* dynamicLib = dlMap[name];
		if(dynamicLib != nullptr) {
			dlhandle thisDLHandle = dynamicLib->handle;
			if(thisDLHandle != nullptr) {
				return T::instantiate(thisDLHandle);
			}
		}
		// warning message already given if plugin not found
		// cout << logHeader << " GManager: plugin " << name << " could not be loaded " << endl;
		return nullptr;
	}


	/**
	 * @fn destroyObject
	 * @param object class type of the instance to be deleted
	 *
	 * Delete the instance pointer
	 */
	template <class T> void destroyObject(T* object) {
		delete object;
	}

	/**
	 * @fn clearDLMap
	 *
	 * Delete the various dynamic libraries handle
	 */
	void clearDLMap() {
		for(auto &i : dlMap) {
			delete i.second;
		}
	}


private:
	map<string, GFactoryBase*> factoryMap;
	// the reason to keep this map is to keep the pointers in memory
	// for some reason declaring a dynamic_lib local variable in LoadObjectFromLibrary
	// scope does not work
	map<string, DynamicLib*> dlMap;

	int verbosity;
	string logHeader;
};

#endif
