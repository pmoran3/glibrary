// gstreamer
#include "gstreamerJLABSROFactory.h"

// c++
#include<vector>
#include <iostream>

bool GstreamerJSROFactory::publishFrameHeader(const GFrameDataCollectionHeader *gframeHeader) 
{
	if(ofile == nullptr) return false;

	cout << " Publishing frame header " << endl;

	// fill dataFrameHeader here or in startStream
	//vector<unsigned int> frame_data;
	//dataFrameHeader = *reinterpret_cast<DataFrameHeader*>(frame_data.data());
	ofile->write(reinterpret_cast<const char*>(frame_data.data()), 
//				sizeof(DataFrameHeader));
				 sizeof(unsigned int) * frame_data.size());
	return true;


}


