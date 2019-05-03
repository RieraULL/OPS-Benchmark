#include "EMIR_set_generator_t.hpp"

#include "EMIR_target_set_t.hpp"
#include "EMIR_target_set_2_LaTeX.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

EMIR::EMIR_set_generator_t::EMIR_set_generator_t(const instance_set_config_t& instance_set_config, const std::vector<target_set_t>& target_sets):
instance_set_config_(instance_set_config),
target_sets_(target_sets)
{
}

EMIR::EMIR_set_generator_t::~EMIR_set_generator_t(void)
{
}

void EMIR::EMIR_set_generator_t::generate(void)
{
	vector<EMIR_target_set_t> EMIR_target_sets;
	vector<EMIR_instance_t>   EMIR_instance_sets;	
	
	generate_targets(EMIR_target_sets);
	generate_instances(EMIR_target_sets,  EMIR_instance_sets);
	
	save_EMIR_target_sets(EMIR_target_sets);
	save_EMIR_instances(EMIR_instance_sets);
}

void EMIR::EMIR_set_generator_t::generate_targets(std::vector<EMIR_target_set_t>& EMIR_target_sets)
{
	const vector<int>& points_range = instance_set_config_.points_range_;
	instance_config_t config;
	instance_set_config_.get(config);
	
	int inx = 0;
		
	for(int n: points_range) {

		for (const target_set_t& ts: target_sets_) {
		
			inx ++;
			
			EMIR_target_set_t E_ts(config, inx);
			
			const int ts_sz = ts.size();
			int i = 0;			
			int j = 0;
			
			while ((j < ts_sz) && (i < n)) {
				
				const target_t target = ts[j];
				
				if (instance_set_config_.is_valid(target)) {
				
					E_ts.push_back(target);					
					i++;				
				}
				
				j++;
			}
		
			if ((j == ts_sz) && (i < n)) {
				std::cerr << "ERROR!!" << std::endl;
				exit(1);
			}
				
			EMIR_target_sets.push_back(E_ts);			
		}
		
	}
}

void EMIR::EMIR_set_generator_t::generate_instances(const std::vector<EMIR_target_set_t>& EMIR_target_sets, std::vector<EMIR_instance_t>& EMIR_instance_sets)
{
	const vector<double> alphas = instance_set_config_.L_range_percent_;
	
	int inx = 0;
	
	for(const EMIR_target_set_t& TS: EMIR_target_sets) {
		
		for(const double alpha: alphas) {
			
			inx ++;
			
			EMIR_instance_t I;
			
			I.set(instance_set_config_, TS, alpha, inx);
			
			EMIR_instance_sets.push_back(I);
		}	
	}
}

void EMIR::EMIR_set_generator_t::save_EMIR_instances(std::vector<EMIR_instance_t>& EMIR_instance_sets)
{
    const string& name        = instance_set_config_.name_;
    const string& family_path = instance_set_config_.path_ + "/" + name;
    const string& instance_path = family_path + "/instances/";
	
    string command;

    command = "mkdir " + family_path;
    system(command.c_str());

    command = "rm -rf " + instance_path;
    system(command.c_str());

    command = "mkdir "  + instance_path;
    system(command.c_str());

    for(const EMIR_instance_t& EMIR_instance: EMIR_instance_sets) {
		
        const string& instance_name = EMIR_instance.get_instance_name();
        const string  filename      = instance_path + instance_name + ".txt";

        ofstream of(filename);
        EMIR_instance.write(of);
        of.close();
    }
}


void EMIR::EMIR_set_generator_t::save_EMIR_target_sets(const std::vector<EMIR_target_set_t>& EMIR_target_sets)
{
    EMIR_target_TIKZ target_TIKZ(instance_set_config_);

    const string& name        = instance_set_config_.name_;
    const string& family_path = instance_set_config_.path_ + "/" + name;
    const string& target_path = family_path + "/targets/";

    string command;

    command = "mkdir " + family_path;
    system(command.c_str());

    command = "rm -rf " + target_path;
    system(command.c_str());

    command = "mkdir "  + target_path;
    system(command.c_str());

    command = "mkdir "  + target_path + "LaTeX/";
    system(command.c_str());

    command = "mkdir "  + target_path + "PDF/";
    system(command.c_str());

    for(const EMIR_target_set_t& EMIR_target_set: EMIR_target_sets) {

        const string  fullname = EMIR_target_set.get_filename();
        const string  filename = target_path + fullname + ".txt";
        const string  ltexname = target_path + "LaTeX/" + fullname + ".tex";

        //cout << fullname << endl;
        //cout << filename << endl;
        //cout << ltexname << endl;

        ofstream of(filename);
        EMIR_target_set.write(of);
        of.close();

        ofstream ltx(ltexname);
        target_TIKZ.write(ltx, EMIR_target_set);
        ltx.close();

        command = "pdflatex -output-directory " + target_path + "PDF/ " + ltexname;
        system(command.c_str());

        command = "rm " + target_path + "PDF/" + fullname + ".aux";
        system(command.c_str());

        command = "rm " + target_path + "PDF/" + fullname + ".log";
        system(command.c_str());
    }

    command = "rm -rf "  + target_path + "LaTeX/";
    system(command.c_str());
}
