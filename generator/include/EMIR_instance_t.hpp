#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "matrix.hpp"
#include "json.hpp"

#include "instance_set_config_t.hpp"
#include "EMIR_target_set_t.hpp"

using json = nlohmann::json;
using namespace std;

#define N_ITEM 2

namespace EMIR
{

enum {NAME, STAMP};	
	
class EMIR_instance_t
{
private:
    vector<string>           id_;        /**< Id of the instance Id of the source target points @see target_set_t.hpp */

    int                     type_;      /**< Type of instance generation @see instance_code_type.hpp */

    vector<vector<int> >    Jk_;        /**< Assignment of jobs to processors \f$ J_k \f$ */
    vector<vector<int> >    Kj_;        /**< Assignment of processors to jobs \f$ J_k \f$ */
    matrix<int>             T_;         /**< Cost matrix \f$ T \f$ */
    vector<int>             b_;         /**< Profit for each job \f$ b \f$ */

    double                  alpha_;     /**< Percentage of the total tour */
    int                     L_;         /**< Time limit  \f$ L \f$ */
	
	int                     max_L_;
    
    double                  scal_factor_;
	
public:
	EMIR_instance_t(void);
	~EMIR_instance_t(void);

    istream& read(istream& is);
    ostream& write(ostream& os) const;

    inline const string&         get_instance_name(void)      const
    {
        return id_[NAME];
    }
    inline const string&         get_instance_stamp(void)      const
    {
        return id_[STAMP];
    }    
    inline int                   get_n(void)         const
    {
        return b_.size();
    }
    inline int                   get_m(void)         const
    {
        return Jk_.size();
    }
    inline const vector<int>  &  get_Jk(int k)       const
    {
        return Jk_[k];
    }
    inline int                   get_b(int j)        const
    {
        return b_[j];
    }
    inline int                   get_L(void)         const
    {
        return L_;
    }
    inline const matrix<int>  &  get_T(void)         const
    {
        return T_;
    }
    inline double                get_scal_factor(void) const
    {
        return scal_factor_;
    }

    int get_max_Jk(void) const;

    const vector<vector<int> >& get_Kj(void) const {return Kj_;}

	void set(const instance_set_config_t& config, const EMIR_target_set_t& TS, double alpha, int intx);

    void set(double alpha);
	
	const string get_file_name(int inx) const;

private:
    void get_json(json& instance) const;
    void set_json(const json& instance);
    
    void make_Kj(void);
	
	int tround(double num) const;
	void make_cost_matrix(const instance_set_config_t& config, const EMIR_target_set_t& TS, matrix<int>& T) const;
	void get_priority(const EMIR_target_set_t& TS, vector<int>& b) const;
	int get_tours_len(const EMIR_target_set_t& TS);
};

}


istream& operator>>(istream& is, EMIR::EMIR_instance_t& input);
ostream& operator<<(ostream& os, const EMIR::EMIR_instance_t& input);
