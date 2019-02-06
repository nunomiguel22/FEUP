/*
*Bisection and False Position Methods
*
*/

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iomanip>

/*
*  F(x) you want to find the root of
*/

double f(double x) {
	return (3*x + sin(x) - exp(x));
}

/*
* Bisection Method
*/

double bisec(double ll, double ul) {

	std::cout << "	Bisection Method" << std::endl << std::endl;
	//iteration counter
	int cnt = 0; 
	//The lower err is more iterations wil be done but the result will also be more precise
	double err = 0.001; 

	double c = ll;

	std::cout << "N" << std::setw(16) << "Lower limit" << std::setw(16) << "Upper limit" << std::endl;

	while ((ul - ll) >= err) {

		c = (ul + ll) / 2;
		if (f(c) * f(ll) < 0)
			ul = c;
		else ll = c;		
		cnt++;
		std::cout << cnt << std::setw(15) << ll << std::setw(16) << ul << std::endl;
	}
	
	std::cout << std::endl << "Final Result = " << c << std::endl << std::endl;
	return c;
}

/*
*False Position Method
*/

double falsePosition(double ll, double ul) {

	std::cout << "	False Position Method" << std::endl << std::endl;
	
	double c = 0;
	double lastValue;
	double err = 0.001;
	//n is the maximum number of iterations the loop will do while the program hasn't met the error criteria
	double n = 50;

	std::cout << "N" << std::setw(16) << "Lower limit" << std::setw(16) << "Upper limit" << std::endl;

	for (int i = 1; i < n; i++) {
		lastValue = c;
		c = (ll * f(ul) - ul * f(ll))  / (f(ul) - f(ll));
	
		if ((f(ll) * f(c)) < 0)
			ul = c;
		else ll = c;
		
		std::cout << i << std::setw(15) << ll << std::setw(16) << ul << std::endl;
		
		if (fabs(c - lastValue) < err)
			break;
	}

	std::cout << std::endl << "Final Result = " << c << std::endl << std::endl;
	return c;

}


int main() {

	std::cout.precision(7);
	std::cout.setf(std::ios::fixed);

	bisec(0, 1);
	falsePosition(0, 1);
	
	return 0;
}