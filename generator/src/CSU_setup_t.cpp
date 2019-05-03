#include "CSU_setup_t.hpp"

#include <iomanip>

using namespace std;

namespace EMIR
{

CSU_setup_t::CSU_setup_t(void)
    : m_(0)
    , dim_(2, 0)
    , d_(2, 0)
    , b_spd_(0)
{}

CSU_setup_t::CSU_setup_t(int m, double H, double W, double d1, double d2, double b_spd)
    : m_(m)
    ,dim_(2)
    , d_(2)
    , b_spd_(b_spd)
{
    dim_[0] = H;
    dim_[1] = W;
    d_[0] = d1;
    d_[1] = d2;
}

CSU_setup_t::~CSU_setup_t(void)
{}

void CSU_setup_t::get_json(json& CSU_conf) const
{
    CSU_conf["m"]       = m_;
    CSU_conf["dim"]     = dim_;
    CSU_conf["d"]       = d_;
    CSU_conf["b_spd"]   = b_spd_;
}

void CSU_setup_t::set_json(const json& CSU_conf)
{
    m_       = CSU_conf["m"].get<int>();
    dim_     = CSU_conf["dim"].get<vector<double> >();
    d_       = CSU_conf["d"].get<vector<double> >();
    b_spd_   = CSU_conf["b_spd"].get<double>();
}

}
