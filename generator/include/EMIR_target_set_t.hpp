#pragma once

#include <string>
#include <vector>

#include "target_set_t.hpp"
#include "matrix.hpp"

#include "instance_config_t.hpp"

namespace EMIR
{

class EMIR_target_set_t: public target_set_t
{
public:
    instance_config_t config_;
	int               inx_;

public:
	EMIR_target_set_t(const instance_config_t& config, int inx);
	EMIR_target_set_t(void);
	~EMIR_target_set_t();

    void write(ostream& os) const;
    void read(istream& is);
    
    const string get_filename(void) const;    
    virtual void get_time_matrix(double speed, matrix<double>& T) const;
	inline int get_n(void) const {return size();}
	
	inline const string get_name(void) const {return config_.name_;}
	inline const string get_stamp(void) const {return config_.stamp_;}

private:
    void get_json(json& target_set) const;
    void set_json(const json& target_set);

};


}

ostream& operator<<(ostream& os, const EMIR::EMIR_target_set_t& target_set);
istream& operator>>(istream& is, EMIR::EMIR_target_set_t& target_set);
