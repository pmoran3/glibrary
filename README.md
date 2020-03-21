# glibrary

A collection of various utility libraries for gemc

---

* string: namespace for string manipulations
* goptions: command line and JSON options handler
* gfactory: dynamically loader of classes from shared object
* gtouchable: definition of an abstract touchable
* ghit: definition of the gemc hit

---

Travis Doxygen Build: ![Travis Build](https://api.travis-ci.com/gemc/glibrary.svg?branch=master)

---

For now we need to append on this SConstruct and inside each glibrary SConstruct
env.Append(CXXFLAGS=['-std=c++17'])


---
