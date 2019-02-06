#include <iostream>
#include <math.h>

#define N 3

using namespace std;

void print_matrix(double matrix[N][N + 1]) {
	
	for (int i = 0; i < N; i++) {
		cout << "{ ";
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j];
			if (j != N - 1)
				cout << ", ";
		}
		cout << " }";
		cout << " { " << matrix[i][N] << " } " << endl;
	}

}

void gauss_row_op(double matrix[N][N + 1], int L1, double cof, int L2) {
	/*
		L1 = L1 - x * L2
	*/
	for (int i = 0; i < N + 1; i++) {
		matrix[L1][i] -= cof * matrix[L2][i];
	}
}

void gauss_row_swap(double matrix[N][N + 1], int L1, int L2) {
	/*
		Swap matrix rows
	*/
	for (int i = 0; i < N + 1; i++) {
		double temp = matrix[L1][i];
		matrix[L1][i] = matrix[L2][i];
		matrix[L2][i] = temp;
	}
}

int gauss(double matrix[N][N + 1]) {

	for (int k = 0; k < N; k++) {

		int pivotrow = k;
		/* 
			Partial Pivoting (optional):
				Swaping rows if a bigger pivot is found in the column
		*/
		for (int i = k+1; i < N; i++) {
			if (abs(matrix[pivotrow][k]) < abs(matrix[i][k])) {
				pivotrow = i;
			}
		}
		if (pivotrow != k)
			gauss_row_swap(matrix, pivotrow, k);
		/*
			Check if any of the main diagonal elements are zero, stop program if true
		*/
		if (matrix[k][k] == 0) {
			cout << "Singular Matrix" << endl;
			return 1;
		}
		/*
			Make all main diagonal members equal 1 using gauss_row_op
				L1 - x * L1 = x = 1 - 1/L1
		*/
		gauss_row_op(matrix, k, (1 - 1 / matrix[k][k]), k);
		/*
			Make all values aboves and below the main diagonal equal 0 using gauss_row_op.
		*/
		for (int i = 0; i < N; i++) {
			if (i == k)
				continue;
			gauss_row_op(matrix, i, matrix[i][k], k);
		}
	}
	return 0;
}



int main() {
	/*
		Set cout precision
	*/
	cout.setf(ios::fixed);
	cout.precision(3);
	/* 
		Matrix[rows][columns] format: AX = B
			matrix is used to solve the system
			matrix2 is used to test external stability
			matrix3 is used to test internal stability
	*/
	double matrix[N][N + 1] = {
		{ 7, 8, 9, 24 },
		{ 8, 9, 10, 27 },
		{ 9, 10, 8, 27 }
	};
	double matrix2[N][N + 1] = {
		{ 7, 8, 9, 24 },
		{ 8, 9, 10, 27 },
		{ 9, 10, 8, 27 }
	};
	double matrix3[N][N + 1] = {
		{ 7, 8, 9, 24 },
		{ 8, 9, 10, 27 },
		{ 9, 10, 8, 27 }
	};
	/*
		Gauss method solution
	*/
	if (gauss(matrix))
		return 0;

	cout << endl << "Solution: " << endl;
	print_matrix(matrix);
	const double delta_A = 0.5, delta_b = 0.5;
	/*
		External stability
			B = Delta_b - delta_A * x
			Solve using gauss's method
	*/
	for (int l = 0; l < N; l++) {
		matrix2[l][N] = delta_b - N*delta_A;
	}

	cout << endl << "External stability: " << endl;
	gauss(matrix2);
	print_matrix(matrix2);
	/*
		Internal stability
			B = A + B - x0;
			Solve using gauss's method
	*/
	int x0 = 1;
	int AX0[N] = { 0, 0, 0 };

	for (int l = 0; l < N; l++) {
		for (int c = 0; c < N; c++) {
			AX0[l] += matrix3[l][c] * x0;
		}
	}
	for (int l = 0; l < N; l++) {
		matrix3[l][N] = matrix3[l][N] - AX0[l];
	}

	cout << endl <<"Internal stability: " << endl;
	gauss(matrix3);
	print_matrix(matrix3);


	return 0;
}