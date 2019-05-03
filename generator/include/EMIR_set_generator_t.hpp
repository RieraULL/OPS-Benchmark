#pragma once

#include <vector>

#include "instance_set_config_t.hpp"
#include "target_set_t.hpp"
#include "EMIR_target_set_t.hpp"
#include "EMIR_instance_t.hpp"

namespace EMIR
{

class EMIR_set_generator_t
{
	const instance_set_config_t&     instance_set_config_;
	const std::vector<target_set_t>& target_sets_;
	
public:
	EMIR_set_generator_t(const instance_set_config_t& instance_set_config, const std::vector<target_set_t>& target_sets);
	~EMIR_set_generator_t(void);

	void generate(void);
	
private:		
	void generate_targets(std::vector<EMIR_target_set_t>& EMIR_target_sets);	
	void generate_instances(const std::vector<EMIR_target_set_t>& EMIR_target_sets, std::vector<EMIR_instance_t>& EMIR_instance_sets);
	
	void save_EMIR_target_sets(const std::vector<EMIR_target_set_t>& EMIR_target_sets);
	void save_EMIR_instances(std::vector<EMIR_instance_t>& EMIR_instance_sets);
};

}

