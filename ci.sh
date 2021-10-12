#!/usr/bin/bash -e

# GLIBRARY Continuous Integration
# ----------------------------
#
# Original Instructions:
# https://docs.github.com/en/actions/creating-actions/creating-a-docker-container-action
# The steps on "main" are pasted on the Github page under "Actions" > set up a workflow yourself
#
# To debug this on the container:
#
# cp ci.sh ~/mywork
# docker run -it --rm -v ~/mywork:/jlab/work/mywork jeffersonlab/gemc:3.0 bash
# cd work/mywork
# ./ci.sh

# load environment
source /etc/profile.d/jlab.sh

echo
echo "GLIBRARY Validation: $1"
echo
time=$(date)
echo "::set-output name=time::$time"

cd /root
git clone http://github.com/gemc/glibrary
cd glibrary
export GLIBRARY=`pwd`

echo
echo Compiling CadMesh
./compileCmesh

# getting number of available CPUS
copt=" -j"`getconf _NPROCESSORS_ONLN`" OPT=1"
echo
echo Compiling glibrary with options: "$copt"
scons $copt

echo Compilation completed, content of lib:
ls -l lib/

# checking on various libraries
ls lib/libeventDispenser.a lib/libgdata.a lib/libguts.a lib/libassimp.dylib libgstreamer.a
if [ $? -ne 0 ]; then
  echo compilation not completed
  exit 1
fi


# checking on the streamers plugins
ls lib/gstreamerJLABSROFactory.gplugin lib/gstreamerROOTFactory.gplugin lib/gstreamerTEXTFactory.gplugin
if [ $? -ne 0 ]; then
  echo gstreamers missing
  exit 1
fi
