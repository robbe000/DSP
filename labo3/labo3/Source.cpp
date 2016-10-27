#define aantalKolommen(a) sizeof(a[0])
#define aantalRijen(a) sizeof(a)/sizeof(a[0])
#include <stdio.h>

void CONVOLUTION_2D(double input[6][7], double kernel[3][3], int kernel_size, int rows, int cols, double *output);

int main(int argc, char *argv)
{
	//opvullen van het masker
	double kernel[3][3] = { {1, 2, 1},	
							{0, 0, 0},
							{-1, -2, -1} };
	//opvullen dan de input
	double input[6][7] = {	{ 0, 0, 0, 0, 0 },
							{ 0, 1, 2, 3, 0 },
							{ 0, 4, 5, 6, 0 },
							{ 0, 7, 8, 9, 0 }, 
							{ 0, 0, 0, 0, 0 }, };
	double output[7][7];
	CONVOLUTION_2D(input, kernel, 3, 5, 6, *output);

	return 0;
}

void CONVOLUTION_2D(double input[6][7], double kernel[3][3], int kernel_size, int rows, int cols, double *output)
{
	int width, height;					//Om aantal verplaatsingen van de kernel te bepalen
	int kernelWidth, kernelHeight;		//Om convolutie van één kernel groot te berekenen
	double uitgang[7][7];
	double kernelElement;
	double inputElement;
	double rekenElement;
	double somElement;

	//van boven naar beneden, van links naar rechts
	for (width = 0; width < rows - (kernel_size/2)-1; width++)
	{
		for (height = 0; height < cols - (kernel_size / 2)-1; height++)
		{
			//Hier convolutie uitvoren van één kernel groot
			somElement = 0;
			for (kernelWidth = 0; kernelWidth < kernel_size; kernelWidth++)
			{
				for (kernelHeight = 0; kernelHeight < kernel_size; kernelHeight++)
				{
					kernelElement = kernel[kernelWidth][kernelHeight];
					inputElement = input[width + kernelWidth][height + kernelHeight];
					rekenElement = kernelElement * inputElement;
					somElement = somElement + rekenElement;
				}
			}
			printf("%lf\t", somElement);
		}
		printf("\n");
	}
}