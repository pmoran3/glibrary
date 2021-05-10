#!/bin/zsh

# Purpose: creates the doxygen documentation for all the glibraries
# This script is used by TRAVIS
#
# Arguments: none

echo " "
echo " Doxygen version: "$(doxygen --version)
echo " "
ddir='doxygen'

libraries=(goptions guts gfactory gdata)

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
	echo " Running Doxygen for "$l
	doxygen Doxyfile 
	mv html ../$ddir/$l
	cd ..
	echo " --------------------------------  "
	echo
done
