// gstreamer
#include "gstreamerJLABSROFactory.h"

// c++
#include<vector>
#include <iostream>

bool GstreamerJSROFactory::publishFrameHeader(const GFrameDataCollectionHeader *gframeHeader) 
{
	if(ofile == nullptr) return false;

	// fill dataFrameHeader here or in startStream
	//vector<unsigned int> frame_data;
//	dataFrameHeader = *reinterpret_cast<DataFrameHeader*>(frame_data.data());
	std::vector<std::uint32_t> const super_magic = {0xC0DA2019, 0XC0DA0001};
	ofile->write(reinterpret_cast<const char*>(super_magic.data()), sizeof(std::uint32_t) * 2);

	ofile->write(reinterpret_cast<const char*>(frame_data.data()), 
				sizeof(DataFrameHeader));
//				 sizeof(unsigned int) * frame_data.size());


	return true;


}


