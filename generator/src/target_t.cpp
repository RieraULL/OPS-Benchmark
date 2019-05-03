#include "target_t.hpp"

#include <cmath>

namespace EMIR
{

ostream& target_t::write(ostream& os) const
{
    json target;
    get_json(target);

    os << target;
    return os;
}

istream& target_t::read(istream& is)
{
    return is;
}

void target_t::get_json(json& target) const
{
    json coord;
    ((point_t*)(this))-> get_json(coord);
    
    const double p = round(p_ * 10) / 10.0;
    const int    b = round(b_ * 10);

    target["coord"] = coord;
    target["p"]     = p;
    target["b"]     = b;
}


void target_t::set_json(const json& target)
{
    json coord = target["coord"];
    p_         = target["p"].get<double>();
    b_         = target["b"].get<int>();

    ((point_t*)(this))->set_json(coord);
}


}
