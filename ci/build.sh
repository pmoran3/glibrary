#!/usr/bin/env zsh

# Purpose: compiles the Cadmesh glibrary libraries

# Container run example:
# docker run -it --rm jeffersonlab/gemc:3.0-clas12 bash
# git clone http://github.com/gemc/glibrary /root/glibrary && cd /root/glibrary
# ./ci/build.sh

# load environment if we're on the container
# notice the extra argument to the source command
TERM=xterm # source script use tput for colors, TERM needs to be specified
FILE=/etc/profile.d/jlab.sh
test -f $FILE && source $FILE keepmine

# using the checked out GLIBRARY
export GLIBRARY=`pwd`
echo GLIBRARY is $GLIBRARY

function compileGLibrary {
	# getting number of available CPUS
	copt=" -j"`getconf _NPROCESSORS_ONLN`" OPT=1"
	echo
	echo Compiling Glibrary with options: "$copt"
	scons $copt
	echo
	echo Compilation completed, content of lib:
		ls -ltrh lib/
}

function checkLibsExistence {
	echo
	echo Checking libraries existence
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


function buildGEMC {
	# getting number of available CPUS
	copt=" -j"`getconf _NPROCESSORS_ONLN`" OPT=1"
	echo
	echo Compiling GEMC with options: "$copt"
	cd $GEMC
	scons $copt
	echo
	echo Compilation completed
	ls -ltrh ./

}

compileCadmesh
compileGLibrary
checkLibsExistence

