/*
 * equation.c
 *
 *  Created on: Dec 10, 2019
 *      Author: roee
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "general.h"
#include "equation.h"


//Creates and checks an equation.
int initEq(Equation* pEq, int index)
{
	char* str;
	int isOk;

	str = initStr(index+1);

	removeSpaces(str);

	isOk = checkStr(str, pEq->count);
	if(!isOk)
	{
		printf("Bad input!\n");
		return 0;
	}

	else
	{

		if(!setEq(pEq, str))
		{
			free(str);
			return 0;
		}

		free(str);

		return 1;
	}

}

//Function for setting an equation.
int setEq(Equation* pEq, char* str)
{
	float num;//Coefficient of x,y,z and also the free number on the right side.

	//Integers that check if the equation is done, if '=' sign has appeared and tracking index.
	int isDone = 0, hasEq = 0, index = 0;
	//Integer that helps set the float (positive or negative).
	int posOrNeg = 1;

	pEq->A=(float*)malloc((pEq->count)*sizeof(float));

	if(!pEq->A)
		return 0;

	memset(pEq->A,0,(pEq->count)*sizeof(float));//Sets array to 0.


	while(!isDone)
	{

		if(str[index] == '-')
			posOrNeg = -1;
		else if(isdigit(str[index]))
			num = setFloat(str, &index, 0, posOrNeg);//Sets float value to variable.
		else if (str[index] == '*')
		{
			index++;
			setNum(&pEq, num, str[index]);//Sets float in array.
			num = 0;
			posOrNeg = 1;
		}
		else if(str[index] == '=')
			hasEq = 1;
		else if(hasEq)
		{
			pEq->B = num;
			isDone = 1;
		}
		index++;
	}
	return isDone;
}



//Setting each coefficient to its variable in the array.
void setNum(Equation** pEq, float num, char letter)
{
	if(letter == 'x')
	{
		((*pEq)->A)[0] = num;
	}
	else if(letter == 'y')
	{
		((*pEq)->A)[1] = num;
	}
	else if(letter == 'z')
	{
		((*pEq)->A)[2] = num;
	}
}

//Frees equation data from memory.
void freeEquation(Equation* pEq)
{
	free(pEq->A);
}

