#pragma once

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

namespace EMIR
{

	
class target_range_t
{

private:
    vector<double>  p_range_;   /**< Exposure time range */
    vector<double>  b_levels_;  /**< Priority levels */

public:
    target_range_t(void);
    target_range_t(const vector<double>& p_range, const vector<double>& b_levels);
    virtual ~target_range_t(void);

    inline const vector<double>& get_p_range(void) const
    {
        return p_range_;
    }
    inline const vector<double>& get_b_levels(void) const
    {
        return b_levels_;
    }

};
}
