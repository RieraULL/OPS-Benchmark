#include "EMIR_target_set_t.hpp"
#include "instance_type_code.hpp"

EMIR::EMIR_target_set_t::EMIR_target_set_t(const instance_config_t& config, int inx):
        target_set_t(),
		config_(config),
        inx_(inx)
    {}
	
EMIR::EMIR_target_set_t::EMIR_target_set_t(void):
        target_set_t(),
        config_(),
        inx_(-1)
    {}	


EMIR::EMIR_target_set_t::~EMIR_target_set_t()
{
}


void EMIR::EMIR_target_set_t::write(ostream& os) const
{
    json target_set;
    get_json(target_set);
    os  << target_set.dump(4) << endl;
}

void EMIR::EMIR_target_set_t::read(istream& is)
{
    json target_set;
    is >> target_set;
    set_json(target_set);
}

void EMIR::EMIR_target_set_t::get_json(json& target_set) const
{
    json targets;

    for(auto target = begin(); target != end(); ++target) {
        json c_target;
        (*target).get_json(c_target);

        targets.push_back(c_target);
    }

    target_set["name"]          = config_.name_;
    target_set["stamp"]         = config_.stamp_;
    target_set["instance_type"] = config_.type_; 
	target_set["inx"]           = inx_;
    target_set["targets"]       = targets;
}

void EMIR::EMIR_target_set_t::set_json(const json& target_set)
{
    json targets   = target_set["targets"];    
    
    config_.name_          = target_set["name"].get<string>();
    config_.stamp_         = target_set["stamp"].get<string>();
    config_.type_          = target_set["instance_type"].get<int>();
	inx_                   = target_set["inx"].get<int>();

    clear();
    for(auto target_it = targets.begin(); target_it != targets.end(); ++ target_it) {

        json jtarget = *target_it;
        target_t target;
        target.set_json(jtarget);
        push_back(target);
    }
}

const string EMIR::EMIR_target_set_t::get_filename(void) const
{
    stringstream ss;
    ss << config_.name_;
    //ss << "_" << intance_type_short[config_.type_];
    ss << "_n" << setfill('0') << setw(3) <<  size();
    ss << "_" << setfill('0') << setw(3) << inx_;
    string fullname = ss.str();

    return fullname;
}


void EMIR::EMIR_target_set_t::get_time_matrix(double speed, matrix<double>& T) const
{
    const int n = size();

    T.resize(n + 2, n + 2);
    T.init(-1);

    T(1, n + 2) = 0;

    for(int i = 0; i < n; i++)
        T(1, i + 2) = (fabs(at(i).get_coord().get_x()) * speed);  // From center (0,0) to point

    for(int i = 0; i < n; i++)
        T(i + 2, n + 2) = (fabs(at(i).get_coord().get_x()) * speed);  // From point to center (0,0)

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (i != j)
                T(i + 2, j + 2) = (fabs(at(i).get_coord().get_x() - at(j).get_coord().get_x()) * speed);    
}


ostream& operator<<(ostream& os, const EMIR::EMIR_target_set_t& target_set)
{
    target_set.write(os);
    return os;
}

istream& operator>>(istream& is, EMIR::EMIR_target_set_t& target_set)
{
    target_set.read(is);
    return is;
}