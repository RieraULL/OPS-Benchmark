#pragma once

#include "CSU_setup_t.hpp"
#include "target_range_t.hpp"

#include "instance_type_code.hpp"

#include <vector>
#include <string>

using namespace std;



namespace EMIR
{

class source_config_t
{
public:

    const CSU_setup_t     CSU_type_;
    const target_range_t  target_range_;
	const int             n_;
    const vector<int>     seed_range_;

public:

    source_config_t(const CSU_setup_t&    CSU_type,
                    const target_range_t& target_range,
					int                   n,
                    const vector<int>&    seed_range):
        CSU_type_(CSU_type),
        target_range_(target_range),
		n_(n),
        seed_range_(seed_range){}

    virtual ~source_config_t(void) {}
};

}
