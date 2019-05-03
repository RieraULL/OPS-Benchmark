#include "valid_range_t.hpp"

EMIR::valid_range_t::valid_range_t(void):
vector<double>(2, 0)
{}

EMIR::valid_range_t::valid_range_t(const std::vector<double> bounds):
vector<double>(bounds)
{}

EMIR::valid_range_t::~valid_range_t(void)
{}


        
