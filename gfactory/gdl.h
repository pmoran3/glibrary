#ifndef  GDYNAMICLIB_H
#define  GDYNAMICLIB_H  1

// this code is based on this tutorial:
// https://0x00sec.org/t/c-dynamic-loading-of-shared-objects-at-runtime/1498

// c++ plugin loading functions
#include <dlfcn.h>

// c++
#include <sys/stat.h> // to check if file exists
#include <string>
#include <iostream>
using namespace std;

typedef void* dlhandle;

static dlhandle load_lib(const string& path);
static void close_lib(dlhandle handle);

#define DLLOGITEM  " ⁍"

/**
 * @struct DynamicLib
 * @brief  Structure to load dynamically symbols from a shared library
 */
struct DynamicLib {

private:
	string   dlFileName;  ///< dynamic library file
	int verbosity = 0;

	bool FileExists(const std::string& name) {
		struct stat buffer;
		return (stat (name.c_str(), &buffer) == 0);
	}


public:
	// default constructor
	DynamicLib() = default;
	dlhandle handle;   ///< posix handle of the dynamic library


	DynamicLib(string path, int v = 0) : dlFileName(path), verbosity(v), handle(nullptr) {

		if ( verbosity ) {
			cout << DLLOGITEM <<  " Loading Dynamic Library " << dlFileName << endl;
		}

		if(FileExists(dlFileName)) {
			handle = load_lib(dlFileName);
		} else {
			// PRAGMA TODO: no warning here. But give error if digitization is requested but not found
			// either exception or mutex lock
			cout << " ⚠︎ Warning: " << dlFileName << " not found." << endl;
		}
	}

	~DynamicLib() {
		if (handle != nullptr)
			close_lib(handle);
		if ( verbosity ) {
			cout << DLLOGITEM << " Closing DL " << dlFileName << endl;
		}
	}


};


static dlhandle load_lib(const string& path) {

	return dlopen(path.data(), RTLD_NOW);
	// get a handle to the lib, may be nullptr.
	// RTLD_NOW ensures that all the symbols are resolved immediately:
	// if a symbol cannot be found, the program will crash now instead of later.
}

static void close_lib(dlhandle handle) {
	dlclose(handle);
}

#endif
