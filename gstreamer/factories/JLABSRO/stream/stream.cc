// gstreamer
#include "gstreamerJLABSROFactory.h"

bool GstreamerJSROFactory::startStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;

	const GFrameDataCollectionHeader* header = frameRunData->getHeader();
	long int frameID = header->getFrameID();

	const std::vector<GIntegralPayload*> *payload = frameRunData->getIntegralPayload();

	// fill dataFrameHeader here or in publishFrameHeader
	DataFrameHeader dfh;

	dfh.source_id = 0;
	dfh.magic = 0xC0DA2019;
	dfh.format_version = 257;
	dfh.flags = 0;
	dfh.record_counter = llswap(frameID);
	dfh.ts_sec = llswap((frameID * 65536) / static_cast<int>(1e9));
	dfh.ts_nsec = llswap((frameID * 65536) % static_cast<int>(1e9));
	dfh.payload_length = payload->size() * sizeof(unsigned int);
	dfh.compressed_length = dfh.payload_length;
	dfh.total_length = dfh.compressed_length + sizeof(DataFrameHeader) - 4;

	return true;
}




bool GstreamerJSROFactory::endStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;


	return true;
}
