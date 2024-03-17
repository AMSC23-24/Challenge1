#include "gradientMethod.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

int main(){
    auto f = [](std::vector<double> x ){
        return x[0]*x[1] + 4*x[0]*x[0]*x[0]*x[0] + x[1]*x[1] + 3*x[0];
    };
    auto df = [](std::vector<double> x)-> std::vector<double>{
        return {x[1] + 16*x[0]*x[0]*x[0] + 3, x[0] + 2*x[1]};
    };

    std::ifstream file("data.json");
    json data = json::parse(file);

    const unsigned int max_it = data.value("max_it",100);
    const double tol_step = data.value("tol_step",1e-6);
    const double tol_res = data.value("tol_res",1e-6);
    const double sigma = data.value("sigma",0.25);
    const double alpha_init = data.value("alpha_init",1);

    std::vector<double> init_guess = data["init_guess"].get<std::vector<double>>();

    gradientMethod method = gradientMethod(f,
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

