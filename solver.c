/*
 * solver.c
 *
 *  Created on: Dec 12, 2019
 *      Author: roee
 */

#include <stdio.h>
#include <stdlib.h>

#include "allEquations.h"
#include "solver.h"
#include "general.h"

//Allocating a solver.
int solve(Solver* pS)
{
	pS = (Solver*)malloc(1*sizeof(Solver));

	if(!initSolver(pS))
		return 0;

	freeSolver(pS);

	return 1;


}

//Inserting values into the solver's variables.
int initSolver(Solver* pS)
{
	AllEquations* pAllEq = (AllEquations*)malloc(1*sizeof(AllEquations));

	if(!pAllEq)
		return 0;

	if(!initAllEquations(pAllEq))
		return 0;

	pS->count = pAllEq->count;

	if(!initMatA(pS, pAllEq))
		return 0;

	if(!initVecB(pS, pAllEq))
		return 0;

	pS->Detrmin = getDet(pS->A_Mat, pS->count);

	if(!solveVec(pS))
		return 0;

	printSol(pS);

	freeAllEquations(pAllEq);

	return 1;

}

//Setting solver's matrix A to point at the all equations equation array address.
int initMatA(Solver* pS, AllEquations* pAllEq)
{
		pS->A_Mat =(float**)malloc((pS->count)*sizeof(float*));
		if(!pS->A_Mat)
			return 0;

		for(int i = 0; i < pS->count; i++)
		{
			pS->A_Mat[i] = (float*)malloc((pS->count)*sizeof(float));
			if(!pS->A_Mat[i])
			{
				free(pS->A_Mat);
				return 0;
			}

			pS->A_Mat[i] = pAllEq->eqArr[i]->A;
		}

		return 1;

}

//Setting solver's vector B's values to be the same as each of the equations B values.
int initVecB(Solver* pS, AllEquations* pAllEq)
{
	pS->B_Vec = (float*)malloc((pS->count)*sizeof(float));

	if(!pS->B_Vec)
		return 0;

	for(int i = 0; i < pAllEq->count; i++)
		pS->B_Vec[i] = pAllEq->eqArr[i]->B;

	return 1;
}

//Calculating vector X with determinants and Cramer's rule.
int solveVec(Solver* pS)
{
	float det;

	pS->X_Vec = (float*)malloc((pS->count)*sizeof(float));
	if(!pS->X_Vec)
		return 0;

	float** mat = (float**)malloc((pS->count)*sizeof(float*));
	if(!mat)
	{
		free(pS->X_Vec);
		return 0;
	}


	for(int j = 0; j < pS->count; j++)
	{
		mat[j] = (float*)malloc((pS->count)*sizeof(float));
		if(!mat[j])
		{
			free(pS->X_Vec);
			free(mat);
			return 0;
		}

	}

	if(pS->Detrmin != 0)
	{
		for(int i = 0; i < pS->count; i++)
		{
			det = cramMat(mat, pS->A_Mat, pS->B_Vec, i, pS->count);

			pS->X_Vec[i] = det/pS->Detrmin;
		}
	}

	for(int k = 0; k < pS->count; k++)
		free(mat[k]);

	free(mat);

	return 1;
}

//Prints wanted output.
void printSol(Solver* pS)
{
	printMat(pS->A_Mat, pS->count);

	printf("\nMatrix A determinant = %.3f\n\n", pS->Detrmin);

	printVecB(pS->B_Vec, pS->count);

	if(pS->Detrmin != 0)
		printVecX(pS->X_Vec, pS->count);
	else
		printf("There is no single solution for that system of equations.\n");
}

//Frees solver data from memory.
void freeSolver(Solver* pS)
{
	for(int i = 0; i < pS->count; i++)
		free(pS->A_Mat[i]);

	free(pS->A_Mat);
	free(pS->B_Vec);
	free(pS->X_Vec);
	free(pS);
}
