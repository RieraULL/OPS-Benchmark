#include "target_generator_t.hpp"
#include <random>

EMIR::target_generator_t::target_generator_t(void)
{
}

EMIR::target_generator_t::~target_generator_t(void)
{
}

void EMIR::target_generator_t::generate(const source_config_t& configuration, std::vector<target_set_t>& target_sets)
{
	const CSU_setup_t& CSU      = configuration.CSU_type_;
    const target_range_t& range = configuration.target_range_;
	const int n                 = configuration.n_;
	const vector<int>& seed     = configuration.seed_range_ ;
	
	const double Heigh = CSU.get_H();
	const double Width = CSU.get_W();
	
	const double N = Heigh * 0.5;
	const double S = -N;
	const double E = Width * 0.5;
	const double W = -E;
	
	const vector<double>& b_levels = range.get_b_levels();
	
	for(int s: seed){
		
		default_random_engine generator(s);
		
		uniform_real_distribution<double> distribution_x(W, E);
		uniform_real_distribution<double> distribution_y(S, N);
		uniform_real_distribution<double> distribution_time(range.get_p_range()[0], range.get_p_range()[1]);
		uniform_int_distribution<int>     distribution_priority(0, b_levels.size() - 1);			
		
		target_set_t target_set;

		for(int i = 0; i < n; i++) {

				const double x = distribution_x(generator);
				const double y = distribution_y(generator);
				
				const point_t point = point_t(x, y);
				
				const double p = round(distribution_time(generator));
				const int    l = distribution_priority(generator);
				const double b = b_levels[l];			
				
				target_set.push_back(target_t(point, p, b));
		}

		target_sets.push_back(target_set);
	}
}

