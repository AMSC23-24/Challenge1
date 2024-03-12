#include <vector>
#include <functional>
#include <cmath>
#include <numeric>

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

        auto norm = [](std::function<std::vector<double>(std::vector<double>)> f, std::vector<double> x){
            return std::sqrt(std::inner_product(f(x).begin(),f(x).end(),f(x).begin(),0.));
        };

        //initial guess for alpha

        alpha = 1;

        while(!reach){
            std::vector <double> sum;

            for(int i = 0; i<xk.size(); ++i){
                sum.push_back(xk[i] - alpha*nabla_f(xk)[i]);
            }
            if(f(xk) - f(sum) >= sigma * alpha * norm(nabla_f,xk)){
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

        std::vector<double> diff;

        for(auto i = 0; i<xk.size();++i){
            diff.push_back(pow(xk_next[i]-xk[i],2));
        }

        if(k > k_max || abs(f(xk_next) - f(xk)) < eps_r || std::sqrt(std::accumulate(diff.begin(),diff.end(),0.)) < eps_s){
            conv = true;
        }
    }

    return xk;
}


int main(){

}