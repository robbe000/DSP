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

int main(int argc, char *argv[])
{
	double *x1, *x2, *wave;
	int i;
	int xlen = 8;

	//geheugen alloceren
	x1 = (double*)calloc(xlen, sizeof(double));
	x2 = (double*)calloc(xlen, sizeof(double));
	wave = (double*)calloc(xlen, sizeof(double));
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

	//geheugen vrijgeven
	free(x1);
	free(x2);
	free(wave);
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