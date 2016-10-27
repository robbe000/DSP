#ifndef _dsp_h
#define _dsp_h

void CONVOLUTIE_1D(double *x, double *h, int xlen, int hlen, double *result);
void berekenK(int *kmin, int *kmax, int n, int xlen, int hlen);
void printArray(double * array, int len);

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

#endif // _dsp_h

