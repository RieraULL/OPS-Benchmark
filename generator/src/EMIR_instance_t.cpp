#include "EMIR_instance_t.hpp"

#include <cmath>
#include <iomanip>

EMIR::EMIR_instance_t::EMIR_instance_t(void):
    id_(N_ITEM),
    type_(),
    Jk_(),
    Kj_(),
    T_(),
    b_(),
    alpha_(-1),
    L_(0),
	max_L_(0),
    scal_factor_(10)
{}

EMIR::EMIR_instance_t::~EMIR_instance_t(void)
{
}

void EMIR::EMIR_instance_t::get_json(json& instance) const
{
    json jT;
    T_.get_json(jT);

    instance["id"]       = id_;
    instance["type"]     = type_;

    instance["Jk"]       = Jk_;
    instance["T"]        = jT;
    instance["b"]        = b_;
    instance["alpha"]    = alpha_;
    instance["L"]        = L_;
	instance["max_L"]    = max_L_;
}

void EMIR::EMIR_instance_t::set_json(const json& instance)
{
    json jT   = instance["T"];

    T_.set_json(jT);

    id_   = instance["id"].get<vector<string> >();
    type_ = instance["type"].get<int>();
    Jk_   = instance["Jk"].get<vector<vector<int> > >();
    b_    = instance["b"].get<vector<int> >();
    alpha_= instance["alpha"].get<double>();
    L_    = instance["L"].get<int>();       
	max_L_= instance["max_L"].get<int>();        
}

istream& EMIR::EMIR_instance_t::read(istream& is)
{
    json instance;
    is >> instance;

    set_json(instance);
    
    make_Kj();

    return is;
}

int EMIR::EMIR_instance_t::get_max_Jk(void) const
{
    int max = 0;

    for(auto Jk: Jk_)
        if ((int)(Jk.size()) > max)
            max = Jk.size();

    return max;
}

void EMIR::EMIR_instance_t::set(double alpha)
{
    alpha_ = alpha;
    L_     = round(double(max_L_) * alpha_);
	
}

const string EMIR::EMIR_instance_t::get_file_name(int inx) const
{
	stringstream ss;
	ss << "_a" << int(trunc(alpha_ * 100));
	ss << "_"<< setfill('0') << setw(3) << inx;
	const string sufix = ss.str();
	const string fullname = get_instance_name() + sufix;
	
	return fullname;
}

void EMIR::EMIR_instance_t::set(const instance_set_config_t& config, const EMIR_target_set_t& TS, double alpha, int inx)
{
	id_[NAME] = TS.get_filename();	
    id_[STAMP]= config.stamp_;
	
	config.make_processor_assignment(TS, Jk_);
	make_cost_matrix(config, TS, T_);
	get_priority(TS, b_);
	
	max_L_ = get_tours_len(TS);
	
	set(alpha);		
	
	const string& instance_name = get_file_name(inx);
	id_[NAME] = instance_name;	
}


int EMIR::EMIR_instance_t::tround(double num) const
{
    return trunc(num * 10);
}

void EMIR::EMIR_instance_t::make_cost_matrix(const instance_set_config_t& config, const EMIR_target_set_t& TS, matrix<int>& T) const
{
    const double b_spd = config.CSU_.b_spd();
    
    matrix<double> T1;
    
    TS.get_time_matrix(b_spd, T1);
    
    T.resize(T1.get_m(), T1.get_n());
    
    const int n = TS.size();
    
    for(int i = 0; i < n; i++)
        T(1, i + 2) = tround(T1(1, i + 2));             
        
    for(int i = 0; i < n; i++)
        T(i + 2, n + 2) = tround(T1(i + 2, n + 2) + TS[i].get_p());  // From point to center (0,0)        

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (i != j)                                
                T(i + 2, j + 2) = tround(T1(i + 2, j + 2) + TS[i].get_p());            
                            

}

int EMIR::EMIR_instance_t::get_tours_len(const EMIR_target_set_t& TS)
{

    int max_range = 0;
    
    for(auto cJk: Jk_){
        
        int range = 0;
        
        if (cJk.size() > 0){
        
            double min     = 0.0;
            double max     = 0.0;
            double total_p = 0.0;
            
            for(auto j: cJk) {
                
                const double y = TS[j - 1].get_x();
				
                if (y < min) min = y;
                if (y > max) max = y;
                
                total_p += TS[j - 1].get_p();
            }                        
           
            const double drange = max - min;
            
            range = tround(drange + total_p);                
        }        
        
        if (range > max_range)
            max_range = range;
    }    
    
    return max_range;
}

void EMIR::EMIR_instance_t::get_priority(const EMIR_target_set_t& TS, vector<int>& b) const
{
	b.clear();
    b.push_back(0);
    for(auto c_target = TS.begin(); c_target != TS.end(); ++ c_target)
        b.push_back((*c_target).get_b());
    b.push_back(0);
}

void EMIR::EMIR_instance_t::make_Kj(void)
{
    Kj_.clear();

    const int K = get_m();

    Kj_.resize(get_n());

    for(int k = 0; k < K; k++) {

        const vector<int>& Jk = get_Jk(k);

        for(int i: Jk)
            Kj_[i].push_back(k);
    }
}

ostream& EMIR::EMIR_instance_t::write(ostream& os) const
{
    json instance;
    get_json(instance);

    os << setw(2) << instance;

    return os;
}

istream& operator>>(istream& is, EMIR::EMIR_instance_t& I)
{
    I.read(is);
    return is;
}

ostream& operator<<(ostream& os, const EMIR::EMIR_instance_t& I)
{
    I.write(os);
    return os;
}
