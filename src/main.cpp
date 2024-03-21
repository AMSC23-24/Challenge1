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

    //Parse json file for parameters

    std::ifstream file("data.json");
    json data = json::parse(file);

    const unsigned int max_it = data.value("max_it",100);
    const double tol_step = data.value("tol_step",1e-6);
    const double tol_res = data.value("tol_res",1e-6);
    const double sigma = data.value("sigma",0.25);
    const double alpha_init = data.value("alpha_init",1.0);

    std::vector<double> init_guess = data["init_guess"].get<std::vector<double>>();

    std::string fun = data.value("fun","0.");

    //Muparser test

    mup::ParserX p;

    std::vector<mup::Value> val_vec{};
    std::vector<mup::Variable> var_vec{};

    for(int i = 0; i<init_guess.size();++i){
        val_vec.emplace_back(0.);
    }

    for(int i=0;i<init_guess.size();++i){
        var_vec.emplace_back(&val_vec[i]);
    }

    p.DefineVar("x",&var_vec[0]);
    p.DefineVar("y",&var_vec[1]);
    
    p.SetExpr(fun);

    auto muFun = [&val_vec,&p](std::vector<double> x){
        for(int i = 0; i<x.size();++i){
            val_vec[i]=x[i];
        }
        return (double)p.Eval().GetFloat();
    };

    gradientMethod method = gradientMethod(muFun,
                                           df,
                                           init_guess,
                                           max_it,
                                           tol_step,
                                           tol_res,
                                           sigma,
                                           alpha_init);

    double sol = method.minimize();

    return 0;

}

