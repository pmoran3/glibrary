// gstreamer
#include "gstreamerJLABSROFactory.h"
#include "VTPFrameGenerator.h"

// c++
#include<vector>


bool GstreamerJSROFactory::publishFrameHeader(const GFrameDataCollectionHeader *gframeHeader) 
{
	if(ofile == nullptr) return false;

	vector<std::uint32_t> const super_magic = {0xC0DA2019, 0XC0DA0001};

	ofile->write(reinterpret_cast<const char*>(super_magic.data()), sizeof(std::uint32_t) * 2);

	double hit_rate = 30000;
	unsigned int channels = 16;
	unsigned int slots = 8;
	unsigned int crates = 1;

	// TODO!!! TEMP FIRST ARGUMENT
	// constructor first argument is vector<unsigned> I put super_magic here as placeholder
	VTPFrameGenerator vtpf(super_magic, crates, slots, channels, hit_rate);


	// this should not be a loop. Should read data from gframeHeader
	// also, looks like this part (payload) should go in publishPayload
	int n_of_frames=10;
	for (int i = 0; i < n_of_frames; i++) {
		// 		auto start = std::chrono::steady_clock::now();

		vtpf.generate_data(i);
		// vtpf.update_counter(i);

		//      auto delta      = std::chrono::steady_clock::now() - start;
		//     auto sleep_time = 65536;//ns - delta;
		//if (sleep_time > 0/*ns*/) {
		//std::this_thread::sleep_for(sleep_time);
		//}

		vector<unsigned int> const& frame = vtpf.get_frame_data();
		ofile->write(reinterpret_cast<const char*>(frame.data()),
						 sizeof(unsigned int) * frame.size());
	}
	return true;


}


