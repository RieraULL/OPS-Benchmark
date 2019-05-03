#pragma once

#include "CSU_setup_t.hpp"
#include "target_range_t.hpp"
#include "target_set_t.hpp"

#include "instance_config_t.hpp"
#include "instance_type_code.hpp"
#include "point_t.hpp"

#include <string>
#include <vector>

using namespace std;

namespace EMIR
{
	
class instance_set_config_t
{	
  public:
    const string name_;
    const string path_;
    const string stamp_;
    const int type_;
    const vector<int> points_range_;
    const vector<double> L_range_percent_;

    const CSU_setup_t CSU_;
	
  protected:
		double upper_limit_;
		double lower_limit_;	

  public:
    instance_set_config_t(const string& name,
                          const string& path,
                          const int type,
                          const vector<int>& points_range,
                          const vector<double> L_range_percent,
                          const CSU_setup_t& CSU,
						  double upper_limit,
						  double lower_limit
						  )
      : name_(name)
      , path_(path)
      , stamp_(get_date())
      , type_(type)
      , points_range_(points_range)
      , L_range_percent_(L_range_percent)
      , CSU_(CSU)
	  , upper_limit_(upper_limit)
	  , lower_limit_(lower_limit)
    {
    }

    virtual ~instance_set_config_t(void)
    {
    }

    void get(instance_config_t& c) const;
	
    inline bool is_valid(const point_t& p) const
    {
		return ((p.get_y() <= upper_limit_) && (p.get_y() >= lower_limit_));
    }	
	
	void make_processor_assignment(const target_set_t& targets, vector<vector<int> >& Jk) const;		

  private:
    const string get_date(void) const;
	const pair<int, double> get_bar(const target_t& target) const;
	
  protected:
	
	virtual void assignment(const pair<int,double>& bar, const int i, vector<vector<int> >& Jk) const = 0;	
};

}