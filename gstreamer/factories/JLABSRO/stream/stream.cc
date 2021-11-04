// gstreamer
#include "gstreamerJLABSROFactory.h"

bool GstreamerJSROFactory::startStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) {
		cout << "ofile == nullptr" << endl;
		return false;
	}
	std::vector<std::uint32_t> const super_magic = {0xC0DA2019, 0XC0DA0001};
	ofile->write(reinterpret_cast<const char*>(super_magic.data()), sizeof(std::uint32_t) * 2);

	static constexpr int header_offset = sizeof(DataFrameHeader) / 4;
	const GFrameDataCollectionHeader* header = frameRunData->getHeader();
	long int frameID = header->getFrameID();

	const std::vector<GIntegralPayload*> *payload = frameRunData->getIntegralPayload();

	frame_data.resize(header_offset,0);

	// fill dataFrameHeader here or in publishFrameHeader
	DataFrameHeader& dataFrameHeader = *reinterpret_cast<DataFrameHeader*>(frame_data.data());

	dataFrameHeader.source_id = 0;
	dataFrameHeader.magic = 0xC0DA2019;
	dataFrameHeader.format_version = 257;
	dataFrameHeader.flags = 0;
	dataFrameHeader.record_counter = llswap(frameID);
	dataFrameHeader.ts_sec = llswap((frameID * 65536) / static_cast<int>(1e9));
	dataFrameHeader.ts_nsec = llswap((frameID * 65536) % static_cast<int>(1e9));


	//make payload data
	unsigned int crateid = 0;
	unsigned int slots = 8;
	unsigned int channel = 16;

	frame_data.resize(header_offset);
	frame_data.push_back(0x80000000);
	frame_data.insert(frame_data.end(), slots, 0);

	for(unsigned int slot = 0; slot < slots; ++slot) {

		int starting_point = frame_data.size() - header_offset;
		frame_data.push_back(0x80008000 | (crateid << 8) | slot);

		bool generating = true;
		int hit_counter = 0;
		std::vector<unsigned int> times(channel, 0);

		while (generating) {
		  for (unsigned int i = 0; i < channel; ++i) {
		    times[i] += header->getTime();
		    if (times[i] > 65536) {
		      generating = false;
		      break;
    		    }
	    	assert((times[i] / 4) < 0x8000 && i < 0x10);
	    	frame_data.push_back(1024 | (i << 13) | ((times[i] / 4) << 17));
	    	++hit_counter;
  		  }
		}

		if (hit_counter == 0) {
		  frame_data.pop_back();
		} else {
		  ++hit_counter;
		}

		frame_data[header_offset + 1 + slot] =
		    ((hit_counter) << 16) | starting_point;
		    }

        DataFrameHeader& dfh = *reinterpret_cast<DataFrameHeader*>(frame_data.data());

	dfh.payload_length = frame_data.size()*sizeof(unsigned int) - sizeof(DataFrameHeader);
	dfh.compressed_length = dfh.payload_length;
	dfh.total_length = dfh.compressed_length + sizeof(DataFrameHeader) - 4;

		return true;
}




bool GstreamerJSROFactory::endStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;


	return true;
}
