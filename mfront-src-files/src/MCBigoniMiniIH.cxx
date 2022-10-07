/*!
* \file   MCBigoniMiniIH.cxx
* \brief  this file implements the MCBigoniMiniIH Behaviour.
*         File generated by tfel version 3.4.0
* \author Simon Raude
* \date   07 / 10 / 2022
 */

#include<string>
#include<cstring>
#include<sstream>
#include<fstream>
#include<stdexcept>

#include"TFEL/Raise.hxx"
#include"TFEL/Material/MCBigoniMiniIHBehaviourData.hxx"
#include"TFEL/Material/MCBigoniMiniIHIntegrationData.hxx"
#include"TFEL/Material/MCBigoniMiniIH.hxx"

namespace tfel{

namespace material{

MCBigoniMiniIHParametersInitializer&
MCBigoniMiniIHParametersInitializer::get()
{
static MCBigoniMiniIHParametersInitializer i;
return i;
}

MCBigoniMiniIHParametersInitializer::MCBigoniMiniIHParametersInitializer()
{
this->theta = 1;
this->epsilon = 1e-14;
this->minimal_time_step_scaling_factor = 0.1;
this->maximal_time_step_scaling_factor = 1.79769e+308;
this->numerical_jacobian_epsilon = 1e-15;
this->iterMax = 100;
// Reading parameters from a file
MCBigoniMiniIHParametersInitializer::readParameters(*this,"MCBigoniMiniIH-parameters.txt");
}

void
MCBigoniMiniIHParametersInitializer::set(const char* const key,
const double v){
using namespace std;
if(::strcmp("theta",key)==0){
this->theta = v;
} else if(::strcmp("epsilon",key)==0){
this->epsilon = v;
} else if(::strcmp("minimal_time_step_scaling_factor",key)==0){
this->minimal_time_step_scaling_factor = v;
} else if(::strcmp("maximal_time_step_scaling_factor",key)==0){
this->maximal_time_step_scaling_factor = v;
} else if(::strcmp("numerical_jacobian_epsilon",key)==0){
this->numerical_jacobian_epsilon = v;
} else {
tfel::raise("MCBigoniMiniIHParametersInitializer::set: "
" no parameter named '"+std::string(key)+"'");
}
}

void
MCBigoniMiniIHParametersInitializer::set(const char* const key,
const unsigned short v){
using namespace std;
if(::strcmp("iterMax",key)==0){
this->iterMax = v;
} else {
tfel::raise("MCBigoniMiniIHParametersInitializer::set: "
"no parameter named '"+std::string(key)+"'");
}
}

double
MCBigoniMiniIHParametersInitializer::getDouble(const std::string& n,
const std::string& v)
{
double value;
std::istringstream converter(v);
converter >> value;
tfel::raise_if(!converter||(!converter.eof()),
"MCBigoniMiniIHParametersInitializer::getDouble: "
"can't convert '"+v+"' to double for parameter '"+ n+"'");
return value;
}

unsigned short
MCBigoniMiniIHParametersInitializer::getUnsignedShort(const std::string& n,
const std::string& v)
{
unsigned short value;
std::istringstream converter(v);
converter >> value;
tfel::raise_if(!converter||(!converter.eof()),
"MCBigoniMiniIHParametersInitializer::getUnsignedShort: "
"can't convert '"+v+"' to unsigned short for parameter '"+ n+"'");
return value;
}

void
MCBigoniMiniIHParametersInitializer::readParameters(MCBigoniMiniIHParametersInitializer& pi,const char* const fn){
auto tokenize = [](const std::string& line){
std::istringstream tokenizer(line);
std::vector<std::string> tokens;
std::copy(std::istream_iterator<std::string>(tokenizer),
std::istream_iterator<std::string>(),
std::back_inserter(tokens));
return tokens;
};
std::ifstream f(fn);
if(!f){
return;
}
size_t ln = 1u;
while(!f.eof()){
auto line = std::string{};
std::getline(f,line);
auto tokens = tokenize(line);
auto throw_if = [ln,line,fn](const bool c,const std::string& m){
tfel::raise_if(c,"MCBigoniMiniIHParametersInitializer::readParameters: "
"error at line '"+std::to_string(ln)+"' "
"while reading parameter file '"+std::string(fn)+"'"
"("+m+")");
};
if(tokens.empty()){
continue;
}
if(tokens[0][0]=='#'){
continue;
}
throw_if(tokens.size()!=2u,"invalid number of tokens");
if("theta"==tokens[0]){
pi.theta = MCBigoniMiniIHParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("epsilon"==tokens[0]){
pi.epsilon = MCBigoniMiniIHParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("minimal_time_step_scaling_factor"==tokens[0]){
pi.minimal_time_step_scaling_factor = MCBigoniMiniIHParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("maximal_time_step_scaling_factor"==tokens[0]){
pi.maximal_time_step_scaling_factor = MCBigoniMiniIHParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("numerical_jacobian_epsilon"==tokens[0]){
pi.numerical_jacobian_epsilon = MCBigoniMiniIHParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("iterMax"==tokens[0]){
pi.iterMax = MCBigoniMiniIHParametersInitializer::getUnsignedShort(tokens[0],tokens[1]);
} else {
throw_if(true,"invalid parameter '"+tokens[0]+"'");
}
}
}

} // end of namespace material

} // end of namespace tfel

