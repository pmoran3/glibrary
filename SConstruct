# TODO: compiling with too many processors causes some example executable to try to load the gmedia library even when it's not build.
# How to prevent that? Maybe this is resolved, check on ifarm with 30+ parallele jobs

from init_env import init_environment

# load needed environment for all glibraries
env = init_environment('glibrary clhep geant4 qt5')
env.Append(CXXFLAGS=['-std=c++17'])

textProgressBar     = SConscript('textProgressBar/SConscript',  exports='env')
guts                = SConscript('guts/SConscript',             exports='env')
goptions            = SConscript('goptions/SConscript',         exports='env')
gsplash             = SConscript('gsplash/SConscript',          exports='env')
gdata               = SConscript('gdata/SConscript',            exports='env')
gtouchable          = SConscript('gtouchable/SConscript',       exports='env')
ghit                = SConscript('ghit/SConscript',             exports='env')
gsystem             = SConscript('gsystem/SConscript',          exports='env')
g4system            = SConscript('g4system/SConscript',         exports='env')
gstreamer           = SConscript('gstreamer/SConscript',        exports='env')
eventDispenser      = SConscript('eventDispenser/SConscript',   exports='env')
gQtButtonsWidget    = SConscript('gQtButtonsWidget/SConscript', exports='env')

Depends(gstreamer, gdata)

# output plugins
gstreamerDLLS   = SConscript('gstreamer/SConscriptDLLS',  exports='env')
Depends(gstreamerDLLS, gstreamer)



#translationTable    = SConscript('translationTable/SConscript')
#frequencySyncSignal = SConscript('frequencySyncSignal/SConscript')
#qtButtonsWidget     = SConscript('qtButtonsWidget/SConscript')
#g4display           = SConscript('g4display/SConscript', exports='env')

