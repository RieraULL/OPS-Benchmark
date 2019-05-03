#pragma once

#include "source_configurations.hpp"
#include "target_set_t.hpp"

#include <vector>

namespace EMIR
{

class target_generator_t
{
public:
	target_generator_t(void);
	~target_generator_t(void);
	
	void generate(const source_config_t& configuration, std::vector<target_set_t>& target_sets);
};

}

