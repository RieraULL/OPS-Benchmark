#pragma once

#include <sstream>
#include <iostream>

#include "EMIR_target_set_t.hpp"
#include "instance_set_config_t.hpp"

using namespace std;

namespace EMIR
{

class EMIR_target_TIKZ
{

    private:
    
    const char* TIKZ_HEADER = {
        "\\documentclass{standalone}               \n\n \
         \\usepackage{tikz}                          \n \
                                                     \n \
         \\usetikzlibrary{arrows,positioning}        \n \
         \\usetikzlibrary{scopes}                    \n \
         \\usetikzlibrary{backgrounds}               \n \
                                                     \n \
         \\pgfdeclarelayer{nodelayer}                \n \
         \\pgfdeclarelayer{edgelayer}                \n \
         \\pgfsetlayers{edgelayer,nodelayer,main} \n \n \
                                                     \n \
         \\usetikzlibrary{shapes.misc}               \n \
         \\tikzset{cross/.style={cross out, draw=black, minimum size=2*(#1-\\pgflinewidth), inner sep=0pt, outer sep=0pt}, \n \
            %default radius will be 1pt. \n \
            cross/.default={1pt}}         \n "
    };

    const char* TIKZ_OPENING = {
        "\\begin{document} \n\n"
    };


    const char* TIKZ_CLOSING = {
        "\n\\end{document} \n"
    };


    const char* TIKZ_FIG_HEADER = {
        "\\noindent\\begin{minipage}[c]{48cm}                             \n \
         \\begin{tikzpicture}                                            \n\n \
         \\tikzstyle{nosty} = [draw=none,fill=none,right]                  \n \
	     \\tikzstyle{star}  = [circle, draw, thick,fill=black!20,right]    \n \
         \\tikzstyle{slit}  = [thick]                                    \n\n"
    };

    const char* TIKZ_FIG_CLOSING = {
        "\n\\end{tikzpicture}                                   \n"
    };

    const char* TIKZ_GANTT_HEADER = {
          "\\newcommand{\\slit}[7]{                                             \n \
                     \\def\\axi{-#1/2 -1}                                           \n \
                     \\def\\axd{ #1/2 + 1}                                                                               \n \
                     \\def\\ahb{(#3}                                   \n \
                     \\def\\aht{(#2}                          \n \
                     \\def\\ahh{#4}                            \n \
 					 \\def\\alp{-#1/2 - 2}                                   \n \
 					 \\def\\ahha{(#3 + #5}                             \n \
 					 \\def\\ahhb{(#2 - #6}                             \n \
                     \\def\\inx{#7}                                              \n \
\n \
 					\\node [nosty] (5) at ({\\axi}, {\\ahha}) {};               \n \
                    \\node [nosty] (8) at ({\\axd}, {\\ahhb}) {};               \n \
                                                                                 \n \
 					\\draw[draw=black!10, fill=black!10] (5.center) rectangle (8.center); \n \
                                              \n \
                    \\node [nosty] (0) at ({\\axi}, {\\ahb}) {};                \n \
                    \\node [nosty] (1) at ({\\axd}, {\\aht}) {};                \n \
                                                  \n \
					\\draw (0.center) rectangle (1.center);                               \n \
\n \
					\\node [nosty] (4) at ({\\alp} ,{\\ahh}) {\\scriptsize ${ \\inx}$};   \n \
           }                                                                     \n"
    };
    
    const char* TIKZ_TEX_BOX_STY = {
        "\\tikzstyle{mybox} = [draw=black, fill=white,                  \n \
         rectangle, rounded corners, inner sep=10pt, inner ysep=20pt]  \n \
         \\tikzstyle{fancytitle} =[fill=white, text=black]              \n"
    };    
    
    const char* TIKZ_TEX_BOX_HDR = {
    "\\noindent\\begin{minipage}[c]{10cm}                                \n \
      \\begin{tikzpicture}                                              \n \
        \\node [mybox] (box){                                          \n \
        \\begin{minipage}{0.75\\textwidth}                              \n "
    };
    
    const char* TIKZ_TEX_BOX_FT = {    
    "\\end{minipage}                                                  \n \
     };                                                              \n"
    };
    
    const char* TIKZ_END_MINI = {    
    "\\end{minipage}                                                  \n"
    };    
    
    const char* TIKZ_TEX_BOX_TTL = { 
    "\\node[fancytitle, right=10pt] at (box.north west) "
    };
    
    
    const double x_limit_;
    const double y_limit_;
    
    const double scal_x_;
    const double scal_y_;
	
	const instance_set_config_t& config_;
    
private:    
    
    ostream& CSU  (ostream& os, const EMIR_target_set_t& ts);
    ostream& stars(ostream& os, const EMIR_target_set_t& ts);
    
    ostream& full_description(ostream& os, const EMIR_target_set_t& ts);
    ostream& name(ostream& os, const EMIR_target_set_t& ts);

public:
    
    EMIR_target_TIKZ(const instance_set_config_t& config);
    ~EMIR_target_TIKZ(void);
    
    ostream& write(ostream& os, const EMIR_target_set_t& ts);
};



}
