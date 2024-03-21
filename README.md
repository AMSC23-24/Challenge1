# Gradient Descent Method for function minimization

This repository contains an implementation of the search of the minimum of a function through the gradient descent method, which from an initial guess $x_0$ searches for the minimum point with the following rule:

$$
\begin{align}
\nonumber
x_{k+1} = x_{k} − \alpha_k \nabla f(x_k) \quad k = 0,...,k_{max}
\end{align}
$$

for any $f : \mathbb{R}^n \rightarrow \mathbb{R}$


## Contents

`gradientMethod.cpp` contains the class that implements the gradient method, where $a_k$ is set to satisfy the Armijo Rule:

$$
\begin{align}
\nonumber
f(x_k - \alpha_k \nabla f(x_k)) - f(x_k) \leq \sigma \alpha_k \nabla(f(x_k))^T \cdot (-\nabla(f(x_k)))
\end{align}
$$

`data.json` contains the parameters for the gradientMethod class, namely:
- The maximum number of iterations $k_{max}$
- The tolerances for the residual and the step length, $\epsilon_r$ and $\epsilon_s$ respectively
- The initial guess
- $\sigma$ and $\alpha_0$ for the Armijo rule
- The function to be minimized


`main.cpp` parses the `data.json` file, creates a gradientMethod object and finds the function minimum

## Issues

The gradient of the function to be minimized has to be defined in the source code.

## Compilation instructions

```bash 
make src/makefile 
``` 
Generates a main file inside the `src` directory to be ran
