#ifndef  GFACTORY_H
#define  GFACTORY_H 1

// c++
#include <map>
#include <string>
#include <iostream>
using std::string;

// dynamic loading
#include "gdl.h"

#define GFACTORYLOGITEM  " ❖"

/*
 * @class GFactoryBase
 * @brief Base class. Use polymorphism to run Create on the
 * derived classes
 */
class GFactoryBase {
public:
	/**
	 @brief Pure virtual method. Derived classes use this to instantiate themselves
	 */
	virtual void* Create() = 0;
};

/**
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
 * @brief Instantiates derived classes either statically or dynamically
 */
class GManager
{

private:

	// the map of GFactoryBase is kept on GManager
	map<string, GFactoryBase*> factoryMap;

	// the reason to keep this map is to keep the (DynamicLib?) pointers in memory
	// for some reason declaring a dynamic_lib local variable in LoadAndRegisterObjectFromLibrary
	// scope does not work
	map<string, DynamicLib*> dlMap;

	int verbosity;

	/**
	 * @fn registerDL
	 * @param name base name of the dynamic library to be registered
	 *
	 * The full filename is OS dependent
	 */
	void registerDL(string name) {
		// PRAGMA TODO: make it OS independent?
		dlMap[name] = new DynamicLib( name + ".gplugin", verbosity);
		if(verbosity > 0) {
			cout  << GFACTORYLOGITEM << " GManager: Loading DL " << name  << endl;
		}
	}

public:
	/**
	 @param v verbosity.
	 - 0: no not print any log
	 - 1: print gmanager registering and instantiating classes
	 */
	GManager( int v = 0 ) : verbosity(v) {}

public:
	/**
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
			cout << GFACTORYLOGITEM << " GFactory Manager: Registering " << name << " factory. Factory has now: " << factoryMap.size() << " items " << endl;
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
		if(factory == factoryMap.end()) {
			cerr << FATALERRORL  " couldn't find factory " << YELLOWHHL << name << RSTHHR << " in factoryMap." << endl;
			gexit(EC__FACTORYNOTFOUND);
		}
		if(verbosity > 0) {
			cout << GFACTORYLOGITEM << " GFactory Manager: Creating instance of " << name << " factory." << endl;
		}
		return static_cast<Base*>(factory->second->Create());
	}


	/**
	 * @fn LoadAndRegisterObjectFromLibrary
	 * @param name name under which the factory is registered
	 *
	 * Instantiate client derived class.\n
	 * Notice the base class must have the static method instantiate
	 */
	template <class T> T* LoadAndRegisterObjectFromLibrary(string name) {

		registerDL(name);

		// will return nullptr if handle is null
		DynamicLib* dynamicLib = dlMap[name];
		if(dynamicLib != nullptr) {
			dlhandle thisDLHandle = dynamicLib->handle;
			if(thisDLHandle != nullptr) {
				return T::instantiate(thisDLHandle);
			}
		}
		// warning message already given if plugin not found
		// cout << GFACTORYLOGITEM << " GManager: plugin " << name << " could not be loaded " << endl;
		return nullptr;
	}


	/**
	 * @fn destroyObject
	 * @param object class type of the instance to be deleted
	 *
	 * Delete the instance pointer
	 */
	//	template <class T> void destroyObject(T* object) {
	//		delete object;
	//	}

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



};

#endif
