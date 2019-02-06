/*
*Newton and picard-peano's Methods
*
*/

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iomanip>

/*
* F(x)
*/

double f(double x) {
	return (pow(x,2)- x-0.2);
}

/*
* First derivative of F(x)
*/

double fd(double x) {
	return (2*x-1);
}

/*
* Newton's method
*/

double newton(double x) {

	std::cout << std::endl << "Newton's Method: " << std::endl << std::endl;

	int maxIter = 10;
	double err = 0.0005;

	std::cout << "N" << std::setw(12) << "x" << std::setw(12) << "f(x)" << std::setw(12) << "fd(x)" << std::setw(12) <<"New x" << std::endl;

	for (int i=0; i < maxIter; i++) {

		std::cout << i << std::setw(12) << x << std::setw(12) << f(x) << std::setw(12) << fd(x);

		double lastVal = x;
		x = x - (f(x) / fd(x));

		std::cout << std::setw(12) << x << std::endl;

		if (fabs((x - lastVal)) < err)
			break;
	}

	std::cout << std::endl << std::endl;
	std::cout << "Final result = " << x << std::endl << std::endl;

	return x;
}

/*
* Picard-Peano method
*/

double picard(double iv, double err) {

	std::cout << std::endl << "Picard-Peano Method: " << std::endl << std::endl;

	double x, prevx = iv;

	int maxIter = 5;

	std::cout << "N" << std::setw(8) << "x" << std::setw(16) << "New x" << std::endl;

	for (int i = 0; i < maxIter; i++){

		

		x = f(prevx);
		
		if (fabs(x - prevx) < err) {
			break;
		}

		std::cout << i << std::setw(12) << prevx << std::setw(12) << x << std::endl;

		prevx = x;
	}

	std::cout << std::endl << std::endl;
	std::cout << "Final Value = " << x << std::endl << std::endl;
	return x;
}

int main() {

	std::cout.precision(6);
	std::cout.setf(std::ios::fixed);

	newton(1);
	picard(0.1, 0.01);

	return 0;
}