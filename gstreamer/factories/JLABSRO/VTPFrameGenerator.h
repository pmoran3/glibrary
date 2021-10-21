#include <vector>

class VTPFrameGenerator
{
	//static constexpr int header_offset_ = sizeof(DataFrameHeader) / 4;
	std::vector<unsigned int> frame_data;

	unsigned int crateid;
	unsigned int slots;
	unsigned int channels;

	//std::default_random_engine gen_;
	//std::exponential_distribution<> time_gen_;

	void init_header(unsigned int counter);
	//void update_frame_length();
	//void make_payload_data(unsigned int slot);

public:

	VTPFrameGenerator(std::vector<unsigned int> header_offset,
							unsigned int crateid,
							unsigned int slots,
							unsigned int channels,
							double hit_rate);

	void generate_data(unsigned int counter);
	//void update_counter(unsigned int counter);

	//  DataFrameHeader const& get_header() const;
	std::vector<unsigned int> const& get_frame_data() const {return frame_data;}
	//PayloadPrinter payload_printer(int nFADC, bool verbose, int rc) const;
};
