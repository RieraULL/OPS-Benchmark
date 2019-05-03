#include "target_range_t.hpp"

#include "../json/json.hpp"
using json = nlohmann::json;


using namespace std;

namespace EMIR
{

target_range_t::target_range_t(void)
    : p_range_()
    , b_levels_()
{}

target_range_t::target_range_t(const vector<double>& p_range, const vector<double>& b_levels)
    : p_range_(p_range)
    ,b_levels_(b_levels)
{}

target_range_t::~target_range_t(void)
{
}


}
