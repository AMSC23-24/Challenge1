#include "gradientMethod.hpp"
#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>

double gradientMethod::minimize() const{

    int k = 1;     //initialize current number of iterations 

    //initialize current and next iteration

    std::vector<double> x = params.init_guess;
    std::vector<double> x_next = x;

    auto norm = [](std::vector<double> v){ //define norm function
        return std::sqrt(std::inner_product(v.begin(),v.end(),v.begin(),0.));
    };

    bool method_conv = false; //initialize convergence bool

    while(k <= params.max_it){

        //save f(xk) and df(xk)

        double fx = params.fun(x);
        std::vector<double> dfx = params.dfun(x);

        //initialize alpha

        double alpha = params.alpha_init;

        bool alpha_reach = false;

        while(!alpha_reach){ //armijo rule
            std::vector <double> sum; //temporary vector to check armijo rule

            for(int i = 0; i<x.size(); ++i){
                sum.push_back(x[i] - alpha*dfx[i]);
            }

            double norm_dfx = norm(dfx); //temp to store norm (prevents using pow)

            if(fx - params.fun(sum) >= params.sigma * alpha * norm_dfx * norm_dfx){ //evaluate condition
                alpha_reach = true;
            }
            else{
                alpha = alpha / 2;
            }
        }

        //with the current alpha, compute the next iteration

        for(size_t i = 0; i<x.size();++i){
            x_next[i] = x[i] - alpha * dfx[i];
        }

        //evaluate convergence conditions

        std::vector<double> diff = {};

        for(auto i = 0; i<x.size();++i){
            diff.push_back((x_next[i]-x[i])*(x_next[i]-x[i]));
        }

        if(k >= params.max_it || 
           norm(params.dfun(x_next)) < params.tol_res ||
           norm(diff) < params.tol_step){
            method_conv = true;

            //printing information about the result

            double minimum = params.fun(x_next);

            std::cout << "minimum: " << minimum << "\n\n"; 

            std::cout << "minimum point:\n\n";

            for(const auto & i : x_next){
                std::cout << i << "\n";
            }
            std::cout << " \n";
            std::cout << "number of iterations: " << k << std::endl;


            return minimum;
        }

        //advance to the next step

        x.swap(x_next);
        ++k;
    }
}