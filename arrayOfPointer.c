#include <stdio.h>
#include <malloc.h>

int** dividingAnArrayIntoParts(int* inputArray, const int* lenght, int* resultLenght)
{
	if (*lenght == 1)
		return NULL;


	*resultLenght = 1;
	int** result = (int**)malloc(sizeof(int*) * *resultLenght);
	int maxLenghtResult = 1;

	int currentLenght = 1;
	int LenghtNIV = 1;
	int startIndex;
	int* nonIncreasingValues = (int*)malloc(sizeof(int) * LenghtNIV);
	int maxLenghtNIR = 1;

	for (int i = 0; i < *lenght - 1; i++)
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
				if ((LenghtNIV + 1) >= maxLenghtNIR)
				{
					maxLenghtNIR = 2 * LenghtNIV;
					nonIncreasingValues = (int*)realloc(nonIncreasingValues, sizeof(int) * maxLenghtNIR);
				}
				nonIncreasingValues[LenghtNIV - 1] = inputArray[i];
			}
			else
			{
				if ((*resultLenght + 1) >= maxLenghtResult)
				{
					maxLenghtResult = 2 * *resultLenght;
					result = (int**)realloc(result, sizeof(int*) * maxLenghtResult);
				}

				result[*resultLenght - 1] = (int*)malloc(sizeof(int) * (currentLenght + 1));

				result[*resultLenght - 1][0] = currentLenght;
				for (int j = 0; j < currentLenght; j++)
					result[*resultLenght - 1][j + 1] = inputArray[startIndex + j];

				currentLenght = 1;
				(*resultLenght)++;
			}
		}
	}
	if (currentLenght == 1)
	{
		nonIncreasingValues[0] = LenghtNIV++;
		if ((LenghtNIV + 1) >= maxLenghtNIR)
		{
			maxLenghtNIR = 2 * LenghtNIV;
			nonIncreasingValues = (int*)realloc(nonIncreasingValues, sizeof(int) * maxLenghtNIR);
		}
		nonIncreasingValues[LenghtNIV - 1] = inputArray[*lenght - 1];
	}
	else
	{
		if ((*resultLenght + 1) >= maxLenghtResult)
		{
			maxLenghtResult = 2 * *resultLenght;
			result = (int**)realloc(result, sizeof(int*) * maxLenghtResult);
		}

		result[*resultLenght - 1] = (int*)malloc(sizeof(int) * (currentLenght + 1));

		result[*resultLenght - 1][0] = currentLenght;
		for (int j = 0; j < currentLenght; j++)
			result[*resultLenght - 1][j + 1] = inputArray[startIndex + j];

		currentLenght = 1;
		(*resultLenght)++;
	}
	result[*resultLenght - 1] = nonIncreasingValues;

	return result;
}

int main() 
{
	fprintf(stdout, "Please enter a sequence of integers separated by a space. Enter -1 at the end of the sequence!\n");
	
	int* inputArray = (int*)malloc(sizeof(int));
	int lenght = 0;

	for (int tmp; 1; lenght++)
	{
		fscanf_s(stdin, "%d", &tmp);
		if (tmp == -1)
			break;
		inputArray = (int*)realloc(inputArray, sizeof(int) * (lenght + 1));
		inputArray[lenght] = tmp;
	}

	//input data: 1 2 3 5 4 6 7 2 1 2 3 -1
	int resultLenght;
	int** result = dividingAnArrayIntoParts(inputArray, &lenght, &resultLenght);

	fprintf(stdout, "Result: \n");
	for (int i = 0; i < resultLenght; i++)
	{
		for (int j = 1; j < result[i][0] + 1; j++)
		{
			fprintf(stdout, "%d ", result[i][j]);
		}
		fprintf(stdout, "\n");
	}
}