#include <stdio.h>
#include <malloc.h>

int** dividingAnArrayIntoParts(int* inputArray)
{
	if ((sizeof(inputArray) / sizeof(int)) == 1)
		return NULL;

	int resultLenght = 1;
	int** result = (int**)malloc(sizeof(int*) * resultLenght);

	int currentLenght = 1;
	int LenghtNIV = 1;
	int startIndex;
	int* nonIncreasingValues = (int*)malloc(sizeof(int) * LenghtNIV);

	for (int i = 0; i < sizeof(inputArray) / sizeof(int) - 1; i++)
	{
		if (inputArray[i] < inputArray[i + 1])
		{
			if (currentLenght == 1)
				startIndex = i;
			currentLenght++;
		}
		else
		{
			if (currentLenght == 1)
			{
				nonIncreasingValues[0] = LenghtNIV++;
				if ((LenghtNIV + 1) == (sizeof(nonIncreasingValues) / sizeof(int)))
					nonIncreasingValues = (int*)realloc(nonIncreasingValues, sizeof(int) * 2 * LenghtNIV);
				nonIncreasingValues[LenghtNIV] = inputArray[i];
			}
			else
			{
				if ((resultLenght + 1) == (sizeof(result) / sizeof(int*)))
					result = (int**)realloc(result, sizeof(int*) * 2 * resultLenght);

				result[resultLenght - 1] = (int*)malloc(sizeof(int) * (currentLenght + 1));

				result[resultLenght - 1][0] = currentLenght;
				for (int j = 0; j < currentLenght; j++)
					result[resultLenght - 1][j + 1] = inputArray[startIndex + j];

				currentLenght = 1;
				resultLenght++;
			}
		}
		result[resultLenght] = nonIncreasingValues;
		currentLenght = 0;
	}

	return result;
}

int main() 
{
	fprintf(stdout, "Please enter a sequence of integers separated by a space: \n");
	
	int* inputArray = NULL;
	for (int i = 0; fscanf_s(stdin, "%d", inputArray[i]) != 0; i++)
		inputArray = (int*)realloc(inputArray, sizeof(int) * (i + 1));
	inputArray[0]++;
}