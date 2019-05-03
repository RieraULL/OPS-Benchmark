#include "point_t.hpp"

#include <vector>
#include <cmath>

namespace EMIR
{

void point_t::get_json(json& point) const
{
    const double x = round(first  * 1E4) / 1E4;
    const double y = round(second * 1E4) / 1E4;
    
    point.push_back(x);
    point.push_back(y);
}

void point_t::set_json(const json& point)
{
    vector<double> v = point.get<vector<double> >();

    first  = v[0];
    second = v[1];
}

ostream& point_t::write(ostream& os) const
{

    json point;
    get_json(point);

    os << point;
    return os;
}

}
