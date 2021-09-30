from init_env import init_environment

# load needed environment for all glibraries
env = init_environment('glibrary clhep geant4 qt5 gcadmesh')
env.Append(CXXFLAGS=['-std=c++17'])

gdata                = SConscript('gdata/SConscript',                exports='env')
textProgressBar      = SConscript('textProgressBar/SConscript',      exports='env')
guts                 = SConscript('guts/SConscript',                 exports='env')
goptions             = SConscript('goptions/SConscript',             exports='env')
gsplash              = SConscript('gsplash/SConscript',              exports='env')
gtouchable           = SConscript('gtouchable/SConscript',           exports='env')
ghit                 = SConscript('ghit/SConscript',                 exports='env')
gsystem              = SConscript('gsystem/SConscript',              exports='env')
g4system             = SConscript('g4system/SConscript',             exports='env')
gstreamer            = SConscript('gstreamer/SConscript',            exports='env')
eventDispenser       = SConscript('eventDispenser/SConscript',       exports='env')
gQtButtonsWidget     = SConscript('gQtButtonsWidget/SConscript',     exports='env')
g4display            = SConscript('g4display/SConscript',            exports='env')
gdynamicDigitization = SConscript('gdynamicDigitization/SConscript', exports='env')
gtranslationTable    = SConscript('gtranslationTable/SConscript',    exports='env')

# output plugins
libsTextDLL = SConscript('gstreamer/SConscriptTextDLL')
libsRootDLL = SConscript('gstreamer/SConscriptRootDLL')

