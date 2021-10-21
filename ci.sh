#!/usr/bin/env bash
set -e

# GLIBRARY Continuous Integration
# ----------------------------
#
# To debug this on the container:
#
# docker run -it --rm jeffersonlab/gemc:3.0 bash
# git clone http://github.com/gemc/glibrary /root/glibrary && cd /root/glibrary
# ./ci.sh


# load environment if we're on the container
FILE=/etc/profile.d/jlab.sh
if test -f "$FILE"; then
    source "$FILE"
fi

# using the checked out GLIBRARY
export GLIBRARY=`pwd`

function compileCadmesh {
	echo
	echo Compiling CadMesh
	./compileCmesh
}

function compileGLibrary {
	# getting number of available CPUS
	copt=" -j"`getconf _NPROCESSORS_ONLN`" OPT=1"
	echo
	echo Compiling glibrary with options: "$copt"
	scons $copt
	echo Compilation completed, content of lib:
	ls -l lib/
}

function checkLibsExistence {

	# shared (dynamic) library extension is different on linux/darwin
	libExtension=".so"
	[[ $OSTYPE == 'darwin'* ]] && libExtension=".dylib"

	# cadmesh
	for lib in assimp cadmesh
		do
		ls lib/lib$lib$libExtension
		if [ $? -ne 0 ]; then
			echo $lib not present
		exit 1
		fi
	done

	# glibrary
	libExtension=".a"
	for lib in eventDispenser g4display g4system gQtButtonsWidget gdata gdynamic ghit goptions \
	           gparticle gsplash gstreamer gsystem gtouchable gtranslationTable guts textProgressBar
		do
		ls lib/lib$lib$libExtension
		if [ $? -ne 0 ]; then
			echo $lib not present
		exit 1
		fi
	done

	# plugins
	libExtension=".gplugin"
	for lib in gstreamerJLABSROFactory gstreamerROOTFactory gstreamerTEXTFactory
		do
		ls lib/$lib$libExtension
		if [ $? -ne 0 ]; then
			echo $lib not present
		exit 1
		fi
	done
}



echo
echo "GLIBRARY Validation: $1"
echo
time=$(date)
echo "::set-output name=time::$time"

if [ $# -eq 1 ]; then
	echo "Running check: "$1
	if [ $1 == "libs" ]; then
		checkLibsExistence
	fi
else
	echo "Running all checks"
	compileCadmesh
	compileGLibrary
	checkLibsExistence
fi
