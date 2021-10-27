// gstreamer
#include "gstreamerJLABSROFactory.h"

bool GstreamerJSROFactory::startStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;

	const GFrameDataCollectionHeader* header = frameRunData->getHeader();
	long int frameID = header->getFrameID();

	const std::vector<GIntegralPayload*> *payload = frameRunData->getIntegralPayload();

	// fill dataFrameHeader here or in publishFrameHeader
	dataFrameHeader.source_id = 0;
	dataFrameHeader.magic = 0xC0DA2019;
	dataFrameHeader.format_version = 257;
	dataFrameHeader.flags = 0;
	dataFrameHeader.record_counter = llswap(frameID);
	dataFrameHeader.ts_sec = llswap((frameID * 65536) / static_cast<int>(1e9));
	dataFrameHeader.ts_nsec = llswap((frameID * 65536) % static_cast<int>(1e9));
	dataFrameHeader.payload_length = payload->size() * sizeof(unsigned int);
	dataFrameHeader.compressed_length = dataFrameHeader.payload_length;
	dataFrameHeader.total_length = dataFrameHeader.compressed_length + sizeof(DataFrameHeader) - 4;

	return true;
}




bool GstreamerJSROFactory::endStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;


	return true;
}
