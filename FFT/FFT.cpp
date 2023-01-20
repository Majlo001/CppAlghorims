#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <complex>


std::complex<double>* fft(double* f, int N) {
	std::complex<double>* c = new std::complex<double>[N];

	if (N == 1) {
		c[0].real(f[0]);
		c[0].imag(0.0);
		return c;
	}

	int newN = N / 2;
	double* even = new double[newN];
	double* odd = new double[newN];
	std::complex<double>* Ecomplex;
	std::complex<double>* Ocomplex;

	for (int i = 0; i < N; i = i + 2) {
		even[i/2] = f[i];
		odd[i/2] = f[i+1];
	}

	Ecomplex = fft(even, newN);
	Ocomplex = fft(odd, newN);

	for (int k = 0; k < newN-1; k++) {
		c[k] = Ecomplex[k] + std::polar(1.0, -2 * M_PI * k/N) * Ocomplex[k];
		c[k+newN] = ;
	}

	delete[] Ecomplex;
	delete[] Ocomplex;
	delete[] even;
	delete[] odd;
	return c;
}

std::complex<double>* dft(double* f, int N) {

}



int main() {
	//const int MAX_ORDER = 13;
	const int MAX_ORDER = 2;
	const bool PRINT_COEFS = false;
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int N = 1 << o; // rozmiar problemu ( potega dwojki - przesuniecie bitowe w lewo )
		printf("N: %i \n", N);

		double* f = new double[N];
		for (int n = 0; n < N; n++)
			f[n] = n / (double)N; // przykladowe dane ( tu akurat : probki funkcji liniowej )

		clock_t t1 = clock();
		//std::complex<double>* cDFT = dft(f, N);
		clock_t t2 = clock();
		double dft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;


		//printf("DFT time[ms] : % f \n", dft_time);
		t1 = clock();
		std::complex<double>* cFFT = fft(f, N);
		t2 = clock();
		double fft_time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000.0;


		//printf("FFT time[ms] : % f \n", fft_time);
		//printf("mean error : % f \n", err(cDFT, cFFT, N));
		//if (PRINT_COEFS)
		//	for (int k = 0; k < N; k++)
		//		... // wypis na ekran wspolczynnikow obu transformat ( czesci rzeczywiste i urojone )
		//		printf("−−−−−\n", N);
		delete[] f;
		//delete[] cDFT;
		delete[] cFFT;
	}
}