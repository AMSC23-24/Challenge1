#include <vector>
#include <functional>
#include <cmath>
#include <numeric>
#include <iostream>

std::vector<double> gradient(std::function<double(std::vector<double>)> f, std::function<std::vector<double>(std::vector<double>)> nabla_f);

void printvec(std::vector<double> v);

int main(){
    auto f = [](std::vector<double> x ){
        return x[0]*x[1] + 4*pow(x[0],4) + pow(x[1],2) + 3*x[0];
    };
    auto nabla_f = [](std::vector<double> x)-> std::vector<double>{
        return {x[1] + 16*pow(x[0],3) + 3, x[0] + 2*x[1]};
    };

    std::vector<double> result = gradient(f,nabla_f);

    for(auto i : result){
        std::cout << i << std::endl;
    }

}

std::vector<double> gradient(std::function<double(std::vector<double>)> f, std::function<std::vector<double>(std::vector<double>)> nabla_f){

    int k = 1;

    int k_max = 100;

    //initial guess
    std::vector<double> xk{0.,0.};
    std::vector<double> xk_next{0.,0.};

    //tolerances

    double eps_r = 1e-6;
    double eps_s = 1e-6;

    //use armijo's rule

    double sigma = 0.25;

    bool conv = false;

    while(!conv){

        bool reach = false;

        double alpha = 1.;

        auto norm = [](std::vector<double> v){
            return std::sqrt(std::inner_product(v.begin(),v.end(),v.begin(),0.));
        };

        //save f(xk) and nabla_f(xk)

        double fxk = f(xk);
        std::vector<double> diff_fxk = nabla_f(xk);

        //initial guess for alpha

        alpha = 1;

        while(!reach){
            std::vector <double> sum;

            for(int i = 0; i<xk.size(); ++i){
                sum.push_back(xk[i] - alpha*diff_fxk[i]);
            }

            printvec(sum);

            if(fxk - f(sum) >= sigma * alpha * norm(diff_fxk)){
                reach = true;
            }
            else{
                alpha = alpha / 2;
            }
        }

        //we have the alpha, let's compute the next iteration

        for(size_t i = 0; i<xk.size();++i){
            xk_next[i] = xk[i] - alpha * nabla_f(xk)[i];
        }

        //check convergence

        std::vector<double> diff = {};

        for(auto i = 0; i<xk.size();++i){
            diff.push_back(pow(xk_next[i]-xk[i],2));
        }

        if(k > k_max || abs(f(xk_next) - f(xk)) < eps_r || std::sqrt(std::accumulate(diff.begin(),diff.end(),0.)) < eps_s){
            conv = true;
        }
    }

    return xk;
}

void printvec(std::vector<double> v){
    for(auto elem : v){
        std::cout << elem << std::endl;
    }
}

