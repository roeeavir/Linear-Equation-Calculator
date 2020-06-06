/*
 * equation.h
 *
 *  Created on: Dec 10, 2019
 *      Author: roee
 */

#ifndef EQUATION_H_
#define EQUATION_H_


typedef struct
{
	int count; //number or coefficients
	float* A; // coefficients of x,y,z (in that order)
	float B; //The free number on the right side;
}Equation;

int initEq(Equation* pEq, int index);
int setEq(Equation* pEq, char* str);
void setNum(Equation** pEq, float num, char letter);
void freeEquation(Equation* pEq);

#endif /* EQUATION_H_ */
