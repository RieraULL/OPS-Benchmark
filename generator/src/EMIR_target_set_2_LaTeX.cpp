#include "EMIR_target_set_2_LaTeX.hpp"

#include <iomanip>
#include <string>

using namespace std;


namespace EMIR {
    

    EMIR_target_TIKZ::EMIR_target_TIKZ(const instance_set_config_t& config):
        x_limit_(40), y_limit_(40), scal_x_(x_limit_ / (double)(config.CSU_.get_W())), scal_y_(y_limit_ / (double)(config.CSU_.get_H())),
		config_(config) {}
    
    EMIR_target_TIKZ::~EMIR_target_TIKZ(void) {}
    
    ostream& EMIR_target_TIKZ::write(ostream& os, const EMIR_target_set_t& TS)
    {
        
        os << TIKZ_HEADER       << endl;
        os << TIKZ_GANTT_HEADER << endl;  

        os << TIKZ_OPENING      << endl;      
        
        ////////////////////////////////
        
        os << TIKZ_TEX_BOX_STY  << endl;
        os << TIKZ_TEX_BOX_HDR  << endl;
        
        full_description(os, TS);
        
        os << TIKZ_TEX_BOX_FT   << endl;
        
        os << TIKZ_TEX_BOX_TTL  << endl;
        
        name(os, TS);
        
        os << TIKZ_FIG_CLOSING  << endl;
        
        os << TIKZ_END_MINI     << endl;
        
        ///////////////////////////////

        
        os << TIKZ_FIG_HEADER   << endl;
        
        CSU  (os, TS);
        stars(os, TS);
         
        os << TIKZ_FIG_CLOSING  << endl;
        os << TIKZ_END_MINI     << endl;
        
        ///////////////////////////////
        
        os << TIKZ_CLOSING      << endl;
        
        return os;
    }
    
    ostream& EMIR_target_TIKZ::stars(ostream& os, const EMIR_target_set_t& TS)
    {
        const CSU_setup_t& CSU_setup = config_.CSU_;

                
        const double CSU_H = CSU_setup.get_H();        
        
        int inx = 1;
        for(const target_t& target: TS)
        {
            const point_t& point = target.get_coord();           
            
            os << "\t \t \\node [cross=3pt, rotate = 45, blue] (" << inx << ") at (" << point.first * scal_x_<< ", " << (point.second + CSU_H * 0.5) * scal_y_ << ")  [label=45:\\scriptsize $" << inx << "$]{};" << endl;
            inx ++;
        }
        
        return os;
    }
    
    ostream& EMIR_target_TIKZ::CSU(ostream& os, const EMIR_target_set_t& TS)
    {
        const CSU_setup_t& CSU_setup = config_.CSU_;
        
        const int m = CSU_setup.get_m();
        
        const double CSU_w = CSU_setup.get_W();
        const double h     = CSU_setup.get_h();
        const double d1    = CSU_setup.get_d1();
        const double d2    = CSU_setup.get_d2();        
        
        ostringstream box;
        
        //box << "\\path [use as bounding box]  ( " << x1 <<  ", " <<  y1 << " ) rectangle ( " <<  y2 << ", " << y2 << " ); \\n";
        
        string boxstr = box.str(); 
        
        os << boxstr << endl;                
        
        const double n_CSU_w =  CSU_w * scal_x_;
        //const double n_CSU_h =  CSU_h * scal_y_;
        //const double n_h     =  n_CSU_h / ((double)(m));   
        const double n_d1    =  d1 * scal_y_;
        const double n_d2    =  d2 * scal_y_;
        
        for(int i = 0; i < m; i++) {  

            const double n_h1    =  (h * (double)(i)) * scal_y_;
            const double n_h2    =  (h * (double)(i + 1)) * scal_y_;
            const double n_h3    =  (h * ((double)(i) + 0.5)) * scal_y_;
            
            os << "\t \t \\slit{" <<  n_CSU_w << "}{" << n_h2 << "}{" << n_h1 << "}{" << n_h3 << "}{" << n_d2 << "}{" << n_d1 << "}{" << i + 1 << "};" << endl;            
        }
        
        os << endl;
        
        return os;
    } 

    ostream& EMIR_target_TIKZ::full_description(ostream& os, const EMIR_target_set_t& TS)
    {

        const CSU_setup_t& CSU_st = config_.CSU_;
        
        os << "\t \t \\begin{tabular}{ llcr }" << endl;        
        os << "\\\\" << endl;
        os << "\t \t  $n$ & \\hspace{4.0cm} &  &" << setw(6) << TS.size() << " \\\\" << endl;
        os << "\t \t  $m$                &  &  &" << setw(6) << CSU_st.get_m() << " \\\\" << endl;
        os << "\t \t  CSU$_w$            &  &  &" << setw(6) << fixed << setprecision(2) << CSU_st.get_W() << " \\\\" << endl;
        os << "\t \t  CSU$_h$            &  &  &" << setw(6) << fixed << setprecision(2) << CSU_st.get_H() << " \\\\" << endl;
        os << "\t \t  $h$                &  &  &" << setw(6) << fixed << setprecision(2) << CSU_st.get_h() << " \\\\" << endl;
        os << "\t \t  $d_1$               & &  &" << setw(6) << fixed << setprecision(2) << CSU_st.get_d1() << " \\\\" << endl;
        os << "\t \t  $d_2$               & &  &" << setw(6) << fixed << setprecision(2) << CSU_st.get_d2() << " \\\\" << endl;
        os << "\t \t \\end{tabular}" << endl;
        
        return os;
    }
    
    ostream& EMIR_target_TIKZ::name(ostream& os, const EMIR_target_set_t& TS)
    {
        string name = TS.get_name();
        string bar ="_";
        
        size_t pos = 0;
        
        do {
            
            pos = name.find(bar, pos);
            
            if (pos != string::npos){     
                           
                name.replace(pos,1,"\\_");    
            
                pos ++;
                pos ++;
            }
            
        } while(pos != string::npos);
        
        os << "{" << name << " (" << TS.get_stamp() << ")};" << endl;
        return os;
    }

}