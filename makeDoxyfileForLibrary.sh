#!/bin/zsh

# Purpose: creates a doxyfile for a specific library, based on a doxyfile created with doxygen -g
#
# Arguments: exactly one argument, the name of the library

if [ "$#" -ne 1 ]; then
	echo " "       >&2
	echo " Usage:" >&2
	echo " "       >&2
	echo  " $0 libraryName"  >&2
	echo " "       >&2
	exit 1
fi


library=$1
echo " Setting Doxyfile for "$library


# replacing instances of "templateGLibrary"
extraArgument=''
case `uname` in
	Darwin)
		extraArgument='backup'
	;;
	Linux)
		extraArgument=''
	;;
esac

# no PROJECT_BRIEF
sed -i $extraArgument s/templateGLibrary/$library/g Doxyfile

toCheck=(PROJECT_NAME OPTIMIZE_OUTPUT_FOR_C BUILTIN_STL_SUPPORT SHOW_FILES HTML_COLORSTYLE_GAMMA QUIET)
echo " "Doxyfile Main changes:
echo
for l in $toCheck
do
	setting=$(grep "$l" Doxyfile | grep -v "#")
	echo "  - "$setting
done

echo
echo " Copying mylayout.css to "$library
if [ $library != "gemc" ]; then
	# adding moc, html to exclde patters
	sed -i $extraArgument 's/EXCLUDE_PATTERNS       =/EXCLUDE_PATTERNS       = \*moc\* \*\/html\/\*/g'    Doxyfile
	cp docs/mylayout.css $library/
	cp Doxyfile $library/
else
	if [[ -v TRAVISENVIRONMENT ]]; then
		echo " Travis Build" >&2
		# Note: EXCLUDE_PATTERNS includes glibrary because we're using this script for "gemc" on travis as well, and in there we clone glibrary
		sed -i $extraArgument 's/EXCLUDE_PATTERNS       =/EXCLUDE_PATTERNS       = \*moc\* \*glibrary\* \*\/html\/\*/g'    Doxyfile
		cp glibrary/docs/mylayout.css .
	else
		echo " Non travis Build" >&2
		# Note: normal EXCLUDE_PATTERNS, glibrary is not here
		sed -i $extraArgument 's/EXCLUDE_PATTERNS       =/EXCLUDE_PATTERNS       = \*moc\* \*\/html\/\*/g'    Doxyfile
		cp ../glibrary/docs/mylayout.css .
	fi
fi

rm -f Doxyfilebackup
