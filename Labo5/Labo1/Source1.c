#define _USE_MATH_DEFINES

//includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//defines
#ifdef M_PI
#define pi M_PI
#else
#define pi 4*atan(1.0)
#endif

//functies declareren 
void GENERATE_SINEWAVE(double A, double f, double fs, double phi, int n, double *result);
void ADDWAVES(double *x1, double *x2, int xlen, double *result);
void DFT(double *input, int N, double *X_Phase, double *X_Mag, double *X_Re, double *X_Im);

int main(int argc, char *argv[])
{
	double *x1, *x2, *wave, *X_Phase, *X_Mag, *X_Re, *X_Im;
	int i;
	int xlen = 8;

	//geheugen alloceren
	x1 = (double*)calloc(xlen, sizeof(double));
	x2 = (double*)calloc(xlen, sizeof(double));
	wave = (double*)calloc(xlen, sizeof(double));
	X_Phase = (double*)calloc(xlen, sizeof(double));
	X_Mag = (double*)calloc(xlen, sizeof(double));
	X_Re = (double*)calloc(xlen, sizeof(double));
	X_Im = (double*)calloc(xlen, sizeof(double));
	//functie oproepen
	GENERATE_SINEWAVE(1, 1000, 8000, 0, xlen, x1);
	GENERATE_SINEWAVE(0.5, 2000, 8000, (3*pi)/4,xlen, x2);
	ADDWAVES(x1, x2, xlen, wave);
	//afdrukken
	printf("\nX1:\n");
	for (i = 0; i < xlen; i++)
	{
		printf("%lf\n", x1[i]);
	}
	printf("\nX2:\n");
	for (i = 0; i < xlen; i++)
	{
		printf("%lf\n", x2[i]);
	}
	printf("\nWave:\n");
	for (i = 0; i < xlen; i++)
	{
		printf("%lf\n", wave[i]);
	}
	DFT(wave, 8, X_Phase, X_Mag, X_Re, X_Im);

	//geheugen vrijgeven
	free(x1);
	free(x2);
	free(wave);
	free(X_Mag);
	free(X_Phase);
	free(X_Re);
	free(X_Im);
}

void DFT(double *input, int N, double *X_Phase, double *X_Mag, double *X_Re, double *X_Im)
{
	int m, n;
	for (m = 0; m < N; m++)
	{
		for (n = 0; n < N; n++)
		{
			X_Re[m] += input[n] * (cos((2 * pi * m * n) / N));
			X_Im[m] += -(input[n] * (sin((2 * pi * m * n) / N)));
		}
		printf("%.25lf\t%.25lf\t\t", X_Re[m], X_Im[m]);
		X_Phase[m] = atan2(X_Im[m], X_Re[m]);
		X_Mag[m] = sqrt((X_Re[m] * X_Re[m]) + (X_Im[m] * X_Im[m]));
		if (X_Mag[m] < 0.001)
		{
			X_Phase[m] = 0;
		}
		X_Phase[m] = X_Phase[m] * 180 / pi;
		printf("%lf\t%lf\n", X_Mag[m], X_Phase[m]);
	}
}

void GENERATE_SINEWAVE(double A, double f, double fs, double phi, int n, double *result)
{
	int i;

	for (i = 0; i < n; i++)
	{
		//komt van: A sin (2 * pi * f * t * phi);
		result[i] = A * sin(2 * pi * f / fs * i + phi);
	}
}

void ADDWAVES(double *x1, double *x2, int n, double *result)
{
	int i;

	for (i = 0; i < n; i++)
	{
		result[i] = x1[i] + x2[i];
	}
}