/*
 * allEquations.h
 *
 *  Created on: Dec 12, 2019
 *      Author: roee
 */

#ifndef ALLEQUATIONS_H_
#define ALLEQUATIONS_H_

#include "equation.h"

typedef struct
{
	int count; //number or equation
	Equation** eqArr; //All equations
}AllEquations;

int initAllEquations(AllEquations* pAllEq);
int addEquation(AllEquations* pAllEq, int index);
int addAllEquations(AllEquations* pAllEq);
void freeAllEquations(AllEquations* pAllEq);

#endif /* ALLEQUATIONS_H_ */
