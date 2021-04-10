#!/bin/bash

# Purpose: creates the doxygen documentation for all the glibraries
# This script is used by TRAVIS
#
# Arguments: none

echo " "
echo " >> GLIBRARY Tests"
echo " "

export JLAB_ROOT=/home/travis
export JLAB_VERSION=2.4

# installing modules, scons and glibrary
git clone https://github.com/gemc/gmodules.git
cd gmodules
./installModules.sh scons
./installModules.sh glibrary
cd ..

# compile glibrary
moduleFile=$(./gmodules/modulefilelocation.py)
echo aaa $moduleFile
ls $moduleFile
source $moduleFile
module use $JLAB_ROOT/$JLAB_VERSION/modules
module load glibrary


# run additional tests
librariesWithTests='goptions'
for l in $librariesWithTests
do
	cd $l
	./runTests.sh
	# exit if
	if [ $? -eq 0 ]; then
		echo " >> GLIBRARY Test: "$l" passed"
	else
		echo " >> GLIBRARY Test: "$l" failed"
		exit $?
	fi
	cd ..
done

exit 0
