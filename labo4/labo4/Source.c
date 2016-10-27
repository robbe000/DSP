//marcro lengte van array berekenen
#define size(a) sizeof(a)/sizeof(a[0])

#include <stdio.h>

//functies declareren
void BLOCKCONV(double *x, double *h, int xlen, int hlen, double *result, int lengteblock);
void CONVOLUTIE_1D(double *x, double *h, int xlen, int hlen, double *result);
void berekenK(int *kmin, int *kmax, int n, int xlen, int hlen);
void printArray(double * array, int len);

int main(int argc, char *argv[])
{
	//intput waarden genereren
	double x[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	double h[3] = { 1,2,3 };

	//lengte array's bepalen
	int xlen = size(x);
	int hlen = size(h);

	//geheugen alloceren voor output: L = P + Q - 1 (L = xlen + hlen - 1)
	int L = xlen + hlen - 1;
	double *resultaat = (double*)calloc(L, sizeof(double));

	BLOCKCONV(x, h, xlen, hlen, resultaat, 3);

	return 0;
}

void BLOCKCONV(double *x, double *h, int xlen, int hlen, double *result, int lengteblock)
{
	//Blokken bereken
	int aantal = xlen / lengteblock;
	int i;
	for (i = 0; i < aantal; i++)
	{
		//nog berekenen of xlen op einde klopt!!!
		CONVOLUTIE_1D(x, h, lengteblock, hlen, resultaat);

	}
}

void CONVOLUTIE_1D(double *x, double *h, int xlen, int hlen, double *result)
{
	int kmin, kmax;
	for (int n = 0; n < (xlen + hlen - 1); n++)
	{
		berekenK(&kmin, &kmax, n, xlen, hlen);
		for (int k = kmin; k <= kmax; k++)
		{
			result[n] = result[n] + (x[k] * h[n - k]);
		}
	}
}

void berekenK(int *kmin, int *kmax, int n, int xlen, int hlen)
{
	int max = xlen + hlen - 1;
	if (n > hlen - 1)
	{
		*kmin = n - (hlen - 1);
	}
	else
	{
		*kmin = 0;
	}

	if (n > xlen - 1)
	{
		*kmax = xlen - 1;
	}
	else
	{
		*kmax = n;
	}
}

void printArray(double * array, int len)
{
	printf("Array:\n");
	for (int i = 0; i < len; i++)
	{
		printf("%lf\n", array[i]);
	}
}