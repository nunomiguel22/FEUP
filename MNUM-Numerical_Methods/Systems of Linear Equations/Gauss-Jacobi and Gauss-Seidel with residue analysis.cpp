#include <iostream>
#include <math.h>

#define iterations 4


using namespace std;

int main() {

	cout.setf(ios::fixed);
	cout.precision(4);

	/*
		7x + 2y      = 24
		4x + 10y + z = 27
		5x - 2y + 8z = 27
	*/

	/*
		Initial values
	*/
	double x = 0, y = 0, z = 0;

	/*
	Gauss-Jacobi's method
	*/
	cout << "Gaus-Jacobi Result:" << endl;
	cout << iterations << " iterations" << endl;
	for (int i = 0; i < iterations; i++) {
		double xn = x, yn = y, zn = z;
		x = (24 - 2 * yn) / 7;
		y = (27 - 4 * xn - zn) / 10;
		z = (27 - 5 * xn + 2 * yn) / 8;
		cout << endl << "Iteration " << i + 1 << ":" << endl;
		cout << "Result:" << endl << "x" << i << ":" << x << "    y" << i << ":" << y << "    z" << i << ":" << z << endl;
		cout << "Residue:" << endl << "x" << i << ":" << fabs(24 - 7 * x - 2 * y)
			<< "    y" << i << ":" << fabs(27 - 10 * y - 4 * x - z)
			<< "    z" << i << ":" << fabs(27 - 8 * z - 5 * x + 2 * z) << endl;

	}
	x = 0, y = 0, z = 0;
	

	/*
	Gauss-Seidels's method
	*/
	cout << endl << endl << endl << "Gaus-Seidel Result:" << endl;
	cout << iterations << " iterations" << endl;
	for (int i = 0; i < iterations; i++) {
		x = (24 - 2 * y) / 7;
		y = (27 - 4 * x - z) / 10;
		z = (27 - 5 * x + 2 * y) / 8;
		cout << endl << "Iteration " << i + 1 << ":" << endl;
		cout << "Result:" << endl << "x" << i << ":" << x << "    y" << i << ":" << y << "    z" << i << ":" << z << endl;
		cout << "Residue:" << endl << "x" << i << ":" << fabs(24 - 7 * x - 2 * y)
			<< "    y" << i << ":" << fabs(27 - 10 * y - 4 * x - z)
			<< "    z" << i << ":" << fabs(27 - 8 * z - 5 * x + 2 * z) << endl;
	}

	cout << endl;
	return 0;
}