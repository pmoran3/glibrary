#!/bin/zsh

# Purpose: creates a directory with files from the template directory
#
# Arguments: exactly one argument, the name of the new library

if [ "$#" -ne 1 ]; then
	echo " "       >&2
	echo " Usage:" >&2
	echo " "       >&2
	echo  " $0 libraryName"  >&2
	echo " "       >&2
	exit 1
fi


library=$1
echo " "
echo " Creating glibrary" $library
mkdir -p $library


# template files
echo " "
for f in SConstruct SConscript example.cc settings.xcconfig README.md
do
	echo " "copying $f
	cp templateGLibrary/$f $library/
done

echo " "
for f in todo
do
	echo " "touching $f
	rm -f $library/$f
	touch $library/$f
done

# header
cheader=$(echo $library"_h" | tr "[:lower:]" "[:upper:]")
echo " "
echo " "Creating $library header using $cheader

rm -f $library/$library".h" ; touch $library/$library".h"

echo '// doxygen'                       >> $library/$library".cc"
echo '#include $library"Doxy.h"'        >> $library/$library".cc"
echo ''                                 >> $library/$library".cc"
echo '// conventions'                   >> $library/$library".cc"
echo '#include $library"Conventions.h"' >> $library/$library".cc"
echo ''                                 >> $library/$library".cc"
echo "#ifndef " $cheader                >> $library/$library".h"
echo "#define " $cheader " 1"           >> $library/$library".h"
echo                                    >> $library/$library".h"
echo                                    >> $library/$library".h"
echo "class $library"                   >> $library/$library".h"
echo "{"                                >> $library/$library".h"
echo                                    >> $library/$library".h"
echo                                    >> $library/$library".h"
echo  "};"                              >> $library/$library".h"
echo                                    >> $library/$library".h"
echo                                    >> $library/$library".h"
echo "#endif"                           >> $library/$library".h"

# doxy main file
doxyFile=$library/$library"Doxy.h"
rm -f $doxyFile ;  touch $doxyFile
echo "#ifndef " $cheader"_DOXY"   >> $doxyFile
echo "#define " $cheader"_DOXY 1" >> $doxyFile
cat docs/doxy.h                   >> $doxyFile
echo "#endif"                     >> $doxyFile

# convention file
convFile=$library/$library"Conventions.h"
rm -f $convFile ;  touch $convFile
echo "#ifndef " $cheader"_CONVENTIONS"     >> $convFile
echo "#define " $cheader"_CONVENTIONS 1"   >> $convFile
echo ""                                    >> $convFile
echo "#endif"                              >> $convFile



# c++ code
echo " "
echo " "Creating $library cc source
rm -f $library/$library".cc"; touch $library/$library".cc"

echo "// $library "             >> $library/$library".cc"
echo '#include "'$library'.h"'  >> $library/$library".cc"

# changing the name in the template files
echo " "
echo " "Changing template name to $library in:
echo " "
for f in SConstruct SConscript example.cc README.md
do
	echo " "$f
	sed -i '' s/templateGLibrary/$library/g     $library/$f
done

echo " "
