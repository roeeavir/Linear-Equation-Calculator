/*
 * genecral.c
 *
 *  Created on: Dec 13, 2019
 *      Author: roee
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "general.h"

#define TRUE 1
#define FALSE 0

//Function for setting a valid number of equations.
int eqSize() {
	int size, isOk = FALSE;
	printf("Please enter the number of equations(1-3):\n");
	while (!isOk) {
		scanf("%d", &size);
		if (size < 1 || size > 3)
			printf(
					"Invalid equation size!\nPlease enter a valid equation size(1-3):\n");
		else
			isOk = TRUE;
	}
	return size;
}

//Function for getting an equation from the user.
char* initStr(int index) {
	char *str;
	char temp[200]; //A set large char array to make room for the string.
	char clear;
	printf("Please enter equation number %d:\n", index);
	if(index == 1)
		scanf("%c", &clear);// Statement to clear buffer.
	fgets(temp, 200*sizeof(char), stdin);

	int len = strlen(temp);
	str = (char*) malloc((len + 1) * sizeof(char));

	if (!str)
		return NULL;

	str = strdup(temp);

	return str;

}



//Function that checks for a valid equation length while ignoring spaces.
int checkStr(char *str, int size) {
	int len = strlen(str);
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ')
			len--;
	}
	if (len > 80)
			{
		printf("Equation cannot be longer than 80 chars!\n");
		return FALSE;
	}
	return TRUE;
}

//Removes all the spaces of a string.
void removeSpaces(char* str)
{
	int j = 0;
	for(int i = 0; i < strlen(str) - 1; i++)
	{
		if(!isspace(str[i]))
			str[j++] = str[i];
	}
	str[j] = 0;
}

//Reads a string and sets it into a float.
float setFloat(char* str, int* index, float num, int posOrNeg)
{
	int afDecPnt = 10;//Decimal point of the float.
	int isDone = 0;

	while(!isDone)
	{
		if(isdigit(str[*index]))
		{
			num = num*10 + str[*index] - '0';
			*index = (*index) + 1;
		}
		else if(str[*index] == '.')
		{
			*index = (*index) + 1;
			while(isdigit(str[*index]))
			{
				num = num*afDecPnt + ((str[*index] - '0'));
				num = num/afDecPnt;
				afDecPnt *= 10;
				*index = (*index) + 1;
			}
		}
		else
		{
			isDone = 1;
			*index = (*index) - 1;
		}
	}


	return num*posOrNeg;
}

//Calculating determinant.
float getDet(float** mat, int size)
{
	float det = 0;
	if(size == 1)
		return mat[0][0];

	else if(size == 2)//A simple calculation of 2X2 determinant.
		return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

	else if(size == 3)
	{
		for(int i = 0; i < 3; i++)//A simple calculation of 3X3 determinant.
			det = det + mat[0][i] * ( mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3]*mat[2][(i+1)%3]);
		return det;
	}
	return 0;
}

//Setting a matrix for Cramer's rule and calculating it.
float cramMat(float** mat2, float** mat1, float* arr, int coef, int size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(j == coef)
				mat2[i][j] = arr[i];
			else
				mat2[i][j] = mat1[i][j];
		}
	}

	return getDet(mat2, size);
}

//Prints matrix A.
void printMat(float** mat, int size)
{
	printf("Matrix A = \n");
	for(int i = 0; i < size; i++)
	{
		printf("\t\t");
		for(int j = 0; j < size; j++)
		{
			printf("%5.3f\t", mat[i][j]);
		}
		printf("\n\n");
	}
}

//Prints vector B.
void printVecB(const float* arr, int size)
{
	printf("Vector B = \n\t\t");
	for(int i = 0; i < size; i++, arr++)
	{
		printf("%6.3f", *arr);
		printf("\n\t\t");
	}
	printf("\n\n");

}

//Prints solution (Vector X).
void printVecX(const float* arr, int size)
{
	char c = 'x';
	printf("Vector x = \n\t\t");
	for(int i = 0; i < size; i++, arr++)
	{
		printf("%c = %6.3f", c++, *arr);
		printf("\n\t\t");
	}
	printf("\n\n");

}

