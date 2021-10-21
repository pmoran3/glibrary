class FrameGenerator
{
  //static constexpr int header_offset_ = sizeof(DataFrameHeader) / 4;
  std::vector<unsigned int> frame_data_;

  unsigned int crateid_;
  unsigned int slots_;
  unsigned int channels_;

  //std::default_random_engine gen_;
  //std::exponential_distribution<> time_gen_;

  void init_header(unsigned int counter);
  //void update_frame_length();
  //void make_payload_data(unsigned int slot);

 public:
  FrameGenerator(unsigned int crateid, unsigned int slots,
                 unsigned int channels, double hit_rate);
  void generate_data(unsigned int counter);
  //void update_counter(unsigned int counter);

//  DataFrameHeader const& get_header() const;
  std::vector<unsigned int> const& get_frame_data() const;
  //PayloadPrinter payload_printer(int nFADC, bool verbose, int rc) const;
};
