#pragma once

#include <iostream>
#include <vector>

#include "../json/json.hpp"
using json = nlohmann::json;

using namespace std;

namespace EMIR
{
 
class CSU_setup_t
{
private:
    int            m_;	        /**< Number of bars */
    vector<double> dim_;        /**< height of field (arcsecs) width of field (arcsecs) */
    vector<double> d_;          /**< Bar upper dead zone (arcsecs) Bar lower dead zone (arcsecs) */
    double         b_spd_;      /**< Bar speed (arcsecs/s) */

public:
    CSU_setup_t(void);
    CSU_setup_t(int m, double H, double W, double d1, double d2, double b_sp);
    virtual ~CSU_setup_t(void);

    inline int get_m(void) const
    {
        return m_;
    }

    inline double get_h(void) const
    {
        return get_H() / (double)(get_m());
    }

    inline double get_H(void) const    
    {
        return dim_[0];
    }

    inline double get_W(void) const
    {
        return dim_[1];
    }

    inline double get_d1(void) const
    {
        return d_[0];
    }

    inline double get_d2(void) const
    {
        return d_[1];
    }

    inline double b_spd(void) const
    {
        return b_spd_;
    }

    void get_json(json& CSU_conf) const;
    void set_json(const json& CSU_conf);
};

}
