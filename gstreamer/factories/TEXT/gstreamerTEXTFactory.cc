// gstreamer
#include "gstreamerTEXTFactory.h"

// tells the DLL how to create a GMediaFactory
// do we need this?
extern "C" GStreamer* GstreamerTextFactory(void) {
	return static_cast<GStreamer*>(new class GstreamerTextFactory);
}
