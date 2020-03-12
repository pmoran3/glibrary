#ifndef  GFACTORY_DOXY_H
#define  GFACTORY_DOXY_H  1
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
 * 
 *  // map that will contain the derived classes instances
 * map<string, Shape*> shapes;
 * GManager manager;
 *  // register class in the manager
 * manager.RegisterObjectFactory<Triangle>("triangle");
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
 * \n\n
 * \author \n &copy; Maurizio Ungaro
 * \author e-mail: ungaro@jlab.org\n\n\n
 */

#endif
