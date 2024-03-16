#include "gradientMethod.hpp"

int main(){
    auto f = [](std::vector<double> x ){
        return x[0]*x[1] + 4*x[0]*x[0]*x[0]*x[0] + x[1]*x[1] + 3*x[0];
    };
    auto df = [](std::vector<double> x)-> std::vector<double>{
        return {x[1] + 16*x[0]*x[0]*x[0] + 3, x[0] + 2*x[1]};
    };

    gradientMethod method = gradientMethod(f,df,{0.,0.},100,1e-6,1e-6);

    //gradientMethod method = gradientMethod(f,df,{0.,0.},100,1e-6,1e-6,0.25,1);

   double sol = method.minimize();

}

