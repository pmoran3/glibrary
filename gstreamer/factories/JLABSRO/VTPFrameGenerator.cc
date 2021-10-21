#include "VTPFrameGenerator.h"

//#include <functional>
//#include <random>

VTPFrameGenerator::VTPFrameGenerator(std::vector<unsigned int> header_offset,
						unsigned int crateid_,
						unsigned int slots_,
						unsigned int channels_,
						double hit_rate)
	: frame_data{header_offset}
	, crateid{crateid_}
	, slots{slots_}
	, channels{channels_}
//    , gen_(crateid * 10 + 100 + slots)
//    , time_gen_{hit_rate}
{
	assert(crateid < 0xFF && slots < 0x3F && channels < 0x3F);
}

void VTPFrameGenerator::generate_data(unsigned int counter)
{
	// init header
	init_header(counter);

	// init payload
	//frame_data.resize(header_offset_);
	//frame_data.push_back(0x80000000);
	//frame_data.insert(frame_data.end(), slots_, 0);

	// make data
	/*for (unsigned int i = 0; i < slots_; ++i) {
	 make_payload_data(i);
	 }*/

	// update frame length
	//update_frame_length();
}

void VTPFrameGenerator::init_header(unsigned int counter)
{
//	DataFrameHeader& vtph =	*reinterpret_cast<DataFrameHeader*>(frame_data.data());
//
//	vtph.source_id      = 0;
//	vtph.magic          = 0;//magic;
//	vtph.format_version = 257;
//	vtph.flags          = 0;
//	vtph.record_counter = 0;//llswap(counter);
//
//	vtph.ts_sec  = 0;//llswap((counter * 65536) / static_cast<int>(1e9));
//	vtph.ts_nsec = 0;//llswap((counter * 65536) % static_cast<int>(1e9));

	//update_frame_length();
}
