#pragma once

#include <vector>
#include "EMIR_param.hpp"

namespace EMIR
{

class valid_range_t: public std::vector<double>
{
public:
	valid_range_t(void);
	valid_range_t(const std::vector<double> bounds);
	
	~valid_range_t();
	
    inline double up(void) const
    {
        return  at(0);
    }

    inline double down(void) const
    {
        return at(1);
    }
};

class A_range: public valid_range_t
{
	A_range(void):
		valid_range_t({UP_CSU - d1_CSU, DW_CSU + d2_CSU}) {}
		
	~A_range(void) {}
};

class B_range: public valid_range_t
{
	B_range(void):
		valid_range_t({UP_CSU - (h_CSU * 0.5), DW_CSU + (h_CSU * 0.5)}) {}
		
	~B_range(void) {}
};

class C_range: public valid_range_t
{
	C_range(void):
		valid_range_t({UP_CSU - h_CSU, DW_CSU + h_CSU}) {}
		
	~C_range(void) {}
};

class D_range: public valid_range_t
{
	D_range(void):
		valid_range_t({UP_CSU - (h_CSU * 1.5), DW_CSU + (h_CSU * 1.5)}) {}
		
	~D_range(void) {}
};


}


