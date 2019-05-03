#include "instance_set_config_t.hpp"

#include <ctime>
#include <cassert>

const string EMIR::instance_set_config_t::get_date(void) const
{
	time_t date = time(0);
	struct tm * timeinfo; 

	timeinfo = localtime(&date);

	char* fecha = asctime(timeinfo);
	fecha[strlen(fecha) - 1] = 0;

	string str(fecha);

	return str;
}

void EMIR::instance_set_config_t::get(instance_config_t& c) const
{
	c.set(name_, path_, stamp_, type_);
}

const pair<int, double> EMIR::instance_set_config_t::get_bar(const target_t& target) const
{
	const double CSU_half = CSU_.get_H() * 0.5;		
	const double h        = CSU_.get_h();
	const double y        = target.get_y();
	const double dpos     = (CSU_half + y) / h;
	const int    bar      = trunc(dpos);
	const double rpos     = dpos - trunc(dpos);	
	
	assert(CSU_.get_m() > bar);
	
	return pair<int,double> (bar, rpos);
}

void EMIR::instance_set_config_t::make_processor_assignment(const target_set_t& targets, vector<vector<int> >& Jk) const
{		
	Jk.resize(CSU_.get_m());
	const int sz = targets.size();

	for(int i = 0; i< sz; i++) 
		assignment(get_bar(targets[i]), i, Jk);		
}