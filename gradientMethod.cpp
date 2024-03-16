#include "gradientMethod.hpp"
#include <cmath>
#include <vector>
#include <numeric>

std::vector<double> gradientMethod::minimize() const{

    //initialize current number of iterations 

    int k = 1;

    //initialize current and next iteration

    std::vector<double> x = params.init_guess;
    std::vector<double> x_next = x;

    //define norm function

    auto norm = [](std::vector<double> v){
        return std::sqrt(std::inner_product(v.begin(),v.end(),v.begin(),0.));
    };

    //use armijo's rule
    
    bool conv = false;

    while(!conv){

        //save f(xk) and nabla_f(xk)

        double fx = params.fun(x);
        std::vector<double> dfx = params.dfun(x);

        //initialize alpha

        double alpha = params.alpha_init;

        bool reach = false;

        while(!reach){
            std::vector <double> sum;

            for(int i = 0; i<x.size(); ++i){
                sum.push_back(x[i] - alpha*dfx[i]);
            }

            if(fx - params.fun(sum) >= params.sigma * alpha * norm(dfx)){
                reach = true;
            }
            else{
                alpha = alpha / 2;
            }
        }

        //we have the alpha, let's compute the next iteration

        for(size_t i = 0; i<x.size();++i){
            x_next[i] = x[i] - alpha * dfx[i];
        }

        //check convergence

        std::vector<double> diff = {};

        for(auto i = 0; i<x.size();++i){
            diff.push_back(pow(x_next[i]-x[i],2));
        }

        if(k > params.max_it || norm(params.dfun(x_next)) < params.tol_res || std::sqrt(std::accumulate(diff.begin(),diff.end(),0.)) < params.tol_step){
            conv = true;
        }

        x.swap(x_next);
    }

    return x;
}