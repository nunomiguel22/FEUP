/*
*Simpson's rule
*Result, error estimation and rate of convergence
*/

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

double pi = M_PI;

/*
*F(x)
*/

double f(double x) {
	return sin(x);
}

/*
*Fourth Derivative of F(x)
*/

double fdddd(double x) {
	return -cos(x);
}

/*
*Simpson's method
*/

double simpson(double ll, double ul, int n) {

	double res = f(ll) + f(ul);
	double h = (ul - ll) / n;

	for (int i = 1; i < n; i++) {
		if (i % 2 != 0)
			res += 4 * f(ll +i*h);
		else res += 2 * f(ll + i * h);
	}

	return res *= (h / 3);

}

/*
*Error estimation
*/

double error(double ll, double ul, int n) {

	double maxFdd = 0;
	double h = ((ul - ll) / n);


	for (int i = 1; i < n; i++) {
		if (fabs(fdddd(ll + i * h)) > maxFdd)
			maxFdd = fabs(fdddd(ll + i * h));
	}

	return ((pow((ul - ll), 5) / (90 * pow(n, 4))) * maxFdd);
}



int main() {

	//Limits
	double ll = 0, ul = M_PI;

	double h, res, s, sl, sll, errcalc, errobs;
	
	//Number of iterations
	int n = 20;

	std::cout << std::endl << "Simpson's rule: " << std::endl << std::endl;

	std::cout.precision(6);
	std::cout.setf(std::ios::fixed);


	res = simpson(ll, ul, n);

	std::cout << "Result  =  " << res << std::endl;

	//Observed and Calculated errors, Errobs = real result(2 in this case) - estimated result

	errcalc = error(ll, ul, n);

	errobs = fabs(2 - res);
	
	//Values for rate of convergence

	s = simpson(ll, ul, n);
	sl = simpson(ll, ul, n * 2);
	sll = simpson(ll, ul, n * 4);

	std::cout << "Err.Calc  =  " << errcalc << std::endl << "Err.Obs = " << errobs << std::endl; 
	std::cout << "Rate of convergence  =  " << ((sl - s) / (sll - sl)) << std::endl;
	std::cout << "Err''  =  " << fabs((sll - sl) / 15) << std::endl << std::endl;


	return 0;
}