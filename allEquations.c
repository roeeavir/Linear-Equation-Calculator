/*
 * allEquations.c
 *
 *  Created on: Dec 12, 2019
 *      Author: roee
 */

#include <stdio.h>
#include <stdlib.h>


#include "equation.h"
#include "allEquations.h"
#include "general.h"

//Setting AllEquations.
int initAllEquations(AllEquations* pAllEq)
{
	pAllEq->count = eqSize();

	pAllEq->eqArr = (Equation**)malloc((pAllEq->count)*sizeof(Equation*));
	if(!pAllEq->eqArr)
		return 0;

	if(!addAllEquations(pAllEq))
		return 0;

	return 1;

}

//Adds equation to AllEquations's equation array.
int addEquation(AllEquations* pAllEq, int index)
{
	Equation* pEq = (Equation*)malloc(1*sizeof(Equation));

	if(!pEq)
		return 0;

	pEq->count = pAllEq->count;

	if(!initEq(pEq, index))
	{
		free(pEq);
		return 0;
	}

	pAllEq->eqArr[index] = pEq;

	return 1;

}

int addAllEquations(AllEquations* pAllEq)
{
	for(int i = 0; i < pAllEq->count; i++)
	{
		if(!addEquation(pAllEq, i))
			return 0;
	}

	return 1;
}

//Frees allEquations data from memory.
void freeAllEquations(AllEquations* pAllEq)
{
	for(int i = 0; i < pAllEq->count; i++)
	{
		freeEquation(pAllEq->eqArr[i]);
		free(pAllEq->eqArr[i]);
	}
	free(pAllEq->eqArr);
	free(pAllEq);
}
