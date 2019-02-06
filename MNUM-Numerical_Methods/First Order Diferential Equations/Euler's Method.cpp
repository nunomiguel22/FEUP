#include <iostream>
#include <math.h>

using namespace std;


double f(double x, double y) {
	return x - 2;
}


double euler(double x, double x0, double y0, double h) {

	double xn = x0 + h, yn = y0 + f(x0, y0)* h;

	while (!(x <= xn && x >= x0)) {
		x0 = xn;
		y0 = yn;

		xn += h;
		yn = y0 + f(x0, y0)*h;
	}

	return y0 + f(x0, y0) * (x - x0);
}

int main() {


	double h = 0.5;
	double x0 = 0, y0 = 3;
	double i = 0;
	double S, SL, SLL;

	while (i <= 5) {
		

		S = euler(i, x0, y0, h);
		SL = euler(i, x0, y0, h/2);
		SLL = euler(i, x0, y0, h / 4);

		cout << "x:" << i << endl;
		cout << "S:" << S << " SL:" << SL << " SLL:" << SLL << endl;
		cout << "Divergence coeffiecent:" << ((SL - S) / (SLL - SL)) << endl;
		cout << "Error:" << (SLL - SL) << endl << endl;

		i += 0.5;

	}


	return 0;

}