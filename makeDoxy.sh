#!/bin/bash

# Purpose: creates the doxygen documentation for all the glibraries
# This script is used by TRAVIS
#
# Arguments: none

echo " "
echo " Doxygen version: "$(doxygen --version)
echo " "
ddir='doxygen'

libraries='goptions gstring gfactory gtouchable ghit gdata gdigitization'

if [ -d $ddir ]
then
	rm -rf $ddir
fi
mkdir -p $ddir

# for documentation purposes
ls -l

echo " "
for l in $libraries
do
	./createDoxyfile.sh
	./makeDoxyfileForLibrary.sh $l
	cd $l
	doxygen Doxyfile 
	mv html ../$ddir/$l
	cd ..
done
echo " "
