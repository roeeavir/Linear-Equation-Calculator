/*
 * solver.h
 *
 *  Created on: Dec 12, 2019
 *      Author: roee
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "allEquations.h"

typedef struct
{
	int count;
	float** A_Mat;
	float* B_Vec;
	float Detrmin;
	float* X_Vec;
}Solver;

int solve(Solver* pS);
int initSolver(Solver* pS);
int initMatA(Solver* mat, AllEquations* pAllEq);
int initVecB(Solver* pS, AllEquations* pAllEq);
int solveVec(Solver* pS);
void printSol(Solver* pS);
void freeSolver(Solver* pS);

#endif /* SOLVER_H_ */
