#include "gradientMethod.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include "muparserx/mpParser.h"

using json = nlohmann::json;

int main(){

    //Define function and derivative

    auto f = [](std::vector<double> x ){
        return x[0]*x[1] + 4*x[0]*x[0]*x[0]*x[0] + x[1]*x[1] + 3*x[0];
    };
    auto df = [](std::vector<double> x)-> std::vector<double>{
        return {x[1] + 16*x[0]*x[0]*x[0] + 3, x[0] + 2*x[1]};
    };

    //Parse json file for parameters, functions and variables

    std::ifstream file("data.json");
    json data = json::parse(file);

    const unsigned int max_it = data.value("max_it",100);
    const double tol_step = data.value("tol_step",1e-6);
    const double tol_res = data.value("tol_res",1e-6);
    const double sigma = data.value("sigma",0.25);
    const double alpha_init = data.value("alpha_init",1.0);

    std::vector<double> init_guess = data["init_guess"].get<std::vector<double>>();

    std::string fun = data.value("fun","0.");
    std::vector<std::string> dfun = data["dfun"].get<std::vector<std::string>>();

    std::vector<std::string> identifiers = data["vars"].get<std::vector<std::string>>();

    mup::ParserX p_fun; //initialize parser for function
    std::vector<mup::ParserX> p_dfun; 

    for(int i=0; i<init_guess.size();++i){ //initialize parser for gradient
        p_dfun.emplace_back();
    }

    //initialize values and variables

    std::vector<mup::Value> val_vec{};
    std::vector<mup::Variable> var_vec{};

    for(int i = 0; i<init_guess.size();++i){
        val_vec.emplace_back(0.);
    }

    for(int i=0;i<init_guess.size();++i){
        var_vec.emplace_back(&val_vec[i]);
    }

    //associates variables with the respective identifiers, for each parser

    for(int i = 0; i< identifiers.size();++i){
        p_fun.DefineVar(identifiers[i],&var_vec[i]);
    }

    for(int i = 0; i<p_dfun.size();++i){
        for(int j = 0; j<identifiers.size();++j){
            p_dfun[i].DefineVar(identifiers[j],&var_vec[j]);
        }
    }

    //sets the functions for each parser

    p_fun.SetExpr(fun);

    for(int i = 0; i<p_dfun.size();++i){
        p_dfun[i].SetExpr(dfun[i]);
    }

    //define function wrappers for function and gradient for use in gradientMethod

    auto muFun = [&val_vec,&p_fun](std::vector<double> x){
        for(int i = 0; i<x.size();++i){
            val_vec[i]=x[i];
        }
        return static_cast<double>(p_fun.Eval().GetFloat());
    };

    auto muDFun = [&val_vec,&p_dfun](std::vector<double> x)->std::vector<double>{
        std::vector<double> ret{};
        for(int i = 0; i<x.size();++i){
            val_vec[i]=x[i];
        }
        for(int i = 0; i<x.size();++i){
            ret.push_back(static_cast<double>(p_dfun[i].Eval().GetFloat()));
        }
        return ret;
    };

    gradientMethod method = gradientMethod(muFun,
                                           muDFun,
                                           init_guess,
                                           max_it,
                                           tol_step,
                                           tol_res,
                                           sigma,
                                           alpha_init);

    double sol = method.minimize();

    return 0;

}

