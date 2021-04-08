#!/bin/bash

# Purpose: creates the doxygen documentation for all the glibraries
# This script is used by TRAVIS
#
# Arguments: none

echo " "
echo " >> GLIBRARY Tests"
echo " "

libraries='goptions'

for l in $libraries
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
