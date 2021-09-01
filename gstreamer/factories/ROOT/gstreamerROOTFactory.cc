// gstreamer
#include "gstreamerROOTFactory.h"

// tells the DLL how to create a GStreamerFactory
extern "C" GStreamer* GStreamerFactory(void) {
	return static_cast<GStreamer*>(new GstreamerRootFactory);
}
