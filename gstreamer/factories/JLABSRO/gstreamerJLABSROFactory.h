#ifndef GSTREAMERJSROFACTORY_H
#define GSTREAMERJSROFACTORY_H 1

// gstreamer
#include "gstreamer.h"

#include <fstream>
using std::ofstream;

class GstreamerJSROFactory : public GStreamer
{
public:
	GstreamerJSROFactory() {}
	//FrameGenerator(unsigned int crateid, unsigned int slots,
	//                 unsigned int channels, double hit_rate);
	void generate_data(unsigned int counter);
	//void update_counter(unsigned int counter);

	//DataFrameHeader const& get_header() const;
	//std::vector<unsigned int> const& get_frame_data() const;
	//PayloadPrinter payload_printer(int nFADC, bool verbose, int rc) const;

private:
	// open and close the output media
	bool openConnection();
	bool closeConnection();

	// frame streams
	bool startStream(const GFrameDataCollection* frameRunData);
	bool endStream(const GFrameDataCollection* frameRunData);
	bool publishFrameHeader(const GFrameDataCollectionHeader *gframeHeader);
	bool publishPayload(const vector<GIntegralPayload*> *payload);


private:
	ofstream *ofile = nullptr;
};

#endif // GSTREAMERJSROFACTORY_H

