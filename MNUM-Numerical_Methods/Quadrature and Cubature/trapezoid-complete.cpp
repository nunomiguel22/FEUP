/*
*Trapezoid rule
*Result, error estimation and rate of convergence
*/
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

/*
* F(x)
*/

double f(double x) {
	return sin(x);
}

/*
* Fourth derivative of F(x)
*/

double fdd(double x) {
	return -sin(x);
}

/*
*Trapezoid rule
*/

double trapezoid(double ll, double ul, int n) {

	double h, res = 0;
	h = ((ul - ll) / n);
	

	for (int i = 1; i < n; i++) {
		res += 2 * f(ll + i * h);
	}

	res += f(ll) + f(ul);
	return res *= (h / 2);
}

/*
*Error Estimation
*/

double error(double ll, double ul, int n) {

	double teste = 0;
	double maxFdd = 0;
	double h = ((ul - ll) / n);
	
	
	for (int i = 1; i < n; i++) {
		if (fabs(fdd(ll + i * h )) > maxFdd)
			maxFdd = fabs(fdd(ll + i * h));
	}

	return ((pow((ul - ll), 3) / (12 * pow(n, 2))) * maxFdd);
}


int main() {
	//Limits
	double ll = 0, ul = M_PI;

	double h, res, s, sl, sll, errcalc, errobs;

	//number of iterations
	int n = 20;

	std::cout.precision(6);
	std::cout.setf(std::ios::fixed);

	std::cout << std::endl << "Trapezoid rule: " << std::endl << std::endl;

	res = trapezoid(ll, ul, n);

	std::cout << "Result  =  " << res << std::endl;

	//Observed and Calculated errors, Errobs = real result(2 in this case) - estimated result

	errcalc = error(ll, ul, n);

	errobs = 2 - res;

	//Values for rate of convergence
	
	s = trapezoid(ll, ul, n);
	sl = trapezoid(ll, ul, n * 2);
	sll = trapezoid(ll, ul, n * 4);
	

	std::cout << "Err.Calc  =  " << errcalc << std::endl << "Err.Obs  =  " << errobs << std::endl;
	std::cout << "Rate of convergence  =  " << ((sl - s) / (sll - sl)) << std::endl;
	std::cout << "Err''  =  " << (sll - sl)/3 << std::endl << std::endl;

	return 0;
}